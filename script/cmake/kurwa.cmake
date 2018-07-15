# target_link_library(<target_name> [LINUX|DARWIN|WINDOWS] [SYSTEM] <library_name> [<library_name> ...] [DLL dll])
#
# A mimic of 'target_link_libraries' function, but incapsulates mechanisms of dealing with deploy files and makes
# it easier to deal with crossplatform dependencies.
#
# If none of 'LINUX', 'DARWIN' or 'WINDOWS' is provided, all the system are applied automatically.
# It is possible to put multiple platforms at the same time.
#
# 'SYSTEM' parameter tells linker to search for this library in a system folder.
#
# Asterisk symbol '*' in 'library_name', will be replaced with system-dependent extension (.a or .lib).
#
# 'DLL' parameter must be provided for shared libraries and used only on Windows platform.
# It points to a .dll part of the shared library.
function(target_link_library)
    set(options LINUX DARWIN WINDOWS SYSTEM)
    cmake_parse_arguments(TARGET_LINK_LIBRARY "${options}" "DLL" "" "${ARGN}")
    list(GET TARGET_LINK_LIBRARY_UNPARSED_ARGUMENTS 0 target_name)
    list(REMOVE_AT TARGET_LINK_LIBRARY_UNPARSED_ARGUMENTS 0)

    # Exclude not matching platforms
    if(TARGET_LINK_LIBRARY_LINUX OR TARGET_LINK_LIBRARY_DARWIN OR TARGET_LINK_LIBRARY_WINDOWS)
        if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
            if(NOT TARGET_LINK_LIBRARY_LINUX)
                return()
            endif()
        elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
            if(NOT TARGET_LINK_LIBRARY_DARWIN)
                return()
            endif()
        elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
            if(NOT TARGET_LINK_LIBRARY_WINDOWS)
                return()
            endif()
        endif()
    endif()

    get_target_property(target_is_imported "${target_name}" "IMPORTED")
    get_target_property(target_type "${target_name}" "TYPE")

    foreach(library_name ${TARGET_LINK_LIBRARY_UNPARSED_ARGUMENTS})
        # Produce platform-dependent library name
        if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux" OR "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
            string(REPLACE "*" "a" full_library_name "${library_name}")
        elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
            string(REPLACE "*" "lib" full_library_name "${library_name}")
        endif()

        if(NOT target_is_imported)
            # No need to find library path, because for non-imported targets all the linked libraries
            # must be already added via add_library function
            target_link_libraries("${target_name}" "${full_library_name}")

            # Interface libraries can't hold deploy files
            get_target_property(library_type "${full_library_name}" "TYPE")
            if(NOT library_type STREQUAL "INTERFACE_LIBRARY")
                # Get deploy files for the given library
                get_target_property(library_deploy_files "${full_library_name}" "DEPLOY_FILES")
                if(library_deploy_files)
                    # Get deploy files for this target. If none, set as an empty list
                    get_target_property(target_deploy_files "${target_name}" "DEPLOY_FILES")
                    if(NOT target_deploy_files)
                        set(target_deploy_files "")
                    endif()

                    # Add all the deploy files from the library to target
                    foreach(deploy_file ${library_deploy_files})
                        list(APPEND target_deploy_files "${deploy_file}")
                    endforeach()

                    # The final list must not contain duplicates
                    list(REMOVE_DUPLICATES library_deploy_files)
                    set_target_properties("${target_name}" PROPERTIES "DEPLOY_FILES" "${target_deploy_files}")
                endif()
            endif()
        else()
            # Determine the directory structure
            if(NOT TARGET_LINK_LIBRARY_SYSTEM)
                if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
                    set(library_folder "${CMAKE_CURRENT_SOURCE_DIR}/library/${CMAKE_SYSTEM_NAME}")
                    set(library_path "${library_folder}/${full_library_name}")
                else()
                    set(library_folder "${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_SYSTEM_NAME}/library")
                    set(library_path "${library_folder}/${full_library_name}")
                endif()
            else()
                # Let the system find the library
                set(library_path "${full_library_name}")
            endif()

            # Link the library
            if(target_type STREQUAL "SHARED_LIBRARY")
                if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
                    # For Windows shared libraries DLL argument must be provided
                    set_target_properties("${target_name}" PROPERTIES
                        IMPORTED_IMPLIB "${library_path}"
                        IMPORTED_LOCATION "${library_folder}/${TARGET_LINK_LIBRARY_DLL}"
                    )
                else()
                    # For Linux and OS X the shared library is not divided by two parts like on Windows
                    set_target_properties("${target_name}" PROPERTIES
                        IMPORTED_IMPLIB "${library_path}"
                        IMPORTED_LOCATION "${library_path}"
                    )
                endif()
            else()
                target_link_libraries("${target_name}" INTERFACE "${library_path}")
            endif()
        endif()
    endforeach()
endfunction()

# target_include_directory(<target_name>)
#
# A mimic of 'target_include_directories' function, but this one does not require the directory itself.
# Istead, it finds it automatically, which is much less code to type when dealing with multiple platforms.
#
# It's done assuming there are only 2 possible structures in the current source directory:
#  1) Shared include folder among all the systems (current source directory must contain 'include' subdirectory);
#  2) Each platform has its own include folder (current source directory must contain 'Darwin',
#     'Linux' and 'Windows' subdirectories with 'include' directory inside).
function(target_include_directory target_name)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
        set(include_directory "${CMAKE_CURRENT_SOURCE_DIR}/include")
    else()
        set(include_directory "${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_SYSTEM_NAME}/include")
        if(NOT EXISTS "${include_directory}")
            message(FATAL_ERROR "Invalid project structure for target '${target_name}'!")
        endif()
    endif()

    get_target_property(include_directories "${target_name}" "INTERFACE_INCLUDE_DIRECTORIES")
    if(NOT include_directories)
        set(include_directories "")
    endif()

    list(APPEND include_directories "${include_directory}")
    set_target_properties("${target_name}" PROPERTIES "INTERFACE_INCLUDE_DIRECTORIES" "${include_directories}")
endfunction()

# target_add_deploy_files(<target_name> [DARWIN|LINUX|WINDOWS] <file_name> [<file_name> ...])
#
# For executable targets puts the given files or directories into the folder containing the executable file.
# For library targets forces saves the given files or directories into internal list, so executables that include
# this library can deploy these files or directories too.
#
# If none of 'LINUX', 'DARWIN' or 'WINDOWS' is provided, all the system are applied automatically.
# It is possible to put multiple platforms at the same time.
function(target_add_deploy_files)
    set(options LINUX DARWIN WINDOWS)
    cmake_parse_arguments(TARGET_ADD_DEPLOY_ITEM "${options}" "" "" "${ARGN}")
    list(GET TARGET_ADD_DEPLOY_ITEM_UNPARSED_ARGUMENTS 0 target_name)
    list(REMOVE_AT TARGET_ADD_DEPLOY_ITEM_UNPARSED_ARGUMENTS 0)

    # Exclude not matching platforms
    if(TARGET_ADD_DEPLOY_ITEM_LINUX OR TARGET_ADD_DEPLOY_ITEM_DARWIN OR TARGET_ADD_DEPLOY_ITEM_WINDOWS)
        if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
            if(NOT TARGET_ADD_DEPLOY_ITEM_LINUX)
                return()
            endif()
        elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
            if(NOT TARGET_ADD_DEPLOY_ITEM_DARWIN)
                return()
            endif()
        elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
            if(NOT TARGET_ADD_DEPLOY_ITEM_WINDOWS)
                return()
            endif()
        endif()
    endif()

    get_target_property(target_deploy_files "${target_name}" "DEPLOY_FILES")
    if(NOT target_deploy_files)
        set(target_deploy_files "")
    endif()

    foreach(file_name ${TARGET_ADD_DEPLOY_ITEM_UNPARSED_ARGUMENTS})
        # File names are expected to be relative to current source directory
        list(APPEND target_deploy_files "${CMAKE_CURRENT_SOURCE_DIR}/${file_name}")
    endforeach()

    set_target_properties("${target_name}" PROPERTIES "DEPLOY_FILES" "${target_deploy_files}")
endfunction()

# bundle_executable(<target_name>)
#
# Deploy everything and create a bundle file for OS X platform.
function(bundle_executable target_name)
    # Force Linux to search for shared libraries next to executable
    if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
        get_target_property(linker_flags "${target_name}" "LINK_FLAGS")
        if(NOT linker_flags)
            set(linker_flags "")
        endif()
        list(APPEND linker_flags "-Wl,-rpath,\"$ORIGIN\"")
        set_target_properties("${target_name}" PROPERTIES
                SKIP_BUILD_RPATH "ON"
                LINK_FLAGS "${linker_flags}")
    endif()

    get_target_property(target_deploy_files "${target_name}" "DEPLOY_FILES")
    if(target_deploy_files)
        get_target_property(output_directory "${target_name}" "RUNTIME_OUTPUT_DIRECTORY")
        foreach(file_name ${target_deploy_files})
            if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
                # \H — Copies files with hidden and system file attributes
                # \Y — Suppresses prompting to confirm that you want to overwrite an existing file
                # \C — Ignores errors
                # \S — Copies directories and subdirectories, unless they are empty
                add_custom_command(TARGET "${target_name}" POST_BUILD
                        COMMAND xcopy \"${file_name}\" \"${output_directory}\" /H /Y /C /S)
            else()
                # -rf — Copy files and directories recursive
                add_custom_command(TARGET "${target_name}" POST_BUILD
                        COMMAND cp -rf \"${file_name}\" \"${output_directory}\")
            endif()
        endforeach()
    endif()
endfunction()

define_property(TARGET PROPERTY DEPLOY_FILES
    BRIEF_DOCS "List of files to deploy"
    FULL_DOCS "List of files to deploy"
)

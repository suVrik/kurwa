# Copyright (c) 2018, 21DOGZ.
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
# except in compliance with the License. You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under the License is
# distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and limitations under the License.

# target_link_library(<target_name> [LINUX|DARWIN|WINDOWS] <library_name> [<library_name> ...] [DLL dll])
#
# A mimic of 'target_link_libraries' function, but incapsulates mechanisms of dealing with resources and makes
# it easier to deal with crossplatform dependencies.
#
# If none of 'LINUX', 'DARWIN' or 'WINDOWS' is provided, all the system are applied automatically.
# It is possible to put multiple platforms at the same time.
#
# The function searches for libraries in:
#  1) Shared library folder among all the systems (current source directory must contain 'library' subdirectory);
#  2) Each platform has its own library folder (current source directory must contain 'Darwin',
#     'Linux' and 'Windows' subdirectories with 'library' directory inside);
#  3) Among system libraries (if first 2 options didn't work).
#
# Asterisk symbol '*' in 'library_name', will be replaced with system-dependent extension (.a or .lib).
#
# 'DLL' parameter must be provided for shared libraries and used only on Windows platform.
# It points to a .dll part of the shared library.
function(target_link_library)
    set(options LINUX DARWIN WINDOWS)
    cmake_parse_arguments(TARGET_LINK_LIBRARY "${options}" "DLL" "" "${ARGN}")
    list(GET TARGET_LINK_LIBRARY_UNPARSED_ARGUMENTS 0 target_name)
    list(REMOVE_AT TARGET_LINK_LIBRARY_UNPARSED_ARGUMENTS 0)

    # Exclude not matching platforms
    if(TARGET_LINK_LIBRARY_LINUX OR TARGET_LINK_LIBRARY_DARWIN OR TARGET_LINK_LIBRARY_WINDOWS)
        if(LINUX)
            if(NOT TARGET_LINK_LIBRARY_LINUX)
                return()
            endif()
        elseif(APPLE)
            if(NOT TARGET_LINK_LIBRARY_DARWIN)
                return()
            endif()
        elseif(WIN32)
            if(NOT TARGET_LINK_LIBRARY_WINDOWS)
                return()
            endif()
        endif()
    endif()

    get_target_property(target_is_imported "${target_name}" "IMPORTED")
    get_target_property(target_type "${target_name}" "TYPE")

    foreach(library_name ${TARGET_LINK_LIBRARY_UNPARSED_ARGUMENTS})
        if(NOT target_is_imported)
            # No need to find library path, because for non-imported targets all the linked libraries
            # must be already added via add_library function
            target_link_libraries("${target_name}" "${library_name}")

            # Interface libraries can't hold deploy files
            get_target_property(library_type "${library_name}" "TYPE")
            if(NOT library_type STREQUAL "INTERFACE_LIBRARY")
                # We're about to copy all the resources and libraries from the library to our target
                get_target_property(library_deploy_resources "${library_name}" "DEPLOY_RESOURCES")
                if(library_deploy_resources)
                    # Get deploy files for this target. If none, set as an empty list
                    get_target_property(target_deploy_resources "${target_name}" "DEPLOY_RESOURCES")
                    if(NOT target_deploy_resources)
                        set(target_deploy_resources "")
                    endif()

                    # Add all the resources from the library to target
                    foreach(deploy_file ${library_deploy_resources})
                        list(APPEND target_deploy_resources "${deploy_file}")
                    endforeach()

                    set_target_properties("${target_name}" PROPERTIES "DEPLOY_RESOURCES" "${target_deploy_resources}")
                endif()

                # We need target libraries to merge library's libraries and the library itself into it
                get_target_property(target_deploy_libraries "${target_name}" "DEPLOY_LIBRARIES")
                if(NOT target_deploy_libraries)
                    set(target_deploy_libraries "")
                endif()

                get_target_property(library_deploy_libraries "${library_name}" "DEPLOY_LIBRARIES")
                if(library_deploy_libraries)
                    foreach(deploy_file ${library_deploy_libraries})
                        list(APPEND target_deploy_libraries "${deploy_file}")
                    endforeach()
                endif()

                # Put the shared library into a target too
                get_target_property(library_imported_location "${library_name}" "IMPORTED_LOCATION")
                if(library_imported_location)
                    list(APPEND target_deploy_libraries "${library_imported_location}")
                endif()

                set_target_properties("${target_name}" PROPERTIES "DEPLOY_LIBRARIES" "${target_deploy_libraries}")
            endif()
        else()
            # Produce platform-dependent library name
            if(LINUX OR APPLE)
                string(REPLACE "*" ".a" full_library_name "${library_name}")
            else()
                string(REPLACE "*" ".lib" full_library_name "${library_name}")
            endif()

            # Determine the directory structure
            if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/library")
                set(library_folder "${CMAKE_CURRENT_SOURCE_DIR}/library/${CMAKE_SYSTEM_NAME}")
            else()
                set(library_folder "${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_SYSTEM_NAME}/library")
            endif()

            # If the given library does not exist in the determined directory, it is possibly a system library
            if(NOT EXISTS "${library_folder}/${full_library_name}")
                set(library_folder "")
            endif()

            # Try to use debug version of the library on Windows, if exists
            if(WIN32)
                string(REPLACE "*" "d.lib" debug_library_name "${library_name}")
                if(EXISTS "${library_folder}/${debug_library_name}")
                    string(REPLACE "*" "$<$<CONFIG:Debug>:d>.lib" full_library_name "${library_name}")
                endif()
            endif()

            if(library_folder)
                set(library_path "${library_folder}/${full_library_name}")
            else()
                set(library_path "${full_library_name}")
            endif()

            if(target_type STREQUAL "SHARED_LIBRARY" AND TARGET_LINK_LIBRARY_DLL)
                if(WIN32)
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

# target_add_resources(<target_name> [DARWIN|LINUX|WINDOWS] <file_name> [<file_name> ...])
#
# For executable targets put the given files and directories into platform-dependent resources directory.
# For library targets save the given files and directories into internal list. Later, executables, that link
# these libraries, put these resources into their platform-dependent resource directory.
#
# If none of 'LINUX', 'DARWIN' or 'WINDOWS' is provided, all the system are applied automatically.
# It is possible to put multiple platforms at the same time.
function(target_add_resources)
    set(options LINUX DARWIN WINDOWS)
    cmake_parse_arguments(TARGET_ADD_DEPLOY_ITEM "${options}" "" "" "${ARGN}")
    list(GET TARGET_ADD_DEPLOY_ITEM_UNPARSED_ARGUMENTS 0 target_name)
    list(REMOVE_AT TARGET_ADD_DEPLOY_ITEM_UNPARSED_ARGUMENTS 0)

    # Exclude not matching platforms
    if(TARGET_ADD_DEPLOY_ITEM_LINUX OR TARGET_ADD_DEPLOY_ITEM_DARWIN OR TARGET_ADD_DEPLOY_ITEM_WINDOWS)
        if(LINUX)
            if(NOT TARGET_ADD_DEPLOY_ITEM_LINUX)
                return()
            endif()
        elseif(APPLE)
            if(NOT TARGET_ADD_DEPLOY_ITEM_DARWIN)
                return()
            endif()
        elseif(WIN32)
            if(NOT TARGET_ADD_DEPLOY_ITEM_WINDOWS)
                return()
            endif()
        endif()
    endif()

    get_target_property(target_deploy_resources "${target_name}" "DEPLOY_RESOURCES")
    if(NOT target_deploy_resources)
        set(target_deploy_resources "")
    endif()

    foreach(file_name ${TARGET_ADD_DEPLOY_ITEM_UNPARSED_ARGUMENTS})
        # Convert relative paths to absolute
        get_filename_component(absolute_file_name "${file_name}"
                REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
        list(APPEND target_deploy_resources "${absolute_file_name}")
    endforeach()

    set_target_properties("${target_name}" PROPERTIES "DEPLOY_RESOURCES" "${target_deploy_resources}")
endfunction()

# target_set_bundle_information(<target_name>
#                               <BUNDLE_NAME bundle_name>
#                               <BUNDLE_VERSION bundle_version>
#                               <COPYRIGHT copyright>
#                               <GUI_IDENTIFIER gui_identifier>
#                               <ICON_FILE icon_file>
#                               <INFO_STRING info_string>
#                               <LONG_VERSION_STRING long_version_string>
#                               <SHORT_VERSION_STRING short_version_string>)
#
# Specify information for OS X bundle. On all the other platforms currently ignored.
#
# TODO: use this information for windows executables.
function(target_set_bundle_information)
    if(APPLE)
        set(single_arguments BUNDLE_NAME BUNDLE_VERSION COPYRIGHT GUI_IDENTIFIER ICON_FILE
                INFO_STRING LONG_VERSION_STRING SHORT_VERSION_STRING)
        cmake_parse_arguments(BUNDLE_INFORMATION "" "${single_arguments}" "" "${ARGN}")
        list(GET BUNDLE_INFORMATION_UNPARSED_ARGUMENTS 0 target_name)

        set_target_properties("${target_name}" PROPERTIES
                MACOSX_BUNDLE "ON"
                MACOSX_BUNDLE_BUNDLE_NAME "${BUNDLE_INFORMATION_BUNDLE_NAME}"
                MACOSX_BUNDLE_BUNDLE_VERSION "${BUNDLE_INFORMATION_BUNDLE_VERSION}"
                MACOSX_BUNDLE_COPYRIGHT "${BUNDLE_INFORMATION_COPYRIGHT}"
                MACOSX_BUNDLE_GUI_IDENTIFIER "${BUNDLE_INFORMATION_GUI_IDENTIFIER}"
                MACOSX_BUNDLE_ICON_FILE "${BUNDLE_INFORMATION_ICON_FILE}"
                MACOSX_BUNDLE_INFO_STRING "${BUNDLE_INFORMATION_INFO_STRING}"
                MACOSX_BUNDLE_LONG_VERSION_STRING "${BUNDLE_INFORMATION_LONG_VERSION_STRING}"
                MACOSX_BUNDLE_SHORT_VERSION_STRING "${BUNDLE_INFORMATION_SHORT_VERSION_STRING}")
    endif()
endfunction()

# finalize_executable(<target_name>)
#
# Deploy everything and create a bundle file for OS X platform.
macro(finalize_executable target_name)
    # Use static version of the run-time library
    if(WIN32)
        # Required for __cplusplus define to be other than 1997
        set_target_properties("${target_name}" PROPERTIES
                COMPILE_FLAGS "/Zc:__cplusplus")

        get_target_property(myCOMPILE_FLAGS "${target_name}" "COMPILE_FLAGS")

        set(compiler_flags
                CMAKE_CXX_FLAGS
                CMAKE_CXX_FLAGS_DEBUG
                CMAKE_CXX_FLAGS_RELEASE
                CMAKE_C_FLAGS
                CMAKE_C_FLAGS_DEBUG
                CMAKE_C_FLAGS_RELEASE)

        foreach(compiler_flag ${compiler_flags})
            string(REPLACE "/MD" "/MT" ${compiler_flag} "${${compiler_flag}}")
        endforeach()
    endif()

    # Force Linux to search for shared libraries next to executable
    if(LINUX OR APPLE)
        get_target_property(linker_flags "${target_name}" "LINK_FLAGS")
        if(NOT linker_flags)
            set(linker_flags "")
        endif()
        if(LINUX)
            list(APPEND linker_flags "-Wl,-rpath,\"$ORIGIN\"")
        else()
            list(APPEND linker_flags "-Wl,-rpath,\"@executable_path/../Frameworks\"")
        endif()
        set_target_properties("${target_name}" PROPERTIES
                SKIP_BUILD_RPATH "ON"
                LINK_FLAGS "${linker_flags}")
    endif()

    get_target_property(output_directory "${target_name}" "RUNTIME_OUTPUT_DIRECTORY")

    # For Windows and Linux simply put the resources into 'resources' folder, and libraries next to binary file
    if(WIN32 OR LINUX)
        get_target_property(target_deploy_resources "${target_name}" "DEPLOY_RESOURCES")
        if(target_deploy_resources)
            list(REMOVE_DUPLICATES target_deploy_resources)

            set(resources_directory "${output_directory}/resources")
            add_custom_command(TARGET "${target_name}" POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory "${resources_directory}")

            foreach(file_name ${target_deploy_resources})
                add_custom_command(TARGET "${target_name}" POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy "${file_name}" "${resources_directory}")
            endforeach()
        endif()

        get_target_property(target_deploy_libraries "${target_name}" "DEPLOY_LIBRARIES")
        if(target_deploy_libraries)
            list(REMOVE_DUPLICATES target_deploy_libraries)

            foreach(file_name ${target_deploy_libraries})
                add_custom_command(TARGET "${target_name}" POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy "${file_name}" "${output_directory}")
            endforeach()
        endif()
    else()
        get_target_property(is_macos_bundle "${target_name}" "MACOSX_BUNDLE")
        if(NOT is_macos_bundle)
            message(FATAL_ERROR "'target_set_bundle_information' call for target '${target_name}' is required")
        endif()

        set(bundle_path "${output_directory}/${target_name}.app")

        # For OS X put libraries into 'Frameworks' and resources into 'Resources'
        get_target_property(target_deploy_resources "${target_name}" "DEPLOY_RESOURCES")
        if(target_deploy_resources)
            list(REMOVE_DUPLICATES target_deploy_resources)

            # Unlike for libraries, Linux and Windows, for Mac OS resources there's a native CMake solution
            target_sources("${target_name}" PRIVATE "${target_deploy_resources}")
            set_target_properties("${target_name}" PROPERTIES
                    RESOURCE "${target_deploy_resources}")
        endif()

        get_target_property(target_deploy_libraries "${target_name}" "DEPLOY_LIBRARIES")
        if(target_deploy_libraries)
            list(REMOVE_DUPLICATES target_deploy_libraries)

            set(frameworks_path "${bundle_path}/Contents/Frameworks")

            # Just in case, create all the needed folders. The unnecessary directories will be ignored
            add_custom_command(TARGET "${target_name}" POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory "${bundle_path}")
            add_custom_command(TARGET "${target_name}" POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory "${bundle_path}/Contents")
            add_custom_command(TARGET "${target_name}" POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory "${frameworks_path}")

            foreach(file_name ${target_deploy_libraries})
                add_custom_command(TARGET "${target_name}" POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy "${file_name}" "${frameworks_path}")
            endforeach()
        endif()
    endif()
endmacro()

# Define LINUX global variable, because there's no such variable by default
if(UNIX AND NOT APPLE)
    set(LINUX TRUE CACHE INTERNAL "" FORCE)
endif()

define_property(TARGET PROPERTY DEPLOY_RESOURCES
    BRIEF_DOCS "List of resources to deploy"
    FULL_DOCS "List of resources to deploy"
)

define_property(TARGET PROPERTY DEPLOY_LIBRARIES
    BRIEF_DOCS "List of libraries to deploy"
    FULL_DOCS "List of libraries to deploy"
)

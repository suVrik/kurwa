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

cmake_minimum_required(VERSION 3.9)

project(framework)

# Framework source files
file(GLOB_RECURSE FRAMEWORK_SOURCE "*.h" "*.cpp")
add_library(framework STATIC "${FRAMEWORK_SOURCE}")

# Framework properties
set_property(TARGET framework PROPERTY CXX_STANDARD "17")
set_property(TARGET framework PROPERTY LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Use static version of the run-time library
if(WIN32)
    # Required for __cplusplus define to be other than 1997
    set_target_properties("framework" PROPERTIES
            COMPILE_FLAGS "/Zc:__cplusplus")

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


# For programs that include framework
target_include_directories(framework PUBLIC include)

# For some reason cmake cannot determine link language for the framework without this
set_target_properties(framework PROPERTIES LINKER_LANGUAGE CXX)

# Framework libraries
target_link_library(framework eastl)
target_link_library(framework fmt)
target_link_library(framework glew)
target_link_library(framework imgui)
target_link_library(framework sdl2)
target_link_library(framework utf8)

if(LINUX)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(framework PRIVATE Threads::Threads)
endif()

# Required by 'kw/debug/stacktrace'
if(WIN32)
    target_link_libraries(framework PRIVATE $<$<CONFIG:Debug>:Dbghelp>)
endif()

# KW_DEBUG must be defined on debug configuration.
target_compile_definitions(framework PUBLIC $<$<CONFIG:Debug>:KW_DEBUG>)

# Platform definitions.
if(WIN32)
    target_compile_definitions(framework PUBLIC KW_WINDOWS)
elseif(APPLE)
    target_compile_definitions(framework PUBLIC KW_OSX)
elseif(UNIX)
    target_compile_definitions(framework PUBLIC KW_LINUX)
endif()

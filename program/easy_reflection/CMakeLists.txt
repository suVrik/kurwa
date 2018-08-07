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

project(easy_reflection)

# Use all source files provided in 'source' directory
file(GLOB_RECURSE EASY_REFLECTION_SOURCE "source/*.h" "source/*.cpp")
add_executable(easy_reflection "${EASY_REFLECTION_SOURCE}")

# Include and link to clang-c
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/library/clang-c")
target_link_libraries(easy_reflection PRIVATE clang-c)

# Enable C++17 and change the executable directory.
set_target_properties(easy_reflection PROPERTIES
        CXX_STANDARD "17"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Use static version of the run-time library on Windows.
if(WIN32)
    # Required for __cplusplus define to be other than 1997.
    set_target_properties(easy_reflection PROPERTIES
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

# TODO: Custom RPath on Linux and OSX?

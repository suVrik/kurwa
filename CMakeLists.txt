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

project(kurwa)

# TODO: Remove includes, consider pure CMake.
include("script/cmake/kurwa.cmake")

if(MSVC)
    set(compiler_flags
            CMAKE_C_FLAGS
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_MINSIZEREL
            CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_CXX_FLAGS
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL
            CMAKE_CXX_FLAGS_RELWITHDEBINFO
    )

    # Use static version of the run-time library.
    foreach(compiler_flag ${compiler_flags})
        string(REPLACE "/MD" "/MT" ${compiler_flag} "${${compiler_flag}}")
    endforeach()
else()
    # Allow to use `offsetof` on non-POD types.
    add_compile_options(-Wno-invalid-offsetof)
endif()

# Specify output folders. Shared libraries must override their `LIBRARY_OUTPUT_DIRECTORY` target property
# on Unix platforms, because their output libraries must be deployed in the binary directory.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Libraries.
add_subdirectory(library/eastl)
add_subdirectory(library/enet)
add_subdirectory(library/fmt)
add_subdirectory(library/glew)
add_subdirectory(library/glm)
add_subdirectory(library/gmock)
add_subdirectory(library/imgui)
add_subdirectory(library/lz4)
add_subdirectory(library/ogg)
add_subdirectory(library/openal)
add_subdirectory(library/zlib)
add_subdirectory(library/png)
add_subdirectory(library/sdl2)
add_subdirectory(library/tinyxml2)
add_subdirectory(library/utf8)
add_subdirectory(library/vorbis)

# Framework.
add_subdirectory(framework)

# Programs.
add_subdirectory(program/testbed)
add_subdirectory(program/unittest)

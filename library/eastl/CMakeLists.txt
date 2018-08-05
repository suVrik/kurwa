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

project(eastl)

add_library(eastl STATIC
        "${CMAKE_CURRENT_SOURCE_DIR}/source/allocator.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/assert.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/fixed_pool.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/hashtable.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/intrusive_list.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/numeric_limits.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/red_black_tree.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/string.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/thread_support.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/EAMemory.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/EASprintf.cpp"
)

target_include_directories(eastl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_compile_definitions(eastl PUBLIC
        _CHAR16T=1
        _CRT_SECURE_NO_WARNINGS=1
        _SCL_SECURE_NO_WARNINGS=1
        EASTL_OPENSOURCE=1
        EASTL_USER_DEFINED_ALLOCATOR=1
        EASTL_NAME_ENABLED=0
)

set_target_properties(eastl PROPERTIES CXX_STANDARD "17")

if(WIN32)
    set(compiler_flags
            CMAKE_CXX_FLAGS
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_RELEASE
    )

    foreach(compiler_flag ${compiler_flags})
        string(REPLACE "/MD" "/MT" ${compiler_flag} "${${compiler_flag}}")
    endforeach()
endif()

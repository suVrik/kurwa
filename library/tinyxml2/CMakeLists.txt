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

project(tinyxml2)

add_library(tinyxml2 STATIC "${CMAKE_CURRENT_SOURCE_DIR}/source/tinyxml2.cpp")

target_include_directories(tinyxml2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(tinyxml2 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/tinyxml2")

set_target_properties(tinyxml2 PROPERTIES CXX_STANDARD "17")

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

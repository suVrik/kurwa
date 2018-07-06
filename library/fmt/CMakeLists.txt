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

cmake_minimum_required(VERSION 3.11)

project(fmt)

add_library(fmt INTERFACE IMPORTED GLOBAL)
target_include_directories(fmt INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(fmt INTERFACE
        "$<$<STREQUAL:${CMAKE_SYSTEM_NAME},Linux>:${CMAKE_CURRENT_SOURCE_DIR}/library/Linux/libfmt.a>"
        "$<$<STREQUAL:${CMAKE_SYSTEM_NAME},Darwin>:${CMAKE_CURRENT_SOURCE_DIR}/library/Darwin/libfmt.a>"
        "$<$<STREQUAL:${CMAKE_SYSTEM_NAME},Windows>:${CMAKE_CURRENT_SOURCE_DIR}/library/Windows/fmt.lib>")

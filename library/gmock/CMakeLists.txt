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

project(gmock)

add_library(gmock INTERFACE IMPORTED GLOBAL)
target_include_directories(gmock INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(gmock INTERFACE
        "$<$<STREQUAL:${CMAKE_SYSTEM_NAME},Linux>:pthread;${CMAKE_CURRENT_SOURCE_DIR}/library/Linux/libgmock.a>"
        "$<$<STREQUAL:${CMAKE_SYSTEM_NAME},Darwin>:${CMAKE_CURRENT_SOURCE_DIR}/library/Darwin/libgmock.a>"
        "$<$<STREQUAL:${CMAKE_SYSTEM_NAME},Windows>:${CMAKE_CURRENT_SOURCE_DIR}/library/Windows/gmock.lib>")

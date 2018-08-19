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

project(unittest)

file(GLOB_RECURSE UNITTEST_SOURCE "source/*.h" "source/*.cpp")
add_executable(unittest "${UNITTEST_SOURCE}")

set_target_properties(unittest PROPERTIES
        CXX_STANDARD "17"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(UNITTEST_VERSION "0.0")
target_set_bundle_information(unittest
                              BUNDLE_NAME "unittest"
                              BUNDLE_VERSION "${UNITTEST_VERSION}"
                              COPYRIGHT "Copyright (c) 2018, 21DOGZ"
                              GUI_IDENTIFIER "com.21dogz.unittest"
                              ICON_FILE ""
                              INFO_STRING "unittest"
                              LONG_VERSION_STRING "${UNITTEST_VERSION}"
                              SHORT_VERSION_STRING "${UNITTEST_VERSION}")

file(GLOB_RECURSE UNITTEST_RESOURCES "resource/*")
target_add_resources(unittest "${UNITTEST_RESOURCES}")

target_link_library(unittest framework)
target_link_library(unittest gmock)

finalize_executable(unittest)

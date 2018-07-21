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

project(testbed)

file(GLOB_RECURSE TESTBED_SOURCE "source/*.h" "source/*.cpp")
add_executable(testbed "${TESTBED_SOURCE}")

set_target_properties(testbed PROPERTIES
        CXX_STANDARD "17"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(TESTBED_VERSION "0.0")
target_set_bundle_information(testbed
        BUNDLE_NAME "testbed"
        BUNDLE_VERSION "${TESTBED_VERSION}"
        COPYRIGHT "Copyright (c) 2018, 21DOGZ"
        GUI_IDENTIFIER "com.21dogz.testbed"
        ICON_FILE ""
        INFO_STRING "testbed"
        LONG_VERSION_STRING "${TESTBED_VERSION}"
        SHORT_VERSION_STRING "${TESTBED_VERSION}")

target_link_library(testbed framework)

finalize_executable(testbed)

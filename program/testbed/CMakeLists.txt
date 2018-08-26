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

project(testbed CXX)

file(GLOB_RECURSE TESTBED_SOURCE "source/*.h" "source/*.cpp")
add_executable(testbed "${TESTBED_SOURCE}")

set_target_properties(testbed PROPERTIES CXX_STANDARD "17")

target_link_libraries(testbed PRIVATE framework)

# Set up shared libraries location directory.
if(UNIX)
    set_property(TARGET testbed PROPERTY SKIP_BUILD_RPATH "ON")

    if(APPLE)
        set_property(TARGET testbed APPEND PROPERTY LINK_FLAGS "-Wl,-rpath,\"@executable_path\"")
    else()
        set_property(TARGET testbed APPEND PROPERTY LINK_FLAGS "-Wl,-rpath,\"$ORIGIN\"")
    endif()
endif()

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

# For programs that include framework
target_include_directory(framework)

# For some reason cmake cannot determine link language for the framework without this
set_target_properties(framework PROPERTIES LINKER_LANGUAGE CXX)

# Framework libraries
target_link_library(framework eastl)
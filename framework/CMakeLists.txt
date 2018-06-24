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

project(framework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

file(GLOB_RECURSE FRAMEWORK_SOURCE "*.h" "*.cpp")
add_library(framework STATIC ${FRAMEWORK_SOURCE})

# For programs that include the framework
target_include_directories(framework INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# For some reason cmake cannot determine link language for framework without this
set_target_properties(framework PROPERTIES LINKER_LANGUAGE CXX)

# Libraries
target_link_libraries(framework PUBLIC eastl)

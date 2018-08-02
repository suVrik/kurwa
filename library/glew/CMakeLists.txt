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

project(glew)

add_definitions(-DGLEW_STATIC)
add_library(glew INTERFACE IMPORTED GLOBAL)
target_include_directory(glew)
target_link_library(glew "libGLEW*")
find_package(OpenGL REQUIRED)
target_link_libraries(glew INTERFACE ${OPENGL_LIBRARIES})

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

project(all)

# Includes
include("script/cmake/kurwa.cmake")

# Libraries
add_subdirectory("library/eastl")
add_subdirectory("library/enet")
add_subdirectory("library/fmt")
add_subdirectory("library/glew")
add_subdirectory("library/glm")
add_subdirectory("library/gmock")
add_subdirectory("library/imgui")
add_subdirectory("library/lz4")
add_subdirectory("library/ogg")
add_subdirectory("library/openal")
add_subdirectory("library/png")
add_subdirectory("library/sdl2")
add_subdirectory("library/theora")
add_subdirectory("library/tinyxml2")
add_subdirectory("library/utf8")
add_subdirectory("library/vorbis")
add_subdirectory("library/zlib")

# Framework
add_subdirectory(framework)

# Programs
add_subdirectory("program/testbed")
add_subdirectory("program/unittest")

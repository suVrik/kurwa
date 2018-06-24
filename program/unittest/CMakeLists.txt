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

project(unittest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Executable
file(GLOB_RECURSE UNITTEST_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
add_executable(unittest ${UNITTEST_SOURCE})

# Libraries
target_link_libraries(unittest PRIVATE framework)
target_link_libraries(unittest PRIVATE eastl)
target_link_libraries(unittest PRIVATE enet)
target_link_libraries(unittest PRIVATE fmt)
target_link_libraries(unittest PRIVATE glew)
target_link_libraries(unittest PRIVATE gmock)
target_link_libraries(unittest PRIVATE imgui)
target_link_libraries(unittest PRIVATE lz4)
target_link_libraries(unittest PRIVATE ogg)
target_link_libraries(unittest PRIVATE openal)
target_link_libraries(unittest PRIVATE png)
target_link_libraries(unittest PRIVATE sdl2)
target_link_libraries(unittest PRIVATE theora)
target_link_libraries(unittest PRIVATE tinyxml2)
target_link_libraries(unittest PRIVATE vorbis)
target_link_libraries(unittest PRIVATE zlib)

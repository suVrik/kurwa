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

# Unitest sources
file(GLOB_RECURSE UNITTEST_SOURCE "source/*.h" "source/*.cpp")
add_executable(unittest "${UNITTEST_SOURCE}")

# Unittest properties
set_property(TARGET unittest PROPERTY CXX_STANDARD "17")
set_property(TARGET unittest PROPERTY RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
append_property(TARGET framework PROPERTY LINK_FLAGS "-stdlib=libc++")
append_property(TARGET framework PROPERTY LINK_FLAGS "-lc++abi")

# Unittest deploy files and folders
target_add_deploy_files(unittest resource)

# Unittest libraries
target_link_library(unittest framework)
target_link_library(unittest eastl)
target_link_library(unittest enet)
target_link_library(unittest fmt)
target_link_library(unittest glew)
target_link_library(unittest gmock)
target_link_library(unittest imgui)
target_link_library(unittest lz4)
target_link_library(unittest ogg)
target_link_library(unittest openal)
target_link_library(unittest png)
target_link_library(unittest sdl2)
target_link_library(unittest theora)
target_link_library(unittest tinyxml2)
target_link_library(unittest vorbis)
target_link_library(unittest zlib)

# Deploy everything and create a bundle file for OS X
bundle_executable(unittest)

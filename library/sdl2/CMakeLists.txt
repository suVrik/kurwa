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

project(sdl2)

add_library(sdl2 SHARED IMPORTED GLOBAL)

target_include_directories(sdl2 INTERFACE "${CMAKE_SYSTEM_NAME}/include")

target_link_library(sdl2 "libSDL2main.*")
target_link_library(sdl2 DARWIN "libSDL2.dylib")
target_link_library(sdl2 LINUX "libSDL2-2.0.so.0.8.0")
target_link_library(sdl2 WINDOWS "SDL2.lib" DLL "SDL2.dll")

target_add_deploy_files(sdl2 DARWIN "Darwin/library/libSDL2.dylib")
target_add_deploy_files(sdl2 LINUX "Linux/library/libSDL2-2.0.so.0.8.0")
target_add_deploy_files(sdl2 WINDOWS "Windows/library/SDL2.dll")

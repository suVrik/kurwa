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

project(openal)

add_library(openal SHARED IMPORTED GLOBAL)

target_include_directory(openal)

target_link_library(openal DARWIN "libopenal.1.dylib")
target_link_library(openal LINUX "libopenal.so.1")
target_link_library(openal WINDOWS "OpenAL32.lib" DLL "OpenAL32.dll")

target_add_deploy_files(openal DARWIN "Darwin/library/libopenal.1.dylib")
target_add_deploy_files(openal LINUX "Linux/library/libopenal.so.1")
target_add_deploy_files(openal WINDOWS "Windows/library/OpenAL32.dll")

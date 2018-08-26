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

project(framework CXX)

file(GLOB_RECURSE FRAMEWORK_SOURCE "*.h" "*.cpp")
add_library(framework STATIC "${FRAMEWORK_SOURCE}")

set_property(TARGET framework PROPERTY CXX_STANDARD "17")

target_include_directories(framework PUBLIC include)

# Framework libraries.
target_link_libraries(framework PUBLIC eastl)
target_link_libraries(framework PRIVATE enet)
target_link_libraries(framework PUBLIC fmt)
target_link_libraries(framework PRIVATE glew)
target_link_libraries(framework PRIVATE glm)
target_link_libraries(framework PUBLIC imgui)
target_link_libraries(framework PRIVATE lz4)
target_link_libraries(framework PRIVATE ogg)
target_link_libraries(framework PRIVATE openal)
target_link_libraries(framework PRIVATE png)
target_link_libraries(framework PUBLIC sdl2)
target_link_libraries(framework PUBLIC tinyxml2)
target_link_libraries(framework PRIVATE utf8)
target_link_libraries(framework PRIVATE vorbis)
target_link_libraries(framework PRIVATE zlib)

if(UNIX AND NOT APPLE)
    # Required for <thread> on Linux.
    target_link_libraries(framework PRIVATE pthread)
endif()

if(WIN32)
    # Required by 'kw/debug/stacktrace'.
    target_link_libraries(framework PRIVATE $<$<CONFIG:Debug>:Dbghelp>)

    # Required by filesystem.
    target_link_libraries(framework PRIVATE Shlwapi)
endif()

# KW_DEBUG must be defined on debug configuration.
target_compile_definitions(framework PUBLIC $<$<CONFIG:Debug>:KW_DEBUG>)

if(MSVC)
    # Required for __cplusplus define to be other than 1997.
    target_compile_options(framework PUBLIC "/Zc:__cplusplus")
endif()

# Treat warnings as errors.
if(MSVC)
    target_compile_options(framework PUBLIC /WX /W3)
else()
    target_compile_options(framework PUBLIC -Werror -Wall -Wextra -pedantic)

    # We're not C++98 compatible.
    target_compile_options(framework PUBLIC -Wno-c++98-compat-pedantic)
    # We allow default section in switch with all covered cases.
    target_compile_options(framework PUBLIC -Wno-covered-switch-default)
    # Allow automatic generation of copy constructors and assignment operators when custom destructor is provided.
    target_compile_options(framework PUBLIC -Wno-deprecated)
    # Allow using %f for floats in functions like printf.
    target_compile_options(framework PUBLIC -Wno-double-promotion)
    # Allow destructing objects in global scope.
    target_compile_options(framework PUBLIC -Wno-exit-time-destructors)
    # We allow to comapare floats with `==` (for templates).
    target_compile_options(framework PUBLIC -Wno-float-equal)
    # Allow constructing objects in global scope.
    target_compile_options(framework PUBLIC -Wno-global-constructors)
    # Allow anonymous structs.
    target_compile_options(framework PUBLIC -Wno-gnu-anonymous-struct)
    # Allow empty `__VA_ARGS__`.
    target_compile_options(framework PUBLIC -Wno-gnu-zero-variadic-macro-arguments)
    # No suggest braces around initialization of subobject.
    target_compile_options(framework PUBLIC -Wno-missing-braces)
    # Allow functions without preceding prototypes.
    target_compile_options(framework PUBLIC -Wno-missing-prototypes)
    # Allow anonymous unions.
    target_compile_options(framework PUBLIC -Wno-nested-anon-types)
    # Allow not having an empty line at the end of each file.
    target_compile_options(framework PUBLIC -Wno-newline-eof)
    # Allow classes with virtual functions to not have a virtual destructor.
    target_compile_options(framework PUBLIC -Wno-non-virtual-dtor)
    # Allow over-aligned types.
    target_compile_options(framework PUBLIC -Wno-over-aligned)
    # Allow padding in structures and classes (for pretty ordering).
    target_compile_options(framework PUBLIC -Wno-padded)
    # Allow different ordering in class fields and constructor initializer list.
    target_compile_options(framework PUBLIC -Wno-reorder)
    # Allow constructor parameters to match with object's fields.
    target_compile_options(framework PUBLIC -Wno-shadow-field-in-constructor)
    # Implicit conversion changes signedness.
    target_compile_options(framework PUBLIC -Wno-sign-conversion)
    # Allow switch statements to lack one or more named code of enumeration, if "default" label is provided.
    target_compile_options(framework PUBLIC -Wno-switch-enum)
    # Allow unused parameters (for virtual functions and etc.).
    target_compile_options(framework PUBLIC -Wno-unused-parameter)
    # Allow lack of out-of-line virtual method definitons.
    target_compile_options(framework PUBLIC -Wno-weak-vtables)
    # Allow `offsetof` on non-POD types.
    target_compile_options(framework PUBLIC -Wno-invalid-offsetof)
    # Allow unused const variables for interface purposes.
    target_compile_options(framework PUBLIC -Wno-unused-const-variable)
endif()

# Platform definitions.
if(WIN32)
    target_compile_definitions(framework PUBLIC KW_WINDOWS)
elseif(APPLE)
    target_compile_definitions(framework PUBLIC KW_MACOS)
elseif(UNIX)
    target_compile_definitions(framework PUBLIC KW_LINUX)
endif()

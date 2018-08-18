/**
 *  Copyright (c) 2018, 21DOGZ.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
 *  except in compliance with the License. You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is
 *  distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and limitations under the License.
 */

#pragma once

#include <kw/base/string.h>
#include <kw/debug/stacktrace.h>

#include <fmt/format.h>

#include <csignal>
#include <cstdio>

#include <kw/debug/internal/assert_impl.h>

/**
 * If the argument expression of this macro with functional form compares equal to zero (i.e., the expression is false),
 * a message is written to the standard error device and abort is called, terminating the program execution.
 *
 * \code
 * KW_ASSERT(stack.size() > 0);
 * KW_ASSERT(Math::is_power_of_2(texture_size), "Texture must be power of two!");
 * KW_ASSERT(sound_file != nullptr, "Failed to load sound file '{}'!", sound_file_path);
 * \endcode
 */
#if defined(KW_DEBUG)
#define KW_ASSERT(expr, ...) \
    do { \
        if (!(expr)) { \
            kw::assert_impl(#expr, __FILE__, __LINE__, ##__VA_ARGS__); \
            KW_RAISE_SIGTRAP(); \
        } \
    } while (false)
#else
#define KW_ASSERT(expr, ...)
#endif

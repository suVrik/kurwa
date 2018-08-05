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

#include <kw/debug/assert.h>

#if defined(KW_WINDOWS)
#define KW_RAISE_SIGTRAP() __debugbreak()
#else
#define KW_RAISE_SIGTRAP() raise(SIGTRAP)
#endif

namespace kw {
inline void assert_impl(const char* expression, const char* filename, uint32 line_number) noexcept {
    const String stacktrace = Stacktrace::get_stacktrace(1, 2);
    fprintf(stderr, "Invalid assertion:\n  %s\nin file %s:%d\n\nStacktrace:\n%s\n", expression, filename, line_number,
            stacktrace.c_str());
}

template <typename... Args>
void assert_impl(const char* expression, const char* filename, uint32 line_number, const String& message, const Args&... args) noexcept {
    const String stacktrace = Stacktrace::get_stacktrace(1, 2);
    const String full_message = fmt::format(message, args...);
    fprintf(stderr, "Invalid assertion:\n  %s\nin file %s:%d\n\nMessage:\n  %s\n\nStacktrace:\n%s\n", expression, filename, line_number,
            full_message.c_str(), stacktrace.c_str());
}
} // namespace kw

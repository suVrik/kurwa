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

#include <kw/utilities/trace.h>

namespace kw {
namespace trace_details {
void trace() {
    std::cout << std::endl;
}

template <typename Arg, typename... Args>
void trace(const Arg& argument, const Args&... args) {
    std::cout << argument << ' ';
    trace(args...);
}
} // namespace trace_details

template <typename... Args>
void tracef(const String& format_str, const Args&... args) {
    const String str = fmt::format(format_str, args...);
    std::cout << str << std::endl;
}

template <typename... Args>
void trace(const Args&... args) {
    trace_details::trace(args...);
}
} // namespace kw

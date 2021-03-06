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

#include <kw/debug/runtime_error.h>

namespace kw {
template <typename... Args>
RuntimeError::RuntimeError(const char* message, const Args&... args) noexcept
    : m_message(fmt::format(message, args...)) {
#if defined(KW_DEBUG)
    append_stacktrace();
#endif
}

template <typename... Args>
RuntimeError::RuntimeError(const String& message, const Args&... args) noexcept
    : m_message(fmt::format(message, args...)) {
#if defined(KW_DEBUG)
    append_stacktrace();
#endif
}

template <typename... Args>
RuntimeError::RuntimeError(const StringView& message, const Args&... args) noexcept
    : m_message(fmt::format(message, args...)) {
#if defined(KW_DEBUG)
    append_stacktrace();
#endif
}
} // namespace kw

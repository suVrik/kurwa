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

#include <kw/debug/runtime_error.h>
#include <kw/debug/stacktrace.h>

#if defined(KW_DEBUG)

namespace kw {
RuntimeError::RuntimeError(const char* message) noexcept
    : m_message(message) {
#if defined(KW_DEBUG)
    append_stacktrace();
#endif
}

RuntimeError::RuntimeError(const String& message) noexcept
    : m_message(message) {
#if defined(KW_DEBUG)
    append_stacktrace();
#endif
}

RuntimeError::RuntimeError(const StringView& message) noexcept
    : m_message(message) {
#if defined(KW_DEBUG)
    append_stacktrace();
#endif
}

const char* RuntimeError::what() const {
    return m_message.c_str();
}

void RuntimeError::append_stacktrace() noexcept {
    // Skip 'RuntimeError::append_stacktrace' and 'RuntimeError' constructor.
    m_message += "\n\nStacktrace:\n" + Stacktrace::get_stacktrace(2);
}
} // namespace kw

#endif

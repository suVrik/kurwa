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
#include <kw/base/string_view.h>

#include <fmt/format.h>

#include <stdexcept>
#include <utility>

namespace kw {
/**
 * This class defines the type of objects thrown as exceptions
 * to report errors that can only be detected during runtime.
 */
class RuntimeError : std::exception {
public:
    /**
     * Construct runtime error with the empty message.
     */
    RuntimeError() = default;

    /**
     * Construct runtime error with the given message.
     */
    explicit RuntimeError(const char* message) noexcept;
    explicit RuntimeError(const String& message) noexcept;
    explicit RuntimeError(const StringView& message) noexcept;

    /**
     * Construct runtime error with the given formatted message.
     * \code
     * throw RuntimeError("Failed to load file '{}'!", filename);
     * \endcode
     */
    template <typename... Args>
    explicit RuntimeError(const char* message, const Args&... args) noexcept;
    template <typename... Args>
    explicit RuntimeError(const String& message, const Args&... args) noexcept;
    template <typename... Args>
    explicit RuntimeError(const StringView& message, const Args&... args) noexcept;

    /**
     * Return error message or an empty string, if error message is not provided.
     */
    const char* what() const noexcept(noexcept(eastl::declval<std::exception>().what())) override;

private:
#if defined(KW_DEBUG)
    void append_stacktrace() noexcept;
#endif

    String m_message;
};
} // namespace kw

#include <kw/debug/internal/runtime_error_impl.h>

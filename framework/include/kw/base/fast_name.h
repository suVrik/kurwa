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

namespace kw {
/**
 * FastName is a string, that can be compared really-really quickly. The key idea behind it is that equal FastName
 * strings have equal c-string pointers and operator== basically compares these pointers. Besides this operator,
 * there's nothing special about this structure.
 * Use it in places where you need to compare strings very often. Prefer caching FastName instances, as FastName
 * constructor is kind of slow (it uses a hash map).
 */
class FastName {
public:
    /**
     * Construct FastName instance.
     */
    FastName() noexcept;
    FastName(const char* string, size_t length) noexcept;
    explicit FastName(const char* string) noexcept;
    explicit FastName(const String& string) noexcept;
    FastName(const FastName&) noexcept = default;
    FastName& operator=(const FastName&) noexcept = default;

    /**
     * Return a character at specified location 'position'.
     */
    char at(size_t position) const noexcept;
    char operator[](size_t position) const noexcept;

    /**
     * Return a pointer to the first character of a string.
     */
    const char* data() const noexcept;
    const char* c_str() const noexcept;

    /**
     * Return an iterator to the beginning.
     */
    const char* begin() const noexcept;
    const char* cbegin() const noexcept;

    /**
     * Return an iterator to the end.
     */
    const char* end() const noexcept;
    const char* cend() const noexcept;

    /**
     * Check whether the string is empty.
     */
    bool empty() const noexcept;

    /**
     * Return the number of characters.
     */
    size_t size() const noexcept;
    size_t length() const noexcept;

    /**
     * operator== and operator!= do not cost anything.
     * Other operators implement linear algorithm under the hood, which is default string implementation.
     */
    bool operator==(const FastName& another) const noexcept;
    bool operator!=(const FastName& another) const noexcept;
    bool operator<(const FastName& another) const noexcept;
    bool operator<=(const FastName& another) const noexcept;
    bool operator>(const FastName& another) const noexcept;
    bool operator>=(const FastName& another) const noexcept;

private:
    const char* m_string;
    size_t m_length;
};
} // namespace kw

namespace eastl {
template <>
struct hash<kw::FastName> {
    size_t operator()(const kw::FastName& value) const;
};
} // namespace eastl

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
#include <kw/base/types.h>

namespace kw {
/**
 * UTF-8 utilities.
 */
class Utf8Utils final {
public:
    /**
     * Return length of string as code points count.
     * Return 0 if string contains wrong utf-8 sequence.
     */
    static uint32 get_length(const String& string) noexcept;

    /**
     * Return code point with specified index.
     * Return 0 if reach end or string contains wrong utf-8 sequence.
     */
    static uint32 get_code_point_at(const String& string, uint32 index) noexcept;

    /**
     * Return next code point and move iterator to next code point.
     * Return 0 if reach end or string contains wrong utf-8 sequence.
     */
    static uint32 get_next_code_point(String::const_iterator& it, const String::const_iterator& end) noexcept;

    /**
     * Return next code point without moving iterator to next code point.
     * Return 0 if reach end or string contains wrong utf-8 sequence.
     */
    static uint32 peel_next_code_point(const String::const_iterator& it, const String::const_iterator& end) noexcept;

    /**
     * Check that string contains valid utf-8 sequences.
     */
    static bool is_valid(const String& string) noexcept;

    /**
     * Return repaired copy for string with invalid utf-8 sequences.
     * Return empty string if can't repair it.
     */
    static String repair(const String& string) noexcept;

    /**
     * Convert utf-16 string to utf-8 string.
     * Return default value if input string contains wrong utf-8 sequence.
     */
    static String to_utf8(const String16& utf16_string, const String& default_value = {}) noexcept;

    /**
     * Convert utf-32 string to utf-8 string.
     * Return default value if input string contains wrong utf-8 sequence.
     */
    static String to_utf8(const String32& utf32_string, const String& default_value = {}) noexcept;

    /**
     * Convert utf-8 string to utf-16 string.
     * Return default value if input string contains wrong utf-8 sequence.
     */
    static String16 to_utf16(const String& utf8_string, const String16& default_value = {}) noexcept;

    /**
     * Convert utf-32 string to utf-16 string.
     * Return default value if input string contains wrong utf-8 sequence.
     */
    static String16 to_utf16(const String32& utf32_string, const String16& default_value = {}) noexcept;

    /**
     * Convert utf-8 string to utf-32 string.
     * Return default value if input string contains wrong utf-8 sequence.
     */
    static String32 to_utf32(const String& utf8_string, const String32& default_value = {}) noexcept;

    /**
     * Convert utf-16 string to utf-32 string.
     * Return default value if input string contains wrong utf-8 sequence.
     */
    static String32 to_utf32(const String16& utf16_string, const String32& default_value = {}) noexcept;

    Utf8Utils() = delete;
};
} // namespace kw

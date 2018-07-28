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

#include <kw/utilities/utf8_utils.h>

#include <utf8/utf8.h>

namespace kw {
uint32 Utf8Utils::get_length(const String& string) noexcept {
    try {
        return static_cast<uint32>(utf8::distance(string.begin(), string.end()));
    } catch (const utf8::exception&) {
        return 0;
    }
}

uint32 Utf8Utils::get_code_point_at(const String& string, uint32 index) noexcept {
    try {
        auto it           = string.begin();
        auto end          = string.end();
        uint32 code_point = 0;
        for (uint32 i = 0; i < index; i++) {
            code_point = utf8::next(it, end);
        }
        return code_point;
    } catch (const utf8::exception&) {
        return 0;
    }
}

uint32 Utf8Utils::get_next_code_point(String::const_iterator& it, const String::const_iterator& end) noexcept {
    try {
        return utf8::next(it, end);
    } catch (const utf8::exception&) {
        return 0;
    }
}

uint32 Utf8Utils::peel_next_code_point(const String::const_iterator& it, const String::const_iterator& end) noexcept {
    try {
        return utf8::peek_next(it, end);
    } catch (const utf8::exception&) {
        return 0;
    }
}

bool Utf8Utils::is_valid(const String& string) noexcept {
    try {
        return utf8::is_valid(string.begin(), string.end());
    } catch (const utf8::exception&) {
        return false;
    }
}

String Utf8Utils::repair(const String& string) noexcept {
    try {
        String temp;
        utf8::replace_invalid(string.begin(), string.end(), back_inserter(temp));
        return temp;
    } catch (const utf8::exception&) {
        return {};
    }
}

String Utf8Utils::to_utf8(const String16& utf16_string, const String& default_value) noexcept {
    try {
        String temp;
        utf8::utf16to8(utf16_string.begin(), utf16_string.end(), back_inserter(temp));
        return temp;
    } catch (const utf8::exception&) {
        return default_value;
    }
}

String Utf8Utils::to_utf8(const String32& utf32_string, const String& default_value) noexcept {
    try {
        String temp;
        utf8::utf32to8(utf32_string.begin(), utf32_string.end(), back_inserter(temp));
        return temp;
    } catch (const utf8::exception&) {
        return default_value;
    }
}

String16 Utf8Utils::to_utf16(const String& utf8_string, const String16& default_value) noexcept {
    try {
        String16 temp;
        utf8::utf8to16(utf8_string.begin(), utf8_string.end(), back_inserter(temp));
        return temp;
    } catch (const utf8::exception&) {
        return default_value;
    }
}

String16 Utf8Utils::to_utf16(const String32& utf32_string, const String16& default_value) noexcept {
    try {
        String temp8;
        utf8::utf32to8(utf32_string.begin(), utf32_string.end(), back_inserter(temp8));
        String16 temp16;
        utf8::utf8to16(temp8.begin(), temp8.end(), back_inserter(temp16));
        return temp16;
    } catch (const utf8::exception&) {
        return default_value;
    }
}

String32 Utf8Utils::to_utf32(const String& utf8_string, const String32& default_value) noexcept {
    try {
        String32 temp;
        utf8::utf8to32(utf8_string.begin(), utf8_string.end(), back_inserter(temp));
        return temp;
    } catch (const utf8::exception&) {
        return default_value;
    }
}

String32 Utf8Utils::to_utf32(const String16& utf16_string, const String32& default_value) noexcept {
    try {
        String temp8;
        utf8::utf16to8(utf16_string.begin(), utf16_string.end(), back_inserter(temp8));
        String32 temp32;
        utf8::utf8to32(temp8.begin(), temp8.end(), back_inserter(temp32));
        return temp32;
    } catch (const utf8::exception&) {
        return default_value;
    }
}
} // namespace kw

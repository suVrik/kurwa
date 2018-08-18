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

#include <kw/base/fast_name.h>
#include <kw/base/hash_map.h>
#include <kw/base/types.h>
#include <kw/base/unique_ptr.h>
#include <kw/concurrency/mutex.h>

#include <cstring>

namespace kw {
namespace fast_name_details {
const char* EMPTY_STRING = "";

struct InternalHash final {
    size_t operator()(const FastName& value) const {
        // FNV-like string hash.
        auto* ptr = reinterpret_cast<const uint8*>(value.c_str());
        size_t result = 2166136261U;
        while (*ptr++ != 0) {
            result = (result * 16777619) ^ *ptr;
        }
        return result;
    }
};

struct InternalEqualTo final {
    bool operator()(const FastName& a, const FastName& b) const {
        return a.length() == b.length() && strcmp(a.c_str(), b.c_str()) == 0;
    }
};

HashMap<FastName, UniquePtr<char[]>, InternalHash, InternalEqualTo> get_database() {
    HashMap<FastName, UniquePtr<char[]>, InternalHash, InternalEqualTo> result;
    result.emplace(FastName(), UniquePtr<char[]>());
    return result;
}
} // namespace fast_name_details

FastName::FastName() noexcept
    : m_string(fast_name_details::EMPTY_STRING)
    , m_length(0) {
}

FastName::FastName(const char* string, size_t length) noexcept
    : m_string(string)
    , m_length(length) {
    using namespace fast_name_details;

    // Put the empty string at the very beginning to make the empty string constructor overload not cost anything.
    static HashMap<FastName, UniquePtr<char[]>, InternalHash, InternalEqualTo> database = get_database();
    static Mutex mutex;

    LockGuard<Mutex> lock(mutex);

    auto success = database.find(*this);
    if (success != database.end()) {
        *this = success->first;
    } else {
        auto* copy = new char[m_length + 1];
        memcpy(copy, m_string, m_length);
        copy[m_length] = '\0';

        m_string = copy;

        database.emplace(*this, UniquePtr<char[]>(copy));
    }
}

FastName::FastName(const char* string) noexcept
    : FastName(string, strlen(string)) {
}

FastName::FastName(const String& string) noexcept
    : FastName(string.c_str(), string.size()) {
}

char FastName::at(size_t position) const noexcept {
    return m_string[position];
}

char FastName::operator[](size_t position) const noexcept {
    return m_string[position];
}

const char* FastName::data() const noexcept {
    return m_string;
}

const char* FastName::c_str() const noexcept {
    return m_string;
}

const char* FastName::begin() const noexcept {
    return m_string;
}

const char* FastName::cbegin() const noexcept {
    return m_string;
}

const char* FastName::end() const noexcept {
    return m_string + m_length + 1;
}

const char* FastName::cend() const noexcept {
    return m_string + m_length + 1;
}

bool FastName::empty() const noexcept {
    return m_length == 0;
}

size_t FastName::size() const noexcept {
    return m_length;
}

size_t FastName::length() const noexcept {
    return m_length;
}

bool FastName::operator==(const FastName& another) const noexcept {
    return m_string == another.m_string;
}

bool FastName::operator!=(const FastName& another) const noexcept {
    return m_string != another.m_string;
}

bool FastName::operator<(const FastName& another) const noexcept {
    return strcmp(m_string, another.m_string) < 0;
}

bool FastName::operator<=(const FastName& another) const noexcept {
    return strcmp(m_string, another.m_string) <= 0;
}

bool FastName::operator>(const FastName& another) const noexcept {
    return strcmp(m_string, another.m_string) > 0;
}

bool FastName::operator>=(const FastName& another) const noexcept {
    return strcmp(m_string, another.m_string) >= 0;
}
} // namespace kw

namespace eastl {
size_t hash<kw::FastName>::operator()(const kw::FastName& value) const {
    return reinterpret_cast<size_t>(value.c_str());
}
} // namespace eastl

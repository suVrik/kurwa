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

#include <kw/reflection/any.h>

namespace kw {
template <typename T>
Any::Any(T&& value) noexcept
    : m_type(Type::of<eastl::decay_t<T>>()) {
    static_assert(!eastl::is_same_v<T, Any>, "Move-Constructor is required for T = Any");

    if constexpr (sizeof(T) <= sizeof(void*)) {
        typedef eastl::decay_t<T> decay_t;
        new (&m_data) decay_t(eastl::forward<T>(value));
    } else {
        m_data = new eastl::decay_t<T>(eastl::forward<T>(value));
    }
}

template <typename T, typename... Args>
void Any::emplace(Args&&... args) noexcept {
    this->~Any();

    m_type = Type::of<eastl::decay_t<T>>();
    if constexpr (sizeof(T) <= sizeof(void*)) {
        typedef eastl::decay_t<T> decay_t;
        new (&m_data) decay_t(eastl::forward<Args>(args)...);
    } else {
        m_data = new eastl::decay_t<T>(eastl::forward<Args>(args)...);
    }
}

template <typename T>
const T* Any::cast() const noexcept {
    const Type* const type = Type::of<eastl::decay_t<T>>();
    if (type == m_type) {
        if constexpr (type_details::get_size<T>() <= sizeof(void*)) {
            return reinterpret_cast<const T*>(&m_data);
        } else {
            return static_cast<const T*>(m_data);
        }
    } else {
        // No inheritance for scalar types
        if constexpr (!eastl::is_scalar<T>::value) {
            if (Pair<bool, uintptr_t> result = type->is_base_of(m_type); result.first) {
                if (type->is_small_object()) {
                    return reinterpret_cast<const T*>(reinterpret_cast<const uint8*>(&m_data) + result.second);
                } else {
                    return reinterpret_cast<const T*>(reinterpret_cast<const uint8*>(m_data) + result.second);
                }
            }
        }
    }
    return nullptr;
}

template <typename T>
T* Any::cast() noexcept {
    const Type* const type = Type::of<eastl::decay_t<T>>();
    if (type == m_type) {
        if constexpr (type_details::get_size<T>() <= sizeof(void*)) {
            return static_cast<T*>(reinterpret_cast<void*>(&m_data));
        } else {
            return static_cast<T*>(m_data);
        }
    } else {
        // No inheritance for scalar types
        if constexpr (!eastl::is_scalar<T>::value) {
            if (Pair<bool, uintptr_t> result = type->is_base_of(m_type); result.first) {
                if (m_type->is_small_object()) {
                    return reinterpret_cast<T*>(reinterpret_cast<uint8*>(&m_data) + result.second);
                } else {
                    return reinterpret_cast<T*>(reinterpret_cast<uint8*>(m_data) + result.second);
                }
            }
        }
    }
    return nullptr;
}

template <typename T>
bool Any::is_same() const noexcept {
    return m_type->is_same<T>();
}
} // namespace kw

namespace eastl {
template <>
struct hash<kw::Any> {
    size_t operator()(const kw::Any& any) const;
};
} // namespace eastl

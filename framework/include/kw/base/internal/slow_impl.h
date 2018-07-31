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

#include <kw/base/slow.h>

namespace kw {
template <typename T>
Slow<T>::~Slow() noexcept {
    if (m_is_constructed) {
        reinterpret_cast<const T*>(m_object)->~T();
    }
}

template <typename T>
Slow<T>::Slow(Slow&& original) noexcept {
    if (original.m_is_constructed) {
        new (reinterpret_cast<T*>(m_object)) T(eastl::move(original));
        m_is_constructed = true;
    }
}

template <typename T>
Slow<T>& Slow<T>::operator=(Slow&& original) noexcept {
    if (original.m_is_constructed) {
        if (m_is_constructed) {
            *reinterpret_cast<const T*>(m_object) = eastl::move(original);
        } else {
            new (reinterpret_cast<T*>(m_object)) T(eastl::move(original));
            m_is_constructed = true;
        }
    } else {
        reinterpret_cast<const T*>(m_object)->~T();
        m_is_constructed = false;
    }

    return *this;
}

template <typename T>
template <typename... Arguments>
void Slow<T>::construct(Arguments&&... args) noexcept(eastl::is_nothrow_constructible<T>::value) {
    KW_ASSERT(!m_is_constructed, "The object is already constructed!");

    new (reinterpret_cast<T*>(m_object)) T(eastl::forward<Arguments>(args)...);

    m_is_constructed = true;
}

template <typename T>
inline T& Slow<T>::operator*() noexcept {
    KW_ASSERT(m_is_constructed, "The object is not yet constructed!");

    return *reinterpret_cast<T*>(m_object);
}

template <typename T>
inline const T& Slow<T>::operator*() const noexcept {
    KW_ASSERT(m_is_constructed, "The object is not yet constructed!");

    return *reinterpret_cast<const T*>(m_object);
}

template <typename T>
inline T& Slow<T>::operator->() noexcept {
    KW_ASSERT(m_is_constructed, "The object is not yet constructed!");

    return *reinterpret_cast<T*>(m_object);
}

template <typename T>
inline const T& Slow<T>::operator->() const noexcept {
    KW_ASSERT(m_is_constructed, "The object is not yet constructed!");

    return *reinterpret_cast<const T*>(m_object);
}

template <typename T>
inline bool Slow<T>::is_constructed() const noexcept {
    return m_is_constructed;
}
} // namespace kw

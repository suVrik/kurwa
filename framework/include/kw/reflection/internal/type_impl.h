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

#include <kw/reflection/type.h>

namespace kw {
namespace type_details {
template <class T>
using operator_equals_t = decltype(eastl::declval<const T&>() == eastl::declval<const T&>());

template <class T>
using operator_less_t = decltype(eastl::declval<const T&>() < eastl::declval<const T&>());

template <typename T>
void register_parents(Vector<Type::Parent>& parents) {
    // All base classes are registered. Nothing to do.
}

template <typename T, typename Base, typename... Bases>
void register_parents(Vector<Type::Parent>& parents) {
    static_assert(eastl::is_base_of<Base, T>::value, "Invalid list of base classes!");

    parents.push_back({ Type::of<Base>(), static_cast<const Base*>(reinterpret_cast<const T*>(nullptr)) });

    register_parents<T, Bases...>(parents);
}
} // namespace type_details

template <typename T>
const Type* Type::of() {
    // TODO: check how it looks in assembly
    if constexpr (eastl::is_same_v<T, eastl::decay_t<T>>) {
        static Type type(reinterpret_cast<const T*>(nullptr));
        return &type;
    } else {
        return of<eastl::decay_t<T>>();
    }
}

template <typename T, typename... Bases>
void Type::register_parents() {
    auto type = const_cast<Type*>(Type::of<T>());
    type->m_parents.reserve(sizeof...(Bases));
    type_details::register_parents<T, Bases...>(type->m_parents);
}

template <typename T>
bool Type::is_same() const {
    return this == Type::of<T>();
}

template <typename T>
bool Type::is_base_of() const {
    return is_base_of(Type::of<T>());
}

template <typename T>
bool Type::is_inherited_from() const {
    return is_inherited_from(Type::of<T>());
}

template <typename T>
Type::Type(const T* dummy)
    : m_type_info(typeid(T))
    , m_size(sizeof(T)) {
    if constexpr (sizeof(T) > sizeof(void*)) {
        m_destructor = [](void* value) { delete static_cast<T*>(value); };
    } else {
        if constexpr (eastl::is_destructible<T>()) {
            m_destructor = [](void* value) { reinterpret_cast<T*>(&value)->~T(); };
        } else {
            m_destructor = [](void*) {};
        }
    }

    // It could look really nice and short, if I would put 'if constexpr' inside of lambda, but it doesn't work.
    if constexpr (sizeof(T) > sizeof(void*)) {
        if constexpr (eastl::is_detected_v<type_details::operator_equals_t, T>) {
            if constexpr (eastl::is_detected_v<type_details::operator_less_t, T>) {
                m_comparator = [](const void* a, const void* b) {
                    const T* const ta = reinterpret_cast<const T*>(a);
                    const T* const tb = reinterpret_cast<const T*>(b);
                    return *ta == *tb ? 0 : (*ta < *tb ? -1 : 1);
                };
            } else {
                m_comparator = [](const void* a, const void* b) {
                    return *reinterpret_cast<const T*>(a) == *reinterpret_cast<const T*>(b) ? 0 : -1;
                };
            }
        } else {
            if constexpr (eastl::is_detected_v<type_details::operator_less_t, T>) {
                m_comparator = [](const void* a, const void* b) {
                    return *reinterpret_cast<const T*>(a) < *reinterpret_cast<const T*>(b) ? -1 : 1;
                };
            } else {
                m_comparator = [](const void*, const void*) { return -1; };
            }
        }
    } else {
        if constexpr (eastl::is_detected_v<type_details::operator_equals_t, T>) {
            if constexpr (eastl::is_detected_v<type_details::operator_less_t, T>) {
                m_comparator = [](const void* a, const void* b) {
                    const T* const ta = reinterpret_cast<const T*>(&a);
                    const T* const tb = reinterpret_cast<const T*>(&b);
                    return *ta == *tb ? 0 : (*ta < *tb ? -1 : 1);
                };
            } else {
                m_comparator = [](const void* a, const void* b) {
                    return *reinterpret_cast<const T*>(&a) == *reinterpret_cast<const T*>(&b) ? 0 : -1;
                };
            }
        } else {
            if constexpr (eastl::is_detected_v<type_details::operator_less_t, T>) {
                m_comparator = [](const void* a, const void* b) {
                    return *reinterpret_cast<const T*>(&a) < *reinterpret_cast<const T*>(&b) ? -1 : 1;
                };
            } else {
                m_comparator = [](const void*, const void*) { return -1; };
            }
        }
    }
}
} // namespace kw

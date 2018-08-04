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

template <class T>
using hash_t = decltype(eastl::hash<T>());

// is_virtual_base_of implementation from boost library
// https://github.com/S2E/s2e-old/blob/master/stp/src/boost/type_traits/is_virtual_base_of.hpp

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4584)
#elif defined(__GNUC__)
#pragma GCC system_header
#endif

template <typename Base, typename Derived, typename tag>
struct is_virtual_base_of_impl {
    static constexpr bool value = false;
};

template <typename Base, typename Derived>
struct is_virtual_base_of_impl<Base, Derived, eastl::true_type> {
    struct X : Derived, virtual Base {
        X();
        X(const X&);
        X& operator=(const X&);
        ~X() throw();
    };

    struct Y : Derived {
        Y();
        Y(const Y&);
        Y& operator=(const Y&);
        ~Y() throw();
    };

    static constexpr bool value = sizeof(X) == sizeof(Y);
};

template <typename Base, typename Derived>
struct is_virtual_base_of {
    static constexpr bool tag_value = eastl::is_base_of<Base, Derived>::value && !eastl::is_same_v<Base, Derived>;
    static constexpr bool value = is_virtual_base_of_impl<Base, Derived, eastl::integral_constant<bool, tag_value>>::value;
};

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

template <typename T>
void register_parents(Vector<Type::Parent>& parents) {
    // All base classes are registered. Nothing to do.
}

template <typename T, typename Base, typename... Bases>
void register_parents(Vector<Type::Parent>& parents) {
    static_assert(eastl::is_base_of<Base, T>::value, "Invalid list of base classes!");
    static_assert(!is_virtual_base_of<Base, T>::value, "Virtual inheritance is not yet supported!");

    // '1' because nullptr doesn't work with inheritance.
    parents.push_back({ Type::of<eastl::decay_t<Base>>(), reinterpret_cast<uintptr_t>(static_cast<const Base*>(reinterpret_cast<const T*>(1))) - 1 });

    register_parents<T, Bases...>(parents);
}

template <typename T>
constexpr size_t get_size() {
    if constexpr (!eastl::is_same_v<T, void>) {
        return sizeof(T);
    }
    return 0;
}
} // namespace type_details

template <typename T>
const Type* Type::of() noexcept {
    if constexpr (eastl::is_same_v<T, eastl::decay_t<T>>) {
        static Type type(static_cast<const T*>(nullptr)); // Dummy parameter.
        return &type;
    } else {
        return Type::of<eastl::decay_t<T>>();
    }
}

template <typename T, typename... Bases>
void Type::register_parents() noexcept {
    auto type = const_cast<Type*>(Type::of<eastl::decay_t<T>>());
    type->m_parents.reserve(sizeof...(Bases));
    type_details::register_parents<T, Bases...>(type->m_parents);
}

template <typename T>
bool Type::is_same() const noexcept {
    return this == Type::of<eastl::decay_t<T>>();
}

template <typename T>
Pair<bool, uintptr_t> Type::is_base_of() const noexcept {
    return is_base_of(Type::of<eastl::decay_t<T>>());
}

template <typename T>
Pair<bool, uintptr_t> Type::is_inherited_from() const noexcept {
    return is_inherited_from(Type::of<eastl::decay_t<T>>());
}

template <typename T>
Type::Type(const T* dummy) noexcept
    : m_type_info(typeid(T))
    , m_size(type_details::get_size<T>()) {
    if constexpr (eastl::is_default_constructible_v<T>) {
        if constexpr (type_details::get_size<T>() > sizeof(void*)) {
            m_default_constructor = [](void** value) noexcept {
                *static_cast<T**>(reinterpret_cast<void*>(value)) = new T();
            };
        } else {
            m_default_constructor = [](void** value) noexcept {
                new (static_cast<T*>(reinterpret_cast<void*>(value))) T();
            };
        }
    } else {
        m_default_constructor = nullptr;
    }

    if constexpr (type_details::get_size<T>() > sizeof(void*)) {
        m_destructor = [](void* value) noexcept {
            delete static_cast<T*>(value);
        };

        if constexpr (eastl::is_detected_v<type_details::operator_equals_t, T>) {
            if constexpr (eastl::is_detected_v<type_details::operator_less_t, T>) {
                m_comparator = [](const void* a, const void* b) noexcept {
                    const T* const ta = static_cast<const T*>(a);
                    const T* const tb = static_cast<const T*>(b);
                    return *ta == *tb ? 0 : (*ta < *tb ? -1 : 1);
                };
            } else {
                m_comparator = [](const void* a, const void* b) noexcept {
                    return *static_cast<const T*>(a) == *static_cast<const T*>(b) ? 0 : -1;
                };
            }
        } else {
            if constexpr (eastl::is_detected_v<type_details::operator_less_t, T>) {
                m_comparator = [](const void* a, const void* b) noexcept {
                    return *static_cast<const T*>(a) < *static_cast<const T*>(b) ? -1 : 1;
                };
            } else {
                m_comparator = [](const void*, const void*) noexcept {
                    return -1;
                };
            }
        }
    } else {
        if constexpr (eastl::is_destructible<T>()) {
            m_destructor = [](void* value) noexcept {
                static_cast<T*>(reinterpret_cast<void*>(&value))->~T();
            };
        } else {
            m_destructor = [](void*) noexcept {};
        }

        if constexpr (eastl::is_detected_v<type_details::operator_equals_t, T>) {
            if constexpr (eastl::is_detected_v<type_details::operator_less_t, T>) {
                m_comparator = [](const void* a, const void* b) noexcept {
                    const T* const ta = static_cast<const T*>(reinterpret_cast<const void*>(&a));
                    const T* const tb = static_cast<const T*>(reinterpret_cast<const void*>(&b));
                    return *ta == *tb ? 0 : (*ta < *tb ? -1 : 1);
                };
            } else {
                m_comparator = [](const void* a, const void* b) noexcept {
                    return *static_cast<const T*>(reinterpret_cast<const void*>(&a)) == *static_cast<const T*>(reinterpret_cast<const void*>(&b)) ? 0 : -1;
                };
            }
        } else {
            if constexpr (eastl::is_same_v<T, void>) {
                // All void types are considered equal.
                m_comparator = [](const void*, const void*) noexcept {
                    return 0;
                };
            } else if constexpr (eastl::is_detected_v<type_details::operator_less_t, T>) {
                m_comparator = [](const void* a, const void* b) noexcept {
                    return *static_cast<const T*>(reinterpret_cast<const void*>(&a)) < *static_cast<const T*>(reinterpret_cast<const void*>(&b)) ? -1 : 1;
                };
            } else {
                m_comparator = [](const void*, const void*) noexcept {
                    return -1;
                };
            }
        }
    }

    if constexpr (eastl::is_detected_exact_v<size_t, type_details::hash_t, T>) {
        if constexpr (type_details::get_size<T>() > sizeof(void*)) {
            m_hash = [](const void* value) noexcept->size_t {
                return eastl::hash<T>(*static_cast<const T*>(value));
            };
        } else {
            m_hash = [](const void* value) noexcept->size_t {
                return eastl::hash<T>(*reinterpret_cast<const T*>(&value));
            };
        }
    } else {
        m_hash = [](const void* value) noexcept->size_t {
            KW_ASSERT("Object of type '{}' doesn't have a hash function defined!", typeid(T).name());
            return reinterpret_cast<size_t>(value);
        };
    }

    if constexpr (eastl::is_pointer<T>::value) {
        m_without_pointer = Type::of<eastl::remove_pointer_t<T>>();
    } else {
        m_without_pointer = nullptr;
    }
}
} // namespace kw

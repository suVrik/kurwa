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

#include <kw/reflection/reflection.h>

namespace kw {
namespace reflection_details {
extern HashMap<const Type*, const Reflection*> reflections;
} // namespace reflection_details

template <typename T>
Reflection* Reflection::add_reflection() {
    using namespace reflection_details;

    if constexpr (eastl::is_same_v<T, eastl::decay_t<T>>) {
        const Type* type = Type::of<T>(); // 'T' is already decayed.

        static Reflection reflection(type);
        auto [iterator, success] = reflections.emplace(type, &reflection);

        if (success) {
            KW_ASSERT(Reflection::of<T>() != nullptr,
                      "It looks like you were trying to access type's '{}' reflection using template 'of' method "
                      "before you actually added it!",
                      type->get_name());

            return &reflection;
        }

        // nullptr means that the given type is already added
        return nullptr;
    } else {
        return Reflection::add_reflection<eastl::decay_t<T>>();
    }
}

template <typename T>
const Reflection* Reflection::of() noexcept {
    if constexpr (eastl::is_same_v<T, eastl::decay_t<T>>) {
        static const Reflection* reflection = [] {
            auto result = reflection_details::reflections.find(Type::of<eastl::decay_t<T>>());
            if (result != reflection_details::reflections.end()) {
                return result->second;
            }
            return static_cast<const Reflection*>(nullptr);
        }();
        return reflection;
    } else {
        return Reflection::of<eastl::decay_t<T>>();
    }
}

template <typename T>
Reflection::Field* Reflection::add_field(const FastName& name, uintptr_t offset) noexcept {
    const Type* type = Type::of<eastl::add_pointer_t<eastl::decay_t<T>>>();
    Field* field = reflection_details::add_field(type, name, offset);
    m_fields.push_back(field);
    return field;
}

template <typename T>
Any Reflection::Field::get(const T& object) const noexcept {
    return Any(m_type, static_cast<const void*>(reinterpret_cast<const uint8*>(&object) + m_offset));
}

template <typename T>
bool Reflection::Field::is_same() const noexcept {
    return m_type->remove_pointer()->is_same<T>();
}

template <typename ObjectType, typename... Arguments>
Any Reflection::Method::operator()(const ObjectType& object, Arguments&&... arguments) const noexcept(false) {
    return m_method(object, eastl::forward<Arguments>(arguments)...);
}

template <typename... Arguments>
Any Reflection::Method::operator()(const Any& object, Arguments&&... arguments) const noexcept(false) {
    return m_method(object, eastl::forward<Arguments>(arguments)...);
}

} // namespace kw

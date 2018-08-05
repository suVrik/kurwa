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

#include <kw/reflection/type.h>

namespace kw {
const std::type_info& Type::get_type_info() const noexcept {
    return m_type_info;
}

size_t Type::get_size() const noexcept {
    return m_size;
}

const char* Type::get_name() const noexcept {
    return m_type_info.name();
}

const Vector<Type::Parent>& Type::get_parents() const noexcept {
    return m_parents;
}

Type::default_constructor_t Type::get_default_constructor() const noexcept {
    return m_default_constructor;
}

Type::destructor_t Type::get_destructor() const noexcept {
    return m_destructor;
}

Type::comparator_t Type::get_comparator() const noexcept {
    return m_comparator;
}

Type::hash_t Type::get_hash() const noexcept {
    return m_hash;
}

Type::Container Type::get_container() const noexcept {
    return m_container_type;
}

const Vector<const Type*>& Type::get_template_arguments() const noexcept {
    return m_template_arguments;
}

bool Type::is_small_object() const noexcept {
    return m_size < sizeof(void*);
}

bool Type::is_pointer() const noexcept {
    return m_without_pointer != nullptr;
}

const Type* Type::remove_pointer() const noexcept {
    return m_without_pointer;
}

Pair<bool, uintptr_t> Type::is_base_of(const Type* type) const noexcept {
    return type->is_inherited_from(this);
}

Pair<bool, uintptr_t> Type::is_inherited_from(const Type* type) const noexcept {
    for (const Parent& base : m_parents) {
        if (base.type == type) {
            return { true, base.offset };
        }
        if (Pair<bool, uintptr_t> result = base.type->is_inherited_from(type); result.first) {
            return { true, result.second + base.offset };
        }
    }
    return { false, 0 };
}
} // namespace kw
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
const std::type_info& Type::get_type_info() const {
    return m_type_info;
}

size_t Type::get_size() const {
    return m_size;
}

const char* Type::get_name() const {
    return m_type_info.name();
}

const Vector<Type::Parent>& Type::get_parents() const {
    return m_parents;
}

Type::destructor_t Type::get_destructor() const {
    return m_destructor;
}

Type::comparator_t Type::get_comparator() const {
    return m_comparator;
}

bool Type::is_small_object() const {
    return m_size < sizeof(void*);
}

bool Type::is_base_of(const Type* type) const {
    return type->is_inherited_from(this);
}

bool Type::is_inherited_from(const Type* type) const {
    for (const Parent& base : m_parents) {
        if (base.type == type) {
            return true;
        }
        if (base.type->is_inherited_from(type)) {
            return true;
        }
    }
    return false;
}
} // namespace kw
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

#include <kw/reflection/any.h>

namespace kw {
Any::Any() noexcept
    : m_type(Type::of<void>())
    , m_data(nullptr) {
}

Any::Any(const Type* type) noexcept
    : m_type(type) {
    Type::default_constructor_t constructor = m_type->get_default_constructor();

    KW_ASSERT(constructor != nullptr, "Type '{}' must have default constructor for such Any initialization!", type->get_name());

    constructor(&m_data);
}

Any::Any(Any&& original) noexcept
    : m_type(original.m_type)
    , m_data(original.m_data) {
    original.m_type = Type::of<void>();
    original.m_data = nullptr;
}

Any::~Any() noexcept {
    m_type->get_destructor()(m_data);
}

Any& Any::operator=(Any&& original) noexcept {
    this->~Any();

    m_type          = original.m_type;
    m_data          = original.m_data;
    original.m_type = Type::of<void>();
    original.m_data = nullptr;

    return *this;
}

bool Any::operator==(const Any& another) const noexcept {
    return m_type->get_comparator()(m_data, another.m_data) == 0;
}

bool Any::operator!=(const Any& another) const noexcept {
    return m_type->get_comparator()(m_data, another.m_data) != 0;
}

bool Any::operator<(const Any& another) const noexcept {
    return m_type->get_comparator()(m_data, another.m_data) == -1;
}

bool Any::operator>(const Any& another) const noexcept {
    return m_type->get_comparator()(m_data, another.m_data) == 1;
}

bool Any::operator<=(const Any& another) const noexcept {
    return m_type->get_comparator()(m_data, another.m_data) <= 0;
}

bool Any::operator>=(const Any& another) const noexcept {
    return m_type->get_comparator()(m_data, another.m_data) >= 0;
}

const Type* Any::get_type() const {
    return m_type;
}

bool Any::is_base_of(const Type* type) const noexcept {
    return m_type->is_base_of(type).first;
}

bool Any::is_inherited_from(const Type* type) const noexcept {
    return m_type->is_inherited_from(type).first;
}
} // namespace kw

namespace eastl {
size_t hash<kw::Any>::operator()(const kw::Any& any) const {
    return any.get_type()->get_hash()(any.m_data);
}
} // namespace eastl

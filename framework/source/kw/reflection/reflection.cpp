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

#include <kw/base/function.h>
#include <kw/base/list.h>
#include <kw/reflection/reflection.h>

namespace kw {
namespace reflection_details {
HashMap<const Type*, const Reflection*> reflections;

Reflection::Meta* add_meta(const FastName& name, Any&& value) {
    static List<Reflection::Meta> meta_database;
    meta_database.push_back(Reflection::Meta(name, eastl::move(value)));
    return &meta_database.back();
}

Reflection::Field* add_field(const Type* pointer_type, const FastName& name, uintptr_t offset) {
    static List<Reflection::Field> field_database;
    field_database.push_back(Reflection::Field(pointer_type, name, offset));
    return &field_database.back();
}
} // namespace reflection_details

const Reflection* Reflection::of(const Type* type) noexcept {
    auto result = reflection_details::reflections.find(type);
    if (result != reflection_details::reflections.end()) {
        return result->second;
    }
    return nullptr;
}

const Reflection* Reflection::of(const Any& any) noexcept {
    return Reflection::of(any.get_type());
}

const Reflection::Field* Reflection::get_field(const FastName& name) const noexcept {
    for (const Field* field : m_fields) {
        if (field->m_name == name) {
            return field;
        }
    }
    return nullptr;
}

const Vector<const Reflection::Field*>& Reflection::get_fields() const noexcept {
    return m_fields;
}

const Reflection::Meta* Reflection::get_meta(const FastName& name) const {
    for (const Meta* meta : m_meta) {
        if (meta->m_name == name) {
            return meta;
        }
    }
    return nullptr;
}

const Vector<const Reflection::Meta*>& Reflection::get_meta() const {
    return m_meta;
}

void Reflection::add_meta(const FastName& name, Any&& value) {
    m_meta.push_back(reflection_details::add_meta(name, eastl::move(value)));
}

const Type* Reflection::get_type() const {
    return m_type;
}

Reflection::Reflection(const Type* type)
    : m_type(type) {
    Function<void(const Type*, uintptr_t)> inherit_fields_and_meta;

    inherit_fields_and_meta = [this, &inherit_fields_and_meta](const Type* parent_type, uintptr_t offset) {
        const Reflection* parent_reflection = Reflection::of(parent_type);
        if (parent_reflection != nullptr) {
            const Vector<const Field*>& parent_fields = parent_reflection->get_fields();
            if (offset == 0) {
                m_fields.insert(m_fields.end(), parent_fields.begin(), parent_fields.end());
            } else {
                for (const Reflection::Field* field : parent_fields) {
                    const uintptr_t field_offset = offset + field->m_offset;
                    m_fields.push_back(reflection_details::add_field(field->m_type, field->m_name, field_offset));
                }
            }

            const Vector<const Meta*>& parent_meta = parent_reflection->get_meta();
            m_meta.insert(m_meta.end(), parent_meta.begin(), parent_meta.end());
        }

        const Vector<Type::Parent>& parents = parent_type->get_parents();
        for (const Type::Parent& parent : parents) {
            inherit_fields_and_meta(parent.type, offset + parent.offset);
        }
    };

    const Vector<Type::Parent>& parents = m_type->get_parents();
    for (const Type::Parent& parent : parents) {
        inherit_fields_and_meta(parent.type, parent.offset);
    }
}

Reflection::Field::Field(const Type* type, const FastName& name, uintptr_t offset)
    : m_type(type)
    , m_name(name)
    , m_offset(offset) {
}

const Type* Reflection::Field::get_type() const {
    return m_type;
}

const FastName& Reflection::Field::get_name() const {
    return m_name;
}

Any Reflection::Field::get(const Any& object) const {
    if (object.get_type()->is_small_object()) {
        return Any(m_type, static_cast<const void*>(reinterpret_cast<const uint8*>(&object.get_raw_data()) + m_offset));
    }
    return Any(m_type, static_cast<const void*>(reinterpret_cast<const uint8*>(object.get_raw_data()) + m_offset));
}

const Reflection::Meta* Reflection::Field::get_meta(const FastName& name) const {
    for (const Meta* meta : m_meta) {
        if (meta->m_name == name) {
            return meta;
        }
    }
    return nullptr;
}

const Vector<const Reflection::Meta*>& Reflection::Field::get_meta() const {
    return m_meta;
}

void Reflection::Field::add_meta(const FastName& name, Any&& value) {
    m_meta.push_back(reflection_details::add_meta(name, eastl::move(value)));
}

const FastName& Reflection::Meta::get_name() const {
    return m_name;
}

const Any& Reflection::Meta::get_value() const {
    return m_value;
}

Reflection::Meta::Meta(const FastName& name, Any&& value)
    : m_name(name)
    , m_value(eastl::move(value)) {
}
} // namespace kw

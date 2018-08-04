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

Reflection::Field* add_field(const Type* pointer_type, const FastName& name, uintptr_t offset) noexcept {
    static List<Reflection::Field> field_database;
    field_database.push_back(Reflection::Field(pointer_type, name, offset));
    return &field_database.back();
}

Reflection::Method* add_method(const FastName& name, AnyFunction&& function) noexcept {
    static List<Reflection::Method> method_database;
    method_database.push_back(Reflection::Method(name, eastl::move(function)));
    return &method_database.back();
}

Reflection::Meta* add_meta(const FastName& name, Any&& value) noexcept {
    static List<Reflection::Meta> meta_database;
    meta_database.push_back(Reflection::Meta(name, eastl::move(value)));
    return &meta_database.back();
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
        if (field->get_name() == name) {
            return field;
        }
    }
    return nullptr;
}

const Vector<const Reflection::Field*>& Reflection::get_fields() const noexcept {
    return m_fields;
}

const Reflection::Method* Reflection::get_method(const FastName& name) const noexcept {
    for (const Method* method : m_methods) {
        if (method->get_name() == name) {
            return method;
        }
    }
    return nullptr;
}

const Vector<const Reflection::Method*>& Reflection::get_methods() const noexcept {
    return m_methods;
}

Reflection::Method* Reflection::add_method(const FastName& name, AnyFunction&& function) noexcept {
    Method* method = reflection_details::add_method(name, eastl::move(function));
    m_methods.push_back(method);
    return method;
}

const Reflection::Meta* Reflection::get_meta(const FastName& name) const noexcept {
    for (const Meta* meta : m_meta) {
        if (meta->get_name() == name) {
            return meta;
        }
    }
    return nullptr;
}

const Vector<const Reflection::Meta*>& Reflection::get_meta() const noexcept {
    return m_meta;
}

void Reflection::add_meta(const FastName& name, Any&& value) noexcept {
    m_meta.push_back(reflection_details::add_meta(name, eastl::move(value)));
}

const Type* Reflection::get_type() const noexcept {
    return m_type;
}

Reflection::Reflection(const Type* type) noexcept
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
                    const uintptr_t field_offset = offset + field->get_offset();
                    m_fields.push_back(reflection_details::add_field(field->get_type(), field->get_name(), field_offset));
                }
            }

            const Vector<const Method*>& parent_methods = parent_reflection->get_methods();
            m_methods.insert(m_methods.end(), parent_methods.begin(), parent_methods.end());

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

#if defined(KW_DEBUG)
    for (uint32 i = 0; i < m_fields.size(); i++) {
        for (uint32 j = i + 1; j < m_fields.size(); j++) {
            KW_ASSERT(m_fields[i]->get_name() != m_fields[j]->get_name(), "Fields with the same name '{}' in reflection of type '{}'!",
                      m_fields[i]->get_name().c_str(), m_type->get_name());
        }
    }

    for (uint32 i = 0; i < m_methods.size(); i++) {
        for (uint32 j = i + 1; j < m_methods.size(); j++) {
            KW_ASSERT(m_methods[i]->get_name() != m_methods[j]->get_name(), "Methods with the same name '{}' in reflection of type '{}'!",
                      m_methods[i]->get_name().c_str(), m_type->get_name());
        }
    }
#endif
}

const FastName& Reflection::Meta::get_name() const noexcept {
    return m_name;
}

const Any& Reflection::Meta::get_value() const noexcept {
    return m_value;
}

Reflection::Meta::Meta(const FastName& name, Any&& value) noexcept
    : m_name(name)
    , m_value(eastl::move(value)) {
}

const Type* Reflection::Field::get_type() const noexcept {
    return m_type->remove_pointer();
}

const FastName& Reflection::Field::get_name() const noexcept {
    return m_name;
}

Any Reflection::Field::get(const Any& object) const noexcept {
    if (object.get_type()->is_small_object()) {
        return Any(m_type, static_cast<const void*>(reinterpret_cast<const uint8*>(&object.get_raw_data()) + m_offset));
    }
    return Any(m_type, static_cast<const void*>(reinterpret_cast<const uint8*>(object.get_raw_data()) + m_offset));
}

const Reflection::Meta* Reflection::Field::get_meta(const FastName& name) const noexcept {
    for (const Meta* meta : m_meta) {
        if (meta->get_name() == name) {
            return meta;
        }
    }
    return nullptr;
}

const Vector<const Reflection::Meta*>& Reflection::Field::get_meta() const noexcept {
    return m_meta;
}

void Reflection::Field::add_meta(const FastName& name, Any&& value) noexcept {
    m_meta.push_back(reflection_details::add_meta(name, eastl::move(value)));
}

uintptr_t Reflection::Field::get_offset() const noexcept {
    return m_offset;
}

Reflection::Field::Field(const Type* type, const FastName& name, uintptr_t offset) noexcept
    : m_type(type)
    , m_name(name)
    , m_offset(offset) {
    KW_ASSERT(type->is_pointer());
}

const FastName& Reflection::Method::get_name() const noexcept {
    return m_name;
}

const Reflection::Meta* Reflection::Method::get_meta(const FastName& name) const noexcept {
    for (const Meta* meta : m_meta) {
        if (meta->get_name() == name) {
            return meta;
        }
    }
    return nullptr;
}

const Vector<const Reflection::Meta*>& Reflection::Method::get_meta() const noexcept {
    return m_meta;
}

void Reflection::Method::add_meta(const FastName& name, Any&& value) noexcept {
    m_meta.push_back(reflection_details::add_meta(name, eastl::move(value)));
}

Reflection::Method::Method(const FastName& name, AnyFunction&& method) noexcept
    : m_name(name)
    , m_method(eastl::move(method)) {
}
} // namespace kw

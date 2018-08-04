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

#include <kw/base/fast_name.h>
#include <kw/base/hash_map.h>
#include <kw/base/string.h>
#include <kw/reflection/any.h>
#include <kw/reflection/any_function.h>

namespace kw {
/**
 * Reflection of specific object `T` is a set of its reflectable fields and meta fields.
 *
 * TODO(another pull request): better description
 */
class Reflection {
public:
    /**
     * Field reflection represents an actual field in object (i.e. we have an object Cat and it has a field
     * called `name`, reflection of this field knows its type, address relative to field's object and name).
     * Fields are inherited.
     *
     * TODO(another pull request): better description
     */
    class Field;

    /**
     * TODO
     */
    class Method;

    /**
     * Meta is just some information that can be stored in object, field or method reflection. Meta is inherited.
     *
     * TODO(another pull request): better description
     */
    class Meta;

    /**
     * Create reflection of the given type `T`. Return added reflection. If reflection is already added, return nullptr.
     *
     * For each unique `T` this method must be called once.
     *
     * Do not use template `of` method before calling this method (because then it caches nullptr Reflection).
     *
     * If `T` has parents, `Type::register_parents<T, ...>` must be called before this method (and its parents too)
     * otherwise neither fields nor meta will not be inherited.
     */
    template <typename T>
    static Reflection* add_reflection();

    /**
     * Return reflection of the given type `T`. If reflection for the given type doesn't exist, nullptr is returned.
     *
     * Keep in mind, that this overload of `of` method is the fastest one, because it's based on static cached
     * variable, while other overloads are implemented using hash map search.
     *
     * WARNING: Must be called after `add_reflection<T>()`, because this method caches a value from reflection hash map.
     */
    template <typename T>
    static const Reflection* of() noexcept;

    /**
     * Return reflection of the given type `type`. If reflection for the given type doesn't exist, nullptr is returned.
     */
    static const Reflection* of(const Type* type) noexcept;

    /**
     * Return reflection of a type stored in the given `any`. If reflection for the given type doesn't exist,
     * nullptr is returned.
     */
    static const Reflection* of(const Any& any) noexcept;

    /**
     * Return field with the given `name`, stored in reflection. If the field with the given name doesn't exist,
     * return nullptr.
     */
    const Field* get_field(const FastName& name) const noexcept;

    /**
     * Return vector of fields stored in this reflection (including inherited fields).
     */
    const Vector<const Field*>& get_fields() const noexcept;

    /**
     * Add field with the given type `T` and `name` to reflection. When choosing `offset`,
     * take parent classes and aligning into account.
     */
    template <typename T>
    Field* add_field(const FastName& name, uintptr_t offset) noexcept;

    /**
     * TODO
     */
    const Method* get_method(const FastName& name) const noexcept;

    /**
     * TODO
     */
    const Vector<const Method*>& get_methods() const noexcept;

    /**
     * TODO
     */
    Method* add_method(const FastName& name, AnyFunction&& function) noexcept;

    /**
     * Return meta field with the given `name` for this object reflection.
     */
    const Meta* get_meta(const FastName& name) const noexcept;

    /**
     * Return all meta fields for this object reflection.
     */
    const Vector<const Meta*>& get_meta() const noexcept;

    /**
     * Add meta field to this object reflection.
     */
    void add_meta(const FastName& name, Any&& value) noexcept;

    /**
     * Return type of the reflected object.
     */
    const Type* get_type() const noexcept;

private:
    explicit Reflection(const Type* type) noexcept;

    Vector<const Field*> m_fields;
    Vector<const Method*> m_methods;
    Vector<const Meta*> m_meta;
    const Type* m_type;
};

namespace reflection_details {
extern Reflection::Field* add_field(const Type* pointer_type, const FastName& name, uintptr_t offset) noexcept;
extern Reflection::Method* add_method(const FastName& name, AnyFunction&& function) noexcept;
extern Reflection::Meta* add_meta(const FastName& name, Any&& value) noexcept;
} // namespace reflection_details

/**
 * Field reflection represents an actual field in object (i.e. we have an object Cat and it has a field called `name`,
 * reflection of this field knows its type, address relative to field's object and name).
 */
class Reflection::Field {
public:
    /**
     * Return type of the field. Always a pointer.
     */
    const Type* get_type() const noexcept;

    /**
     * Return name of the field.
     */
    const FastName& get_name() const noexcept;

    /**
     * Return a pointer to a field in the given `object` (which must have type of parent reflection,
     * which is not present in this class for optimization reasons).
     */
    Any get(const Any& object) const noexcept;
    template <typename T>
    Any get(const T& object) const noexcept;

    /**
     * Return meta field with the given `name` for this field reflection.
     */
    const Meta* get_meta(const FastName& name) const noexcept;

    /**
     * Return all meta fields for this field reflection.
     */
    const Vector<const Meta*>& get_meta() const noexcept;

    /**
     * Add meta field to this field reflection.
     */
    void add_meta(const FastName& name, Any&& value) noexcept;

    /**
     * Return true if the field has the given type `T`. Otherwise return false.
     *
     * A shortcut for `field->get_type()->is_same<T>()`.
     */
    template <typename T>
    bool is_same() const noexcept;

private:
    Field(const Type* type, const FastName& name, uintptr_t offset) noexcept;

    Vector<const Meta*> m_meta;
    const Type* m_type;
    FastName m_name;
    uintptr_t m_offset;

    // Allow Reflection to access offset (for field inheritance):
    friend class Reflection;

    // Allow this function to create Field:
    friend Field* reflection_details::add_field(const Type*, const FastName&, uintptr_t) noexcept;
};

/**
 * TODO
 */
class Reflection::Method {
public:
    /**
     * Return name of the field.
     */
    const FastName& get_name() const noexcept;

    // TODO
    template <typename ObjectType, typename... Arguments>
    Any operator()(const ObjectType& object, Arguments&&... arguments) const noexcept(false);

    template <typename... Arguments>
    Any operator()(const Any& object, Arguments&&... arguments) const noexcept(false);

    /**
     * Return meta field with the given `name` for this field reflection.
     */
    const Meta* get_meta(const FastName& name) const noexcept;

    /**
     * Return all meta fields for this field reflection.
     */
    const Vector<const Meta*>& get_meta() const noexcept;

    /**
     * Add meta field to this field reflection.
     */
    void add_meta(const FastName& name, Any&& value) noexcept;

private:
    Method(const FastName& name, AnyFunction&& function) noexcept;

    Vector<const Meta*> m_meta;
    AnyFunction m_method;
    FastName m_name;

    // Allow this function to create Method:
    friend Method* reflection_details::add_method(const FastName&, AnyFunction&&) noexcept;
};

/**
 * Meta is just some information that can be stored in object, field or method reflection. Meta is inherited.
 */
class Reflection::Meta {
public:
    /**
     * Return name of the meta field.
     */
    const FastName& get_name() const noexcept;

    /**
     * Return value of the meta field.
     */
    const Any& get_value() const noexcept;

private:
    Meta(const FastName& name, Any&& value) noexcept;

    FastName m_name;
    Any m_value;

    // Allow this function to create Meta:
    friend Meta* reflection_details::add_meta(const FastName&, Any&&) noexcept;
};
} // namespace kw

#include <kw/reflection/internal/reflection_impl.h>

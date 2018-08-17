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
 * Reflection of specific object `T` is a set of its reflectable fields, methods and meta fields.
 *
 * For example for such object:
 *
 * \code
 * struct Foo {
 *     void bar(int8 arg1, int16 arg2);
 *
 *     int32 a;
 *     int64 b;
 * };
 * \endcode
 *
 * Its reflection could be:
 * * Methods: void (Foo::*bar)(int8, int16)
 * * Fields: int32 a, int64 b
 *
 * But not necessary all the fields or methods are in the reflection, you can add specific fields and methods in
 * reflection of any type.
 */
class Reflection {
public:
    /**
     * Reflection::Meta is just some information that can be stored in object, field or method reflection.
     *
     * Meta is inherited. If parent reflection already contains a meta field with specific name, it is overridden by a
     * child meta field.
     */
    class Meta;

    /**
     * Reflection::Field reflects an actual field of an object (i.e. we have an object of type Cat and it has a field
     * called `name`, reflection of this field is its type, address relative to field's object and name).
     *
     * Fields are inherited. If parent reflection already contains a field with specific name, it is overridden by a
     * child field. But keep in mind, if two parent objects have fields with the same name, an assertion error will occur.
     */
    class Field;

    /**
     * Reflection::Method reflects an actual method of an object (i.e. if we have an object of type Cat and it has a
     * method called `meow`, reflection of this method is a `Function` (please take a look at AnyFunction class) and
     * a name.
     *
     * Methods are inherited. If parent reflection already contains a method with specific name, it is overridden by a
     * child method. But keep in mind, if two parent objects have methods with the same name, an assertion error will occur.
     */
    class Method;

    /**
     * Add reflection of the given type `T` and return it. If reflection is already added, return nullptr.
     *
     * Do not use template `of` method before calling this method (because then it caches nullptr Reflection).
     *
     * If `T` has parents, `Type::register_parents<T, ...>` must be called before this method (and its parents too)
     * otherwise neither fields nor method nor meta will be inherited.
     */
    template <typename T>
    static Reflection* add();

    /**
     * Return reflection of the given type `T`. If reflection for the given type doesn't exist, return nullptr.
     *
     * Keep in mind, that this overload of `of` method is the fastest one, because it's based on static cached
     * variable, while other overloads are implemented using hash map search.
     *
     * WARNING: Must be called after `add<T>()`, because this method caches a value from reflection hash map.
     */
    template <typename T>
    static const Reflection* of() noexcept;

    /**
     * Return reflection of the given type `type`. If reflection of the given type doesn't exist, return nullptr .
     */
    static const Reflection* of(const Type* type) noexcept;

    /**
     * Return reflection of a type stored in the given `any`. If reflection of the given type doesn't exist,
     * return nullptr.
     */
    static const Reflection* of(const Any& any) noexcept;

    /**
     * Return a field with the given `name`, stored in this reflection. If the field with the given `name` doesn't
     * exist, return nullptr.
     */
    const Field* get_field(const FastName& name) const noexcept;

    /**
     * Return vector of fields stored in this reflection (including inherited fields).
     */
    const Vector<const Field*>& get_fields() const noexcept;

    /**
     * Add a field with the given type `T` and `name` to reflection. When choosing `offset`, take parent classes
     * and aligning into account (you can use `offsetof` function for this purpose).
     */
    template <typename T>
    Field* add_field(const FastName& name, uintptr_t offset) noexcept;

    /**
     * Return a method with the given `name`, stored in this reflection. If the method with the given `name` doesn't
     * exist, return nullptr.
     */
    const Method* get_method(const FastName& name) const noexcept;

    /**
     * Return vector of methods stored in this reflection (including inherited methods).
     */
    const Vector<const Method*>& get_methods() const noexcept;

    /**
     * Add a method with the given `name` represented by provided `function`. As far as `AnyFunction`s constructor
     * is implicit, it is allowed to just pass a pointer to a method.
     *
     * \code
     * reflection->add_method(FastName("foo"), &MyClass::foo);
     * \endcode
     */
    Method* add_method(const FastName& name, AnyFunction&& function) noexcept;

    /**
     * Return meta field with the given `name` stored in this reflection. If the meta field with the given `name`
     * doesn't exist, return nullptr.
     */
    const Meta* get_meta(const FastName& name) const noexcept;

    /**
     * Return all meta fields stored in this reflection.
     */
    const Vector<const Meta*>& get_meta() const noexcept;

    /**
     * Add a meta field with the given `name` and `value`.
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
 * Reflection::Meta is just some information that can be stored in object, field or method reflection.
 *
 * Meta is inherited. If parent reflection already contains a meta field with specific name, it is overridden by a
 * child meta field.
 */
class Reflection::Meta {
public:
    /**
     * Return name of this meta field.
     */
    const FastName& get_name() const noexcept;

    /**
     * Return value of this meta field.
     */
    const Any& get_value() const noexcept;

private:
    Meta(const FastName& name, Any&& value) noexcept;

    FastName m_name;
    Any m_value;

    // Allow this function to create Meta:
    friend Meta* reflection_details::add_meta(const FastName&, Any&&) noexcept;
};

/**
 * Reflection::Field reflects an actual field of an object (i.e. we have an object of type Cat and it has a field
 * called `name`, reflection of this field is its type, address relative to field's object and name).
 *
 * Fields are inherited. If parent reflection already contains a field with specific name, it is overridden by a
 * child field. But keep in mind, if two parent objects have fields with the same name, an assertion error will occur.
 */
class Reflection::Field {
public:
    /**
     * Return type of this field. Always a pointer.
     *
     * \code
     * KW_ASSERT(field->get_type()->is_pointer());
     * \endcode
     */
    const Type* get_type() const noexcept;

    /**
     * Return name of this field.
     */
    const FastName& get_name() const noexcept;

    /**
     * Return a pointer to this field in the given `object`.
     *
     * WARNING: Please check type of `object` while working with reflection! Field does not perform this check
     * because it doesn't contain a Type of an object it's in (because it is actually shared between multiple types).
     */
    Any get(const Any& object) const noexcept;
    template <typename T>
    Any get(const T& object) const noexcept;

    /**
     * Return meta field with the given `name` stored in this field. If the meta field with the given `name`
     * doesn't exist, return nullptr.
     */
    const Meta* get_meta(const FastName& name) const noexcept;

    /**
     * Return all meta fields stored in this field.
     */
    const Vector<const Meta*>& get_meta() const noexcept;

    /**
     * Add a meta field with the given `name` and `value`.
     */
    void add_meta(const FastName& name, Any&& value) noexcept;

    /**
     * Return offset of this field relatively to the object.
     */
    uintptr_t get_offset() const noexcept;

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

    // Allow this function to create Field:
    friend Field* reflection_details::add_field(const Type*, const FastName&, uintptr_t) noexcept;
};

/**
 * Reflection::Method reflects an actual method of an object (i.e. if we have an object of type Cat and it has a
 * method called `meow`, reflection of this method is a `Function` (please take a look at AnyFunction class) and
 * a name.
 *
 * Methods are inherited. If parent reflection already contains a method with specific name, it is overridden by a
 * child method. But keep in mind, if two parent objects have methods with the same name, an assertion error will occur.
 */
class Reflection::Method {
public:
    /**
     * Return name of the field.
     */
    const FastName& get_name() const noexcept;

    /**
     * Call the contained method of the given `object` using provided `arguments`.
     */
    template <typename ObjectType, typename... Arguments>
    Any operator()(const ObjectType& object, Arguments&&... arguments) const noexcept(false);

    template <typename... Arguments>
    Any operator()(const Any& object, Arguments&&... arguments) const noexcept(false);

    /**
     * Return meta field with the given `name` stored in this method. If the meta field with the given `name`
     * doesn't exist, return nullptr.
     */
    const Meta* get_meta(const FastName& name) const noexcept;

    /**
     * Return all meta fields stored in this method.
     */
    const Vector<const Meta*>& get_meta() const noexcept;

    /**
     * Add a meta field with the given `name` and `value`.
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
} // namespace kw

#include <kw/reflection/internal/reflection_impl.h>

/**
 * A shortcut Reflection. You can use `kw` structures and types inside, as if there's `using namespace kw`
 * (there actually is).
 * By using this macro you never ask yourself anymore 'where do I add reflection for my class?' and simply use
 * this macro in your source file.
 *
 * \code
 * REFLECTION_REGISTRATOR({
 *    Reflection* reflection = Reflection::add<MyClass>();
 *    reflection->add_field("field_name", offsetof(MyClass, field_name));
 * });
 * \endcode
 */
#define REFLECTION_REGISTRATOR(scope) \
    static int REFLECTION_##__COUNTER__ = [] { \
        using namespace kw; \
        scope return 0; \
    }();

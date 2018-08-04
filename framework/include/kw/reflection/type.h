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

#include <kw/base/detected.h>
#include <kw/base/pair.h>
#include <kw/base/types.h>
#include <kw/base/vector.h>
#include <kw/debug/assert.h>

#include <typeinfo>

namespace kw {
/**
 * Type is a structure that contains information about specific types.
 * For the same type there's always the same Type instance. So when it is not possible to check if two objects
 * belong to the same type using templates (like when they're hidden in Any structure), but there're Types of these
 * objects available, it is enough to just compare these Types.
 * Type also stores inheritance information, destructors and comparators. Keep in mind tho, that it is very difficult
 * to understand right away what kind of functionality is needed for Type (is_pointer, is_array, maybe something else?),
 * so feel free to add whatever you need.
 * Please, inspect this class to get more information.
 */
class Type final {
public:
    /**
     * The following structure contains information about a base class relative to a child class.
     */
    struct Parent {
        const Type* type; /// Type of the base class.
        uintptr_t offset; /// Offset of the base class relatively to the child (for multiple inheritance).
    };

    /**
     * Construct an object of underlying type.
     * If underlying type is small enough, object is considered to be stored inside of a pointer,
     * and so constructor is called on the pointer, but not on what pointer points at.
     */
    typedef void (*default_constructor_t)(void**) noexcept;

    /**
     * Clean up an object of the underlying type.
     * If underlying type is small enough, object is considered to be stored inside of a pointer,
     * and so destructor is called on the pointer, but not on what pointer points at.
     */
    typedef void (*destructor_t)(void*) noexcept;

    /**
     * Return 0 if the given objects of the underlying type are equal.
     * Return -1 if the first object is less than the second.
     * Return 1 if the first object is more than the second.
     */
    typedef int32 (*comparator_t)(const void*, const void*) noexcept;

    /**
     * Return hash of the object with the underlying type.
     * If the object doesn't have a hash function, this function will cause an invalid assertion and
     * return a object's pointer casted to size_t (so it's not completely broken in release build).
     */
    typedef size_t (*hash_t)(const void*) noexcept;

    /**
     * Return an unique Type instance for any unique type T.
     *
     * \code
     * Type* type_a = Type::of<MyClass>();
     * Type* type_b = Type::of<MyClass>();
     * Type* type_c = Type::of<AnotherClass>();
     * KW_ASSERT(type_a == type_b && type_a != type_c);
     * \endcode
     */
    template <typename T>
    static const Type* of() noexcept;

    /**
     * Unfortunately C++ doesn't provide any way to get base classes of some type,
     * so the following function must be used to provide this information.
     *
     * \code
     * struct DummyBaseA {};
     * struct DummyBaseB {};
     * struct DummyChild : DummyBaseA, DummyBaseB { };
     *
     * Type::register_parents<DummyChild, DummyBaseA, DummyBaseB>();
     * \endcode
     */
    template <typename T, typename... Bases>
    static void register_parents() noexcept;

    Type(Type&&) = delete;
    Type(const Type&) = delete;
    Type& operator=(Type&&) = delete;
    Type& operator=(const Type&) = delete;

    /**
     * Return std::type_info of the underlying type.
     */
    const std::type_info& get_type_info() const noexcept;

    /**
     * Return size of the underlying type.
     */
    size_t get_size() const noexcept;

    /**
     * Return name of the underlying type (compiler-dependent).
     */
    const char* get_name() const noexcept;

    /**
     * Return the set parent classes of the underlying type.
     * Keep in mind that parent classes must be registered manually via `register_parents` method.
     */
    const Vector<Parent>& get_parents() const noexcept;

    /**
     * Return the default constructor function for the underlying type.
     * If the underlying type is not default constructible, return nullptr.
     * Please, take a look at `default_constructor_t` structure.
     */
    default_constructor_t get_default_constructor() const noexcept;

    /**
     * Return the destructor function for the underlying type.
     * Please, take a look at `destructor_t` structure.
     */
    destructor_t get_destructor() const noexcept;

    /**
     * Return the comparator function for the underlying type.
     * Please, take a look at `comparator_t` structure.
     */
    comparator_t get_comparator() const noexcept;

    /**
     * Return the hash function for the underlying type.
     * Please, take a look at `hash_t` structure.
     */
    hash_t get_hash() const noexcept;

    /**
     * If Any holding an object of this Type must use Small Object Optimization, the return value is true.
     * Otherwise the return value is false.
     */
    bool is_small_object() const noexcept;

    /**
     * Return true if the underlying type is a pointer type.
     *
     * \code
     * KW_ASSERT(Type::of<int32*>().is_pointer());
     * \endcode
     */
    bool is_pointer() const noexcept;

    /**
     * If the given type is a pointer type, return type this pointer points at. Otherwise return nullptr.
     */
    const Type* remove_pointer() const noexcept;

    /**
     * Return true if the given `T` is the underlying type. Otherwise return false.
     */
    template <typename T>
    bool is_same() const noexcept;

    /**
     * Return true as the first value, if the underlying type is parent of the given type.
     * The second value in that case is an offset from child type to base type.
     * Otherwise return false as the first value, and nullptr as the second value.
     */
    Pair<bool, uintptr_t> is_base_of(const Type* type) const noexcept;

    /**
     * Return true as the first value, if the underlying type is parent of the given type.
     * The second value in that case is an offset from child type to base type.
     * Otherwise return false as the first value, and nullptr as the second value.
     */
    template <typename T>
    Pair<bool, uintptr_t> is_base_of() const noexcept;

    /**
     * Return true as the first value, if the underlying type is inherited from the given type.
     * The second value in that case is an offset from child type to base type.
     * Otherwise return false as the first value, and nullptr as the second value.
     */
    Pair<bool, uintptr_t> is_inherited_from(const Type* type) const noexcept;

    /**
     * Return true as the first value, if the underlying type is inherited from the given type.
     * The second value in that case is an offset from child type to base type.
     * Otherwise return false as the first value, and nullptr as the second value.
     */
    template <typename T>
    Pair<bool, uintptr_t> is_inherited_from() const noexcept;

private:
    template <typename T>
    explicit Type(const T* dummy) noexcept;

    Vector<Parent> m_parents;
    const std::type_info& m_type_info;
    const Type* m_without_pointer;
    size_t m_size;

    default_constructor_t m_default_constructor;
    destructor_t m_destructor;
    comparator_t m_comparator;
    hash_t m_hash;
};
} // namespace kw

#include <kw/reflection/internal/type_impl.h>

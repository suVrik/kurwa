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
 * Type is a structure that contains information about a specific type.
 *
 * For the same type there's always the same Type instance. So when it is not possible to check if two objects
 * belong to the same type using templates (like when they're hidden in Any structure), but there're `Type`s of these
 * objects available, it is enough to just compare these `Type`s.
 *
 * Type also stores inheritance information, destructor, default constructor and comparator. Keep in mind though,
 * that it is very difficult to understand right away what kind of functionality is needed for Type (`is_array`,
 * `is_const` or maybe something else?), so feel free to add or propose whatever you need.
 */
class Type final {
public:
    /**
     * The following structure contains information about a base class relative to a child class.
     */
    struct Parent final {
        const Type* type; /// Type of the base class.
        uintptr_t offset; /// Offset of the base class relatively to the child (for multiple inheritance).
    };

    /**
     * The following structure lists all supported container types. To check if a specific type is a container,
     * please use `get_container` method. To get `Type` of its template arguments, please use
     * `get_template_arguments` method.
     */
    enum class Container {
        NONE,
        ARRAY,
        BASIC_STRING,
        BASIC_STRING_VIEW,
        BITSET,
        BITVECTOR,
        DEQUE,
        FIXED_BASIC_STRING,
        FIXED_HASH_MAP,
        FIXED_HASH_SET,
        FIXED_LIST,
        FIXED_MAP,
        FIXED_MULTIMAP,
        FIXED_MULTISET,
        FIXED_SET,
        FIXED_SLIST,
        FIXED_VECTOR,
        HASH_MAP,
        HASH_SET,
        LIST,
        MAP,
        OPTIONAL,
        PAIR,
        PRIORITY_QUEUE,
        QUEUE,
        RING_BUFFER,
        SET,
        SHARED_PTR,
        SLIST,
        STACK,
        STRING_HASH_MAP,
        STRING_MAP,
        TUPLE,
        UNIQUE_PTR,
        VARIANT,
        VECTOR,
        VECTOR_MAP,
        VECTOR_MULTIMAP,
        VECTOR_MULTISET,
        VECTOR_SET,
    };

    /**
     * Construct an object of this type.
     *
     * If an object of this type is small enough, it is considered to be stored inside of a pointer (it is called
     * small object optimization), and so constructor is called on the pointer, but not on what pointer points at.
     */
    typedef void (*default_constructor_t)(void**) noexcept;

    /**
     * Clean up an object of this type.
     *
     * If an object of this type is small enough, it is considered to be stored inside of a pointer (it is called
     * small object optimization), and so destructor is called on the pointer, but not on what pointer points at.
     */
    typedef void (*destructor_t)(void*) noexcept;

    /**
     * Return 0 if the given objects of this type are equal.
     * Return -1 if the first object is less than the second.
     * Return 1 if the first object is greater than the second.
     */
    typedef int32 (*comparator_t)(const void*, const void*) noexcept;

    /**
     * Return hash of the object with this type.
     *
     * If the object doesn't have a hash function, this function will cause an invalid assertion and
     * return an object's pointer casted to size_t (so it's not completely broken in release build).
     */
    typedef size_t (*hash_t)(const void*) noexcept;

    /**
     * Return a unique `Type` instance for any unique type `T`.
     *
     * WARNING: References are removed from original types for simplification. Use pointers instead.
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
     * Unfortunately C++ doesn't provide any way to get base classes of some type, so the following function
     * must be used to provide this information.
     *
     * WARNING: Virtual inheritance is not supported yet due to implementation complexity.
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
     * Return `std::type_info` of the underlying type.
     */
    const std::type_info& get_type_info() const noexcept;

    /**
     * Return size of the underlying type.
     */
    size_t get_size() const noexcept;

    /**
     * Return name of the underlying type (it is compiler-dependent, must be used only for debug purposes).
     */
    const char* get_name() const noexcept;

    /**
     * Return the set of parent classes of this type.
     *
     * Keep in mind that parent classes must be registered manually via `register_parents` method.
     */
    const Vector<Parent>& get_parents() const noexcept;

    /**
     * Return the default constructor function for this type. If this type is not default constructible, return nullptr.
     */
    default_constructor_t get_default_constructor() const noexcept;

    /**
     * Return the destructor function for this type.
     */
    destructor_t get_destructor() const noexcept;

    /**
     * Return the comparator function for this type.
     */
    comparator_t get_comparator() const noexcept;

    /**
     * Return the hash function for this type.
     */
    hash_t get_hash() const noexcept;

    /**
     * Return container type.
     */
    Container get_container() const noexcept;

    /**
     * Return the set of template arguments, if they are present. Otherwise return an empty set.
     *
     * Works only for `Container` types!
     */
    const Vector<const Type*>& get_template_arguments() const noexcept;

    /**
     * Return true if `Any` containing an object of this type must use small object optimization.
     * Otherwise return false.
     */
    bool is_small_object() const noexcept;

    /**
     * Return true if this is a pointer type.
     *
     * \code
     * KW_ASSERT(Type::of<int32*>()->is_pointer());
     * \endcode
     */
    bool is_pointer() const noexcept;

    /**
     * If this type is a pointer type, return type this pointer points at. Otherwise return nullptr.
     *
     * \code
     * KW_ASSERT(Type::of<int32*>()->remove_pointer() == Type::of<int32>());
     * \endcode
     */
    const Type* remove_pointer() const noexcept;

    /**
     * Return true if the given `T` is this type. Otherwise return false.
     */
    template <typename T>
    bool is_same() const noexcept;

    /**
     * Return true as the first value, if this type is parent of the given type.
     * The second value in that case is an offset from child type to base type.
     * Otherwise return false as the first value, and nullptr as the second value.
     */
    Pair<bool, uintptr_t> is_base_of(const Type* type) const noexcept;

    template <typename T>
    Pair<bool, uintptr_t> is_base_of() const noexcept;

    /**
     * Return true as the first value, if this type is inherited from the given type.
     * The second value in that case is an offset from child type to base type.
     * Otherwise return false as the first value, and nullptr as the second value.
     */
    Pair<bool, uintptr_t> is_inherited_from(const Type* type) const noexcept;

    template <typename T>
    Pair<bool, uintptr_t> is_inherited_from() const noexcept;

private:
    template <typename T>
    explicit Type(const T* dummy) noexcept;

    Vector<Parent> m_parents;
    Vector<const Type*> m_template_arguments;
    const std::type_info& m_type_info;
    const Type* m_without_pointer;
    Container m_container_type;
    size_t m_size;

    default_constructor_t m_default_constructor;
    destructor_t m_destructor;
    comparator_t m_comparator;
    hash_t m_hash;
};
} // namespace kw

#include <kw/reflection/internal/type_containers.h>
#include <kw/reflection/internal/type_impl.h>

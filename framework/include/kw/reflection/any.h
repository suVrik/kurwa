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

#include <kw/reflection/type.h>

namespace eastl {
template <typename T>
struct hash;
} // namespace eastl

namespace kw {
/**
 * The instance of type Any contains an object of any type.
 *
 * Keep in mind that for objects with size less than a size of a pointer, small object optimization is used.
 */
class Any final {
public:
    /**
     * Construct an Any instance with the object of type void (without overhead).
     */
    Any() noexcept;

    /**
     * Construct an Any instance with the object of type `T`, direct-initialized from the given `value`.
     */
    template <typename T>
    Any(T&& value) noexcept;

    /**
     * Construct an Any instance with the object of the given type `type`, default-initialized.
     *
     * \code
     * struct A {
     *     int32 value = 1337;
     * };
     *
     * Any any(Type::of<A>());
     *
     * KW_ASSERT(any.cast<A>()->value == 1337);
     * \endcode
     */
    explicit Any(const Type* type) noexcept;

    /**
     * Construct an Any instance with the pointer type `type` that contains a pointer provided by `value`.
     *
     * \code
     * int32 my_value = 33;
     * Any any(Type::of<int32*>(), &my_value);
     * KW_ASSERT(**any.cast<int32*> == 33);
     * \endcode
     */
    Any(const Type* type, const void* value) noexcept;

    Any(const Any&) = delete;
    Any(Any&& original) noexcept;
    ~Any() noexcept;
    Any& operator=(const Any&) = delete;
    Any& operator=(Any&& original) noexcept;

    /**
     * Compare two Any instances using operators provided by their Types.
     * If these two Any instances have different types, they're considered to be unequal.
     */
    bool operator==(const Any& another) const noexcept;
    bool operator!=(const Any& another) const noexcept;
    bool operator<(const Any& another) const noexcept;
    bool operator>(const Any& another) const noexcept;
    bool operator<=(const Any& another) const noexcept;
    bool operator>=(const Any& another) const noexcept;

    /**
     * Change the contained object to one of type `T`, constructed from the arguments.
     */
    template <typename T, typename... Args>
    void emplace(Args&&... args) noexcept;

    /**
     * If the contained object has type `T` (or inherited from it), return a pointer to it. Otherwise return nullptr.
     *
     * Keep in mind, that this method doesn't work with pointer types. Use `cast_pointer` method for this.
     */
    template <typename T>
    const T* cast() const noexcept;

    /**
     * If the contained object has type `T` (or inherited from it), return a pointer to it. Otherwise return nullptr.
     *
     * Keep in mind, that this method doesn't work with pointer types. Use `cast_pointer` method for this.
     */
    template <typename T>
    T* cast() noexcept;

    /**
     * If the contained object is a pointer to object of type `T` (or inherited from it), return a pointer to it.
     * Otherwise return nullptr.
     */
    template <typename T>
    const T* cast_pointer() const noexcept;

    /**
     * If the contained object is a pointer to object of type `T` (or inherited from it), return a pointer to it.
     * Otherwise return nullptr.
     */
    template <typename T>
    T* cast_pointer() noexcept;

    /**
     * Return type of the contained object.
     */
    const Type* get_type() const noexcept;

    /**
     * Return pointer to raw data stored in this Any object.
     *
     * Dereferencing this pointer might lead to a memory access violation due to small object optimization used in Any.
     */
    void* const& get_raw_data() const noexcept;

    /**
     * Return true if the contained object has the given type `T`. Otherwise return false.
     *
     * A shortcut for `any.get_type()->is_same<T>()`.
     */
    template <typename T>
    bool is_same() const noexcept;

private:
    const Type* m_type;
    void* m_data;
};
} // namespace kw

#include <kw/reflection/internal/any_impl.h>

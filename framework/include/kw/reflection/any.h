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
 * Keep in mind that for objects which size is less than a size of a pointer, small object optimization is used.
 */
class Any final {
public:
    /**
     * Construct an Any instance with the object of type void.
     */
    Any() noexcept;

    /**
     * Construct an Any instance with the object of type 'T', direct-initialized from the given 'value'.
     */
    template <typename T>
    explicit Any(T&& value) noexcept;

    /**
     * Construct an Any instance with the object of the given type 'type', default-initialized.
     */
    explicit Any(const Type* type) noexcept;

    Any(const Any&) = delete;
    Any(Any&& original) noexcept;
    ~Any() noexcept;
    Any& operator=(const Any&) = delete;
    Any& operator              =(Any&& original) noexcept;

    /**
     * Operators equals and less implemented for associative arrays, but can be used for any other reason.
     */
    bool operator==(const Any& another) const noexcept;
    bool operator!=(const Any& another) const noexcept;
    bool operator<(const Any& another) const noexcept;
    bool operator>(const Any& another) const noexcept;
    bool operator<=(const Any& another) const noexcept;
    bool operator>=(const Any& another) const noexcept;

    /**
     * Change the contained object to one of type 'T', constructed from the arguments.
     */
    template <typename T, typename... Args>
    void emplace(Args&&... args) noexcept;

    /**
     * Cast the contained object to the given type 'T' and return a reference to it.
     */
    template <typename T>
    const T* cast() const noexcept;

    /**
     * Cast the contained object to the given type 'T' and return a reference to it.
     */
    template <typename T>
    T* cast() noexcept;

    /**
     * Return type of the contained object.
     */
    const Type* get_type() const;

    /**
     * Return true if the contained object has the given type 'T'. Otherwise return false.
     */
    template <typename T>
    bool is_same() const noexcept;

    /**
     * Return true if the contained object's type is parent of the given 'type'. Otherwise return false.
     */
    bool is_base_of(const Type* type) const noexcept;

    /**
     * Return true if the contained object's type is parent of the given type 'T'. Otherwise return false.
     */
    template <typename T>
    bool is_base_of() const noexcept;

    /**
     * Return true if the contained object's type is inherited from the given type 'type'. Otherwise return false.
     */
    bool is_inherited_from(const Type* type) const noexcept;

    /**
     * Return true if the contained object's type is inherited from the given type 'T'. Otherwise return false.
     */
    template <typename T>
    bool is_inherited_from() const noexcept;

private:
    const Type* m_type;
    void* m_data;

    friend struct eastl::hash<Any>; // Allow hash to access 'm_data' field.
};
} // namespace kw

#include <kw/reflection/internal/any_impl.h>

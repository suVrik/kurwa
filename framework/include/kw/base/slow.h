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

#include <kw/base/types.h>

#include <kw/debug/assert.h>

namespace kw {
/**
 * Slow<T> is a structure that contains and gives access to the object of type 'T'.
 * The difference between 'T' and 'Slow<T>' is that 'Slow<T>' doesn't construct 'T' right away,
 * instead it waits for a 'construct' call.
 * Why not use unique_ptr? Slow<T> allocates memory in place which is convenient for arrays and tuples
 * (i.e. you can iterate over them faster, due to the fact the objects themselves lay each after each).
 */
template <typename T>
class Slow {
public:
    typedef T value_type;

    /**
     * 'T' is not constructed. The attempt to access it leads to undefined behaviour.
     */
    Slow() = default;

    ~Slow() noexcept;
    Slow(const Slow&) = delete;
    Slow(Slow&& original) noexcept;
    Slow& operator=(const Slow&) = delete;
    Slow& operator=(Slow&& original) noexcept;

    /**
     * Construct an object of type 'T' using the given 'Arguments'.
     */
    template <typename... Arguments>
    void construct(Arguments&&... args) noexcept(eastl::is_nothrow_constructible<T>::value);

    /**
     * Provide access to the object owned by SlowObject.
     */
    T& operator*() noexcept;
    const T& operator*() const noexcept;
    T& operator->() noexcept;
    const T& operator->() const noexcept;

    /**
     * Return true if 'construct' was already called. If not, return false.
     */
    bool is_constructed() const noexcept;

private:
    uint8 m_object[sizeof(T)];
    bool m_is_constructed = false;
};
} // namespace kw

#include <kw/base/internal/slow_impl.h>

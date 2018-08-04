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

#include <kw/base/function.h>
#include <kw/base/vector.h>
#include <kw/reflection/any.h>

namespace kw {
/**
 * The instance of AnyFunction contains a pointer to a member function with any arguments and any return value type.
 */
class AnyFunction {
public:
    AnyFunction() = default;

    /**
     * Construct AnyFunction with the given member function `function`.
     */
    template <typename Result, typename Object, typename... Arguments>
    AnyFunction(Result (Object::*const function)(Arguments...)) noexcept;

    template <typename Result, typename Object, typename... Arguments>
    AnyFunction(Result (Object::*const function)(Arguments...) noexcept) noexcept;

    template <typename Result, typename Object, typename... Arguments>
    AnyFunction(Result (Object::*const function)(Arguments...) const) noexcept;

    template <typename Result, typename Object, typename... Arguments>
    AnyFunction(Result (Object::*const function)(Arguments...) const noexcept) noexcept;

    /**
     * Call the contained member function of the given `object` using provided `arguments`.
     */
    template <typename ObjectType, typename... Arguments>
    Any operator()(const ObjectType& object, Arguments&&... arguments) const noexcept(false);

    template <typename... Arguments>
    Any operator()(const Any& object, Arguments&&... arguments) const noexcept(false);

private:
    Function<Any(const Any&, Vector<Any>&)> m_function;
};
} // namespace kw

#include <kw/reflection/internal/any_function_impl.h>

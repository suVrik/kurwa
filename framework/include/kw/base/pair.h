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

#include <EASTL/utility.h>
#include <utility>

namespace kw {
template <typename T1, typename T2>
using Pair = eastl::pair<T1, T2>;
using eastl::make_pair;
} // namespace kw

// Required for Structured binding declaration
namespace std {
template <typename A, typename B>
struct tuple_size<eastl::pair<A, B>> : eastl::integral_constant<size_t, 2> {};
template <typename A, typename B>
struct tuple_element<0, eastl::pair<A, B>> {
    typedef A type;
};
template <typename A, typename B>
struct tuple_element<1, eastl::pair<A, B>> {
    typedef B type;
};
} // namespace std

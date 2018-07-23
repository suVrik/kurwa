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

#include <EASTL/tuple.h>

namespace kw {
template <typename... Ts>
using Tuple = eastl::tuple<Ts...>;

template <typename T, typename Tuple>
struct has;

template <typename T>
struct has<T, Tuple<>> : eastl::false_type {};

template <typename T, typename U, typename... Ts>
struct has<T, Tuple<U, Ts...>> : has<T, eastl::tuple<Ts...>> {};

template <typename T, typename... Ts>
struct has<T, Tuple<T, Ts...>> : eastl::true_type {};

template <typename T1, typename T2>
using has_t = typename has<T1, T2>::type;

using eastl::get;
} // namespace kw

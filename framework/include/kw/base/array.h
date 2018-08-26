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

#include <EASTL/array.h>

#include <utility>

namespace kw {
template <typename T, size_t N>
using Array = eastl::array<T, N>;
} // namespace kw

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmismatched-tags"
#endif // __clang__

// Required for Structured binding declaration
namespace std {
template <typename T, size_t N>
struct tuple_size<eastl::array<T, N>> : eastl::integral_constant<size_t, N> {};

template <size_t Index, typename T, size_t N>
struct tuple_element<Index, eastl::array<T, N>> {
    typedef T type;
};
} // namespace std

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

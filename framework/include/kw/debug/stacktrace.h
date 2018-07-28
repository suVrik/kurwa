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

#include <kw/base/string.h>
#include <kw/base/types.h>

namespace kw {
/**
 * Please, look at 'get_stacktrace' static method for description.
 */
class Stacktrace {
public:
    Stacktrace() = delete;

    /**
     * Return current stacktrace (ignoring the 'get_stacktrace' method itself).
     * The 'skip_count' argument tells how many stack levels to skip.
     * The 'offset' argument is a number of spaces in each line (for style kind of things).
     */
    static String get_stacktrace(uint32 skip_count = 0, uint32 offset = 0) noexcept;
};
} // namespace kw

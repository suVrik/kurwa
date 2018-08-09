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

#include <fmt/format.h>

namespace kw {
/**
 * Show message box with the formatted string 'format_str'.
 * The message is also duplicated in stderr stream.
 * Keep in mind this is a blocking call.
 */
template <typename... Args>
void message_box(const String& format_str, const Args&... args);
} // namespace kw

#include <kw/core/internal/message_box_impl.h>

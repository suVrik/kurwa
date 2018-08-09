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

#include <kw/core/message_box.h>

namespace kw {
namespace message_box_details {
void show_message_box(const String& message);
} // namespace message_box_details

template <typename... Args>
void message_box(const String& format_str, const Args&... args) {
    const String str = fmt::format(format_str, args...);
    message_box_details::show_message_box(str);
}
} // namespace kw

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

#include <kw/base/queue.h>
#include <kw/concurrency/mutex.h>
#include <kw/render/commands.h>

namespace kw {
namespace render {

/**
 * UpdateQueue is a thread-safe wrapper around a Queue, which is used to prerecord updates for a rendering backend.
 */
class UpdateQueue {
public:
    CommandBuffer pop();

    void push(CommandBuffer&& command_buffer);

private:
    Queue<CommandBuffer> m_queue;
    Mutex m_mutex;
};

} // namespace render
} // namespace kw

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

#include <kw/render/update_queue.h>

namespace kw {
namespace render {

CommandBuffer UpdateQueue::pop() {
    LockGuard<Mutex> lock(m_mutex);
    CommandBuffer command_buffer = eastl::move(m_queue.front());
    m_queue.pop();
    return command_buffer;
}

void UpdateQueue::push(CommandBuffer&& command_buffer) {
    LockGuard<Mutex> lock(m_mutex);
    m_queue.push(command_buffer);
}

} // namespace render
} // namespace kw

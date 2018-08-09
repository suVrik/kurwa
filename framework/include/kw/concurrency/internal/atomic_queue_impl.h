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

#include <kw/concurrency/atomic_queue.h>

namespace kw {
template <typename T>
void AtomicQueue<T>::pop(T& value) noexcept {
    KW_ASSERT(!m_queue.empty(), "The queue is empty!");

    LockGuard<Mutex> lock(m_mutex);
    value = eastl::move(m_queue.front());
    m_queue.pop();
}

template <typename T>
void AtomicQueue<T>::push(T&& value) noexcept {
    LockGuard<Mutex> lock(m_mutex);
    m_queue.push(eastl::move(value));
}

template <typename T>
bool AtomicQueue<T>::is_empty() const {
    return m_queue.empty();
}
} // namespace kw

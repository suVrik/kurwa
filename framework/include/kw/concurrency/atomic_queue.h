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
#include <kw/debug/assert.h>

namespace kw {
/**
 * AtomicQueue is a thread-safe wrapper around a Queue.
 */
template <typename T>
class AtomicQueue final {
public:
    /**
     * Pop the first value out of queue and return it.
     *
     * If the queue is empty, behaviour is undefined. Use `is_empty` to check if it's empty.
     */
    void pop(T& value) noexcept;

    /**
     * Push the given `value` into the queue.
     */
    void push(T&& value) noexcept;

    /**
     * Return true if this queue is empty or false otherwise.
     */
    bool is_empty() const;

private:
    Queue<T> m_queue;
    Mutex m_mutex;
};
} // namespace kw

#include <kw/concurrency/internal/atomic_queue_impl.h>

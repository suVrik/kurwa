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

#include <kw/base/types.h>

struct SDL_semaphore;

namespace kw {
/**
 * Semaphore class describes a lockable object.
 * Any thread can signal a semaphore, at any time, whether or not that thread has previously waited for the semaphore.
 * Ownership is taken with a wait operation, also known as decrementing the semaphore.
 * Ownership is released with a post operation, also known as incrementing the semaphore.
 * If the count is greater than zero then the decrement happens, and the wait call returns.
 * If the count is zero then it cannot be decremented, so the wait call will block until another thread calls post.
 */
class Semaphore {
public:
    Semaphore() noexcept;
    explicit Semaphore(uint32 counter) noexcept;
    ~Semaphore() noexcept;
    Semaphore(const Semaphore& original) = delete;
    Semaphore& operator=(const Semaphore& original) = delete;

    /**
     * Atomically increment a semaphore's value and wake waiting threads.
     */
    void post() const noexcept;
    /**
     * Wait until a semaphore has a positive value and then decrement it.
     */
    void wait() const noexcept;

private:
    SDL_semaphore* sem;
};
} // namespace kw

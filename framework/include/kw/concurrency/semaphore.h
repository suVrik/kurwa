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

struct SDL_semaphore;

namespace kw {
/**
 * Semaphore is a class that provides a synchronization service for multithreaded code.
 */
class Semaphore {
public:
    Semaphore() noexcept;
    explicit Semaphore(unsigned short counter) noexcept;
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
}
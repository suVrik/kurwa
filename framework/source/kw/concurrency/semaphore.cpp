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

#include <kw/concurrency/semaphore.h>

#include <SDL2/SDL_mutex.h>

namespace kw {
Semaphore::Semaphore() noexcept
    : m_semaphore(SDL_CreateSemaphore(0)) {
}

Semaphore::Semaphore(uint32 counter) noexcept
    : m_semaphore(SDL_CreateSemaphore(counter)) {
}

Semaphore::~Semaphore() noexcept {
    SDL_DestroySemaphore(m_semaphore);
}

void Semaphore::wait() const noexcept {
    SDL_SemWait(m_semaphore);
}

void Semaphore::post() const noexcept {
    SDL_SemPost(m_semaphore);
}
} // namespace kw

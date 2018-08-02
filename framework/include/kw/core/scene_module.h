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

#include <kw/base/signal.h>
#include <kw/base/string.h>
#include <kw/base/types.h>
#include <kw/concurrency/atomic.h>
#include <kw/concurrency/mutex.h>
#include <kw/concurrency/semaphore.h>
#include <kw/concurrency/thread.h>
#include <kw/render/commands.h>

union SDL_Event;
struct SDL_Window;

namespace kw {
class IGame;

class RenderingBackend;

/**
 * UpdateQueue is a thread-safe wrapper around a List, which is used to prerecord updates for a rendering backend.
 */
class UpdateQueue {
public:
    render::CommandBuffer front() const {
        return m_queue.front();
    }

    void pop() {
        LockGuard<Mutex> lock(m_mutex);
        m_queue.pop_front();
    }

    void push(render::CommandBuffer&& command_buffer) {
        LockGuard<Mutex> lock(m_mutex);
        m_queue.emplace_back(command_buffer);
    }
private:
    List<render::CommandBuffer> m_queue;
    Mutex m_mutex;
};

/**
 * Scene module creates an update loop, records and stores the commands to be sent to a rendering backend.
 */
class SceneModule : public SignalListener {
public:
    explicit SceneModule(IGame* game) noexcept;
    SceneModule(const SceneModule& original) = delete;
    SceneModule& operator=(const SceneModule& original) = delete;
private:
    void on_init_listener(kw::IGame *game) noexcept(false);
    void on_update_listener() noexcept(false);
    void on_destroy_listener(kw::IGame *game) noexcept;

    // The number of updates to prepare beforehand
    const unsigned short VIRTUAL_FRAMES_NUMBER = 2;
    Thread m_thread;
    RenderingBackend* m_renderer;
    AtomicBool is_update_thread_active = true;
    Semaphore m_render_semaphore;
    Semaphore m_update_semaphore;
    UpdateQueue m_update_queue;
};
} // namespace kw
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
#include <kw/base/unique_ptr.h>
#include <kw/concurrency/atomic.h>
#include <kw/concurrency/atomic_queue.h>
#include <kw/concurrency/semaphore.h>
#include <kw/concurrency/thread.h>
#include <kw/render/internal/backend.h>
#include <kw/render/internal/commands.h>

struct SDL_Window;

namespace kw {
namespace render {
class Backend;
} // namespace render

class IGame;

/**
 * RenderModule runs a separate rendering thread and synchronizes it with a main thread's `on_update` signal.
 */
class RenderModule final : public SignalListener {
public:
    explicit RenderModule(IGame* game) noexcept;
    RenderModule(const RenderModule& original) = delete;
    ~RenderModule();
    RenderModule& operator=(const RenderModule& original) = delete;

    /**
     * Push a specified `command buffer` into a temporary command buffers queue,
     * which will be sent to rendering backend at the very end of `IGame`s `on_update` signal.
     */
    void push_command_buffer(render::CommandBuffer&& command_buffer) noexcept;

    /**
     * Return a rendering backend type, that current RenderModule is running on.
     */
    render::Backend::Type get_rendering_backend_type() noexcept;

private:
    void on_init_listener(IGame* game) noexcept(false);
    void on_destroy_listener(IGame*) noexcept;
    void on_update_listener() noexcept;

    Thread m_thread;
    Semaphore m_render_semaphore;
    Semaphore m_update_semaphore;
    Atomic<bool> is_thread_active;

    UniquePtr<render::Backend> m_backend;
    AtomicQueue<render::CommandBuffers> m_command_buffers_queue;
    render::CommandBuffers m_command_buffers;
    render::Backend::Type m_backend_type;
};

} // namespace kw

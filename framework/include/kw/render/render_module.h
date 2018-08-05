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
#include <kw/concurrency/semaphore.h>
#include <kw/render/rendering_backend.h>
#include <kw/render/update_queue.h>

struct SDL_Window;

namespace kw {

enum class RenderingBackendType {
    OPENGL
};

class IGame;

/**
 * Render module provides access to the render implementation.
 */
class RenderModule final : public SignalListener {
public:
    /**
     * Construct a render module using the given 'game' instance.
     */
    explicit RenderModule(kw::IGame* game) noexcept;
    RenderModule(const RenderModule& original) = delete;
    RenderModule& operator=(const RenderModule& original) = delete;

    /**
     * Push a specified command buffer content into a local command buffer.
     */

    //TODO noexcept
    void push_command_buffer(render::CommandBuffer&& command_buffer);

    /**
     * Submit a local command buffer to the update queue.
     */
    void submit_command_buffers();

    /**
     * Return a renderer instance.
     */
    RenderingBackend* const get_rendering_backend() const noexcept;

    /**
     * Return a specified renderer type.
     */
    const RenderingBackendType get_rendering_backend_type() noexcept;

private:
    void on_init_listener(kw::IGame* game) noexcept(false);
    void on_update_listener() noexcept(false);

    UniquePtr<RenderingBackend> m_renderer;
    SDL_Window* m_window;
    RenderingBackendType m_renderer_type = RenderingBackendType::OPENGL;
    static constexpr uint32 COMMAND_BUFFER_QUEUE_SIZE = 2;

    Semaphore m_render_semaphore;
    Semaphore m_update_semaphore;
    render::UpdateQueue m_update_queue;
    render::CommandBuffer m_command_buffer;
};

} // namespace kw

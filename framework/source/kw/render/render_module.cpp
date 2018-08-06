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

#include <kw/core/i_game.h>
#include <kw/core/window_module.h>
#include <kw/render/backend_opengl.h>
#include <kw/render/render_module.h>

#include <SDL2/SDL_video.h>

namespace kw {

RenderModule::RenderModule(IGame* game) noexcept
    : m_render_semaphore(COMMAND_BUFFER_QUEUE_SIZE)
    , m_main_thread_id(this_thread::get_id()) {
    game->on_init.connect(this, &RenderModule::on_init_listener);
    game->on_update.connect(this, &RenderModule::on_update_listener);
}

void RenderModule::on_init_listener(IGame* game) noexcept(false) {
    auto& window_module = game->get<WindowModule>();
    m_window = window_module.get_window();
    switch (m_renderer_type) {
        case RenderingBackendType::OPENGL:
            m_renderer = eastl::make_unique<render::BackendOpenGL>(game);
            break;
        default:
            break;
    }
}

void RenderModule::on_update_listener() noexcept(false) {
    m_update_semaphore.wait();
    render::CommandBuffer buffer = m_update_queue.pop();
    m_render_semaphore.post();
    m_renderer->process_command_buffer(eastl::move(buffer));
}

void RenderModule::push_command_buffer(render::CommandBuffer&& command_buffer) noexcept {
    KW_ASSERT(this_thread::get_id() != m_main_thread_id, "You are trying to push command buffers from a wrong thread!");
    for (render::Command& command : command_buffer.commands) {
        m_command_buffer.commands.push_back(eastl::move(command));
    }
}

void RenderModule::submit_command_buffers() noexcept {
    m_render_semaphore.wait();
    m_update_queue.push(eastl::move(m_command_buffer));
    m_update_semaphore.post();
}

RenderingBackend* const RenderModule::get_rendering_backend() const noexcept {
    return m_renderer.get();
}

const RenderingBackendType RenderModule::get_rendering_backend_type() noexcept {
    return m_renderer_type;
}

} // namespace kw

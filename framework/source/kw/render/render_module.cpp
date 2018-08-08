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
#include <kw/render/internal/backend_opengl.h>
#include <kw/render/render_module.h>

#include <SDL2/SDL_video.h>

namespace kw {
namespace render_module_details {
constexpr uint32 COMMAND_BUFFER_QUEUE_SIZE = 2;
} // namespace render_module_details

RenderModule::RenderModule(IGame* game) noexcept
    : m_render_semaphore(render_module_details::COMMAND_BUFFER_QUEUE_SIZE)
    , is_thread_active(true) {
    game->on_init.connect(this, &RenderModule::on_init_listener);
    game->on_destroy.connect(this, &RenderModule::on_destroy_listener);

    // TODO: Here we do some crazy calculations to understand what backend we're going to run on.
    m_backend_type = render::Backend::Type::OPENGL;
}

RenderModule::~RenderModule() = default;

void RenderModule::on_init_listener(IGame* game) noexcept(false) {
    m_thread = Thread([this, game] {
        // TODO: try-catch here
        switch (m_backend_type) {
            case render::Backend::Type::OPENGL:
                m_backend = eastl::make_unique<render::BackendOpenGL>(game);
                break;
            default:
                break;
        }

        while (is_thread_active) {
            m_update_semaphore.wait();
            render::CommandBuffers buffers;
            if (!m_command_buffers_queue.is_empty()) {
                m_command_buffers_queue.pop(buffers);
            }
            m_render_semaphore.post();
            // TODO: try-catch here
            m_backend->process_command_buffer(buffers);
        }
    });
}

void RenderModule::on_destroy_listener(IGame*) noexcept {
    is_thread_active = false;
    // We might be waiting for an update notification, which would never happen if we join the thread.
    m_update_semaphore.post();
    m_thread.join();
}

void RenderModule::push_command_buffer(render::CommandBuffer&& command_buffer) noexcept {
    m_command_buffers.push_back(eastl::move(command_buffer));
}

void RenderModule::submit_command_buffers() noexcept {
    m_render_semaphore.wait();
    m_command_buffers_queue.push(eastl::move(m_command_buffers));
    m_update_semaphore.post();
}

const render::Backend::Type RenderModule::get_rendering_backend_type() noexcept {
    return m_backend_type;
}
} // namespace kw

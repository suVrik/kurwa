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
#include <kw/render/render_module.h>
#include <kw/render/rendering_backend.h>
#include <kw/render/backend_gl.h>

#include <SDL2/SDL_video.h>
#include <kw/core/scene_module.h>

namespace kw {

RenderModule::RenderModule(kw::IGame* game) noexcept {
    game->on_init.connect(this, &RenderModule::on_init_listener);
}

void RenderModule::on_init_listener(kw::IGame* game) noexcept(false) {
    auto& window_module = game->get<kw::WindowModule>();
    m_window = window_module.get_window();
    switch (m_renderer_type) {
        case RenderingBackendType::OPENGL:
            m_renderer = eastl::make_unique<render::BackendGl>(game);
            break;
        case RenderingBackendType::VULKAN:
            break;
        default:
            break;
    }
}

RenderingBackend* const RenderModule::get_renderer() const noexcept {
    return m_renderer.get();
}

const RenderingBackendType RenderModule::get_renderer_type() noexcept {
    return m_renderer_type;
}

} // namespace kw

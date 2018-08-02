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
#include <kw/core/scene_module.h>
#include <kw/render/render_module.h>

namespace kw {
SceneModule::SceneModule(IGame* game) noexcept {
    game->on_init.connect(this, &SceneModule::on_init_listener);
    game->on_update.connect(this, &SceneModule::on_update_listener);
    game->on_destroy.connect(this, &SceneModule::on_destroy_listener);
}

void SceneModule::on_init_listener(kw::IGame *game) noexcept(false) {
    auto& scene_module = game->get<RenderModule>();
    m_renderer = scene_module.get_renderer();
    m_thread = Thread([this]() {
        for (unsigned short i = 0; i < VIRTUAL_FRAMES_NUMBER; i++) {
            m_render_semaphore.post();
        }

        while (is_update_thread_active) {
            m_render_semaphore.wait();

            render::CommandBuffer command_buffer;
            render::Command command {};
            command.clear.type = kw::render::CommandType::CLEAR;
            command.clear.r = 0.9f / sinf(std::time(nullptr) % 10);
            command.clear.g = 0.9f;
            command.clear.b = 0.9f;
            command.clear.a = 1.f;
            command_buffer.commands.push_back(command);

            m_update_queue.push(eastl::move(command_buffer));
            m_update_semaphore.post();
        }
    });
}

void SceneModule::on_update_listener() noexcept(false) {
    m_update_semaphore.wait();
    kw::render::CommandBuffer buffer = m_update_queue.front();
    m_update_queue.pop();
    m_render_semaphore.post();
    m_renderer->process_command_buffer(eastl::move(buffer));
}

void SceneModule::on_destroy_listener(kw::IGame *game) noexcept {
    is_update_thread_active = false;
    m_thread.detach();
}

} // namespace kw

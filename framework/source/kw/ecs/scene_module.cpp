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
#include <kw/ecs/scene_module.h>
#include <kw/render/render_module.h>

namespace kw {
SceneModule::SceneModule(IGame* game) noexcept
    : is_update_thread_active(true) {
    game->on_init.connect(this, &SceneModule::on_init_listener);
    game->on_destroy.connect(this, &SceneModule::on_destroy_listener);
}

void SceneModule::on_init_listener(IGame* game) noexcept {
    auto& render_module = game->get<RenderModule>();
    m_thread = Thread([&render_module, this]() {
        render::CommandBuffer command_buffer;
        render::Command command;
        command.type = render::CommandType::INIT_2D;
        command_buffer.commands.push_back(eastl::move(command));
        render_module.push_command_buffer(eastl::move(command_buffer));

        on_init.emit(this);

        while (is_update_thread_active) {
            on_update.emit(this);

            render_module.submit_command_buffers();
        }
        on_destroy.emit(this);
    });
}

void SceneModule::on_destroy_listener(IGame* game) noexcept {
    is_update_thread_active = false;
    m_thread.detach();
}

} // namespace kw

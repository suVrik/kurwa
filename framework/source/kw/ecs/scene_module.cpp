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
SceneModule::SceneModule(IGame* game) noexcept {
    game->on_init.connect(this, &SceneModule::on_init_listener);
    game->on_update.connect(this, &SceneModule::on_update_listener);
}

void SceneModule::on_init_listener(IGame* game) noexcept {
    m_render_module = &game->get<RenderModule>();
}

void SceneModule::on_update_listener() noexcept {
    m_render_module->submit_command_buffers();
}
} // namespace kw

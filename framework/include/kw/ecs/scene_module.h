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

union SDL_Event;
struct SDL_Window;

namespace kw {
class IGame;
class RenderModule;

/**
 * Scene module creates an update loop, records and stores the commands to be sent to a rendering backend.
 */
class SceneModule : public SignalListener {
public:
    explicit SceneModule(IGame* game) noexcept;
    SceneModule(const SceneModule& original) = delete;
    SceneModule& operator=(const SceneModule& original) = delete;

private:
    void on_init_listener(IGame* game) noexcept;
    void on_update_listener() noexcept;

    RenderModule* m_render_module;
};
} // namespace kw

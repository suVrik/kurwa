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

#include <kw/base/array.h>
#include <kw/base/signal.h>
#include <kw/base/string.h>
#include <kw/render/commands.h>

struct SDL_Window;

namespace kw {
class IGame;

/**
 * RenderingBackend class provides methods to interact with GPU and to output visuals to the screen.
 * The class is abstract from any underlying platform-dependent graphics API.
 */
class RenderingBackend : public SignalListener {
public:
    virtual ~RenderingBackend() = default;

    /**
     * Execute the commands in a command buffer and present the resulting image.
     */
    virtual void process_command_buffer(render::CommandBuffer&& command_buffer) = 0;
protected:
    RenderingBackend() = default;

    virtual void on_init_listener(kw::IGame* game) noexcept(false);

    SDL_Window* m_window;
};
} // namespace kw

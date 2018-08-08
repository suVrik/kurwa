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
#include <kw/render/internal/backend.h>

struct SDL_Window;

namespace kw {
class IGame;

namespace render {
/**
 * BackendOpenGL is a class that translates rendering API-agnostic `Command` into real OpenGL commands.
 */
class BackendOpenGL : public Backend, public SignalListener {
public:
    explicit BackendOpenGL(IGame* game) noexcept(false);
    BackendOpenGL(const BackendOpenGL& original) = delete;
    ~BackendOpenGL();
    BackendOpenGL& operator=(const BackendOpenGL& original) = delete;

    /**
     * Execute the commands in a command buffer and present the resulting image to the screen.
     */
    void process_command_buffer(CommandBuffers& command_buffers) noexcept(false) override;

private:
    SDL_Window* m_window;
    void* m_context;
};
} // namespace render
} // namespace kw

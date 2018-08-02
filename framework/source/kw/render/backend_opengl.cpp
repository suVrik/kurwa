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
#include <kw/debug/runtime_error.h>
#include <kw/render/backend_opengl.h>

#include <GL/glew.h>

#include <SDL2/SDL_video.h>

namespace kw {
namespace render {

BackendOpenGL::BackendOpenGL(kw::IGame* game) noexcept {
    game->on_init.connect(this, &BackendOpenGL::on_init_listener);
};

void BackendOpenGL::on_init_listener(kw::IGame* game) noexcept(false) {
    RenderingBackend::on_init_listener(game);

    SDL_GL_CreateContext(m_window);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        throw RuntimeError(fmt::format("Failed to initialize GLEW!\nThe error message: {}", glewGetErrorString(err)));
    }
}

void BackendOpenGL::process_command_buffer(CommandBuffer&& command_buffer) noexcept {
    for (Command& command : command_buffer.commands) {
        switch (command.type) {
            case CommandType::CLEAR:
                glClearColor(command.clear.r, command.clear.g, command.clear.b, command.clear.a);
                glClear(GL_COLOR_BUFFER_BIT);
                break;
        }
    }

    SDL_GL_SwapWindow(m_window);
}

} // namespace render
} // namespace kw

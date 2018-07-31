#include <kw/core/i_game.h>
#include <kw/render/renderer_gl.h>
#include <GL/glew.h>
#include <SDL2/SDL_video.h>

namespace kw {
namespace render {
RendererGl::RendererGl(kw::IGame* game) noexcept : Renderer(game) {
    game->on_init.connect(this, &RendererGl::on_init_listener);
};

void RendererGl::on_init_listener(kw::IGame* game) {
    Renderer::on_init_listener(game);
    SDL_GL_CreateContext(m_window);
    SDL_GL_SetSwapInterval(1);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
}

void RendererGl::process_command_buffer(CommandBuffer& command_buffer) {
    for (render::Command& command : command_buffer.commands) {
        switch (command.type) {
            case render::CommandType::CLEAR:
                glClearColor(command.clear.r, command.clear.g, command.clear.b, command.clear.a);
                glClear(GL_COLOR_BUFFER_BIT);
                break;
        }
    }

    SDL_GL_SwapWindow(m_window);
}
}
}


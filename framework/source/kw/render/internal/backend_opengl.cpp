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
#include <kw/debug/runtime_error.h>
#include <kw/render/internal/backend_opengl.h>
#include <kw/render/internal/commands.h>

#include <GL/glew.h>
#include <SDL2/SDL_video.h>

namespace kw::render {
namespace backend_opengl_details {
void check_shader_compilation_status(GLuint handle) noexcept(false) {
    GLint success;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        GLint log_length;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_length);
        Vector<char> log(static_cast<uint32>(log_length));
        glGetShaderInfoLog(handle, log_length, nullptr, log.data());
        throw RuntimeError(fmt::format("Shader compilation failed!\nThe error message: {}", log.data()));
    }
}

void check_program_link_status(GLuint handle) noexcept(false) {
    GLint success;
    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if (success == 0) {
        GLint log_length;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &log_length);
        Vector<char> log(static_cast<uint32>(log_length));
        glGetProgramInfoLog(handle, log_length, nullptr, log.data());
        throw RuntimeError(fmt::format("Failed to link a shader!\nThe error message: {}", log.data()));
    }
}

void process_command(Command& command) noexcept(false) {
    switch (command.type) {
        case CommandType::CLEAR:
            glClearColor(command.clear.r, command.clear.g, command.clear.b, command.clear.a);
            glClear(GL_COLOR_BUFFER_BIT);
            break;
        case CommandType::CREATE_VERTEX_BUFFER:
            glGenVertexArrays(1, command.create_vertex_buffer.vao_id);
            glGenBuffers(1, command.create_vertex_buffer.vbo_id);
            break;
        case CommandType::UPDATE_VERTEX_BUFFER:
            glBufferData(GL_ARRAY_BUFFER, command.update_vertex_buffer.size, command.update_vertex_buffer.data.data(),
                         GL_STREAM_DRAW);
            break;
        case CommandType::BIND_VERTEX_BUFFER:
            KW_ASSERT(command.bind_vertex_buffer.vao_id != nullptr || command.bind_vertex_buffer.vbo_id != nullptr,
                      "You forgot to attach a vertex buffer handle!");
            glBindVertexArray(*command.bind_vertex_buffer.vao_id);
            glBindBuffer(GL_ARRAY_BUFFER, *command.bind_vertex_buffer.vbo_id);
            break;
        case CommandType::CREATE_INDEX_BUFFER:
            glGenBuffers(1, command.create_index_buffer.id);
            break;
        case CommandType::UPDATE_INDEX_BUFFER:
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, command.update_index_buffer.size,
                         command.update_index_buffer.data.data(), GL_STREAM_DRAW);
            break;
        case CommandType::BIND_INDEX_BUFFER:
            KW_ASSERT(command.bind_index_buffer.id != nullptr, "You forgot to attach an index buffer handle!");
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *command.bind_index_buffer.id);
            break;
        case CommandType::CREATE_TEXTURE: {
            glGenTextures(1, command.create_texture.id);
            glBindTexture(GL_TEXTURE_2D, *command.create_texture.id);
            GLint param;
            switch (command.create_texture.texture_filtering) {
                case TextureFiltering::NEAREST:
                    param = GL_NEAREST;
                    break;
                case TextureFiltering::LINEAR:
                    param = GL_LINEAR;
                    break;
            }
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
            glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
            GLint pixel_data_type;
            switch (command.create_texture.pixel_data_type) {
                case PixelDataType::RGBA:
                    pixel_data_type = GL_RGBA;
                    break;
            }
            glTexImage2D(GL_TEXTURE_2D, 0, pixel_data_type, command.create_texture.width, command.create_texture.height,
                         0, GL_RGBA, GL_UNSIGNED_BYTE, command.create_texture.pixels);
            break;
        }
        case CommandType::BIND_TEXTURE:
            KW_ASSERT(command.bind_texture.id != nullptr, "You forgot to attach a texture handle!");
            glBindTexture(GL_TEXTURE_2D, *command.bind_texture.id);
            break;
        case CommandType::CREATE_PROGRAM: {
            uint32 vertex_shader_id = *command.create_program.vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex_shader_id, 1, &command.create_program.vertex_shader_code, nullptr);
            glCompileShader(vertex_shader_id);
            check_shader_compilation_status(vertex_shader_id);

            uint32 fragment_shader_id = *command.create_program.fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment_shader_id, 1, &command.create_program.fragment_shader_code, nullptr);
            glCompileShader(fragment_shader_id);
            check_shader_compilation_status(fragment_shader_id);

            uint32 program_id = *command.create_program.shader_program_id = glCreateProgram();
            glAttachShader(program_id, vertex_shader_id);
            glAttachShader(program_id, fragment_shader_id);
            glLinkProgram(program_id);
            check_program_link_status(program_id);
            break;
        }
        case CommandType::BIND_PROGRAM:
            KW_ASSERT(command.bind_program.id != nullptr, "You forgot to attach a shader program handle!");
            glUseProgram(*command.bind_program.id);
            break;
        case CommandType::DRAW_INDEXED:
            glDrawElements(GL_TRIANGLES, command.draw_indexed.size, GL_UNSIGNED_SHORT, command.draw_indexed.data);
            break;
        case CommandType::CREATE_VERTEX_ATTRIBUTE: {
            auto m_attribute_position = static_cast<uint32>(
                glGetAttribLocation(*command.create_vertex_attribute.shader_program_id,
                                    command.create_vertex_attribute.name));
            glEnableVertexAttribArray(m_attribute_position);
            GLenum type;
            switch (command.create_vertex_attribute.type) {
                case AttributeType::FLOAT:
                    type = GL_FLOAT;
                    break;
                case AttributeType::UNSIGNED_BYTE:
                    type = GL_UNSIGNED_BYTE;
                    break;
            }
            glVertexAttribPointer(m_attribute_position, command.create_vertex_attribute.size, type, GL_TRUE,
                                  command.create_vertex_attribute.stride,
                                  reinterpret_cast<const void*>(command.create_vertex_attribute.offset));
            break;
        }
        case CommandType::GET_UNIFORM_LOCATION:
            KW_ASSERT(command.get_uniform_location.shader_program_id != nullptr,
                      "You forgot to attach a shader program handle!");
            *command.get_uniform_location.id = static_cast<uint32>(
                glGetUniformLocation(*command.get_uniform_location.shader_program_id,
                                     command.get_uniform_location.name));
            break;
        case CommandType::UPDATE_UNIFORM_MATRIX_4F:
            KW_ASSERT(command.update_uniform_matrix_4f.id != nullptr, "You forgot to attach a uniform handle!");
            glUniformMatrix4fv(
                *command.update_uniform_matrix_4f.id, 1, GL_FALSE, command.update_uniform_matrix_4f.matrix.data());
            break;
        case CommandType::INIT_2D:
            glEnable(GL_BLEND);
            glBlendEquation(GL_FUNC_ADD);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glDisable(GL_CULL_FACE);
            glDisable(GL_DEPTH_TEST);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case CommandType::SCISSOR:
            glScissor(command.scissor.x, command.scissor.y, command.scissor.width, command.scissor.height);
            break;
        case CommandType::SWITCH_CAPABILITY_STATUS: {
            GLenum capability;
            switch (command.switch_capability_status.capability) {
                case Capability::SCISSOR_TEST:
                    capability = GL_SCISSOR_TEST;
                    break;
            }
            if (command.switch_capability_status.enable) {
                glEnable(capability);
            } else {
                glDisable(capability);
            }
            break;
        }
        default:
            break;
    }
}
} // namespace backend_opengl_details

BackendOpenGL::BackendOpenGL(IGame* game) noexcept(false) {
    auto& window_module = game->get<WindowModule>();
    m_window = window_module.get_window();

    m_context = SDL_GL_CreateContext(m_window);
    if (m_context == nullptr) {
        throw RuntimeError(fmt::format("Failed to create OpenGL context!\nThe error message: {}", SDL_GetError()));
    }

    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        throw RuntimeError(fmt::format("Failed to initialize GLEW!\nThe error message: {}", glewGetErrorString(err)));
    }
}

BackendOpenGL::~BackendOpenGL() {
    SDL_GL_DeleteContext(m_context);
}

void BackendOpenGL::process_command_buffer(render::CommandBuffers& command_buffers) noexcept(false) {
    for (CommandBuffer& command_buffer : command_buffers) {
        for (Command& command : command_buffer) {
            backend_opengl_details::process_command(command);
        }
    }

    SDL_GL_SwapWindow(m_window);
}
} // namespace kw::render

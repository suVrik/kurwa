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

BackendOpenGL::BackendOpenGL(IGame* game) noexcept {
    game->on_init.connect(this, &BackendOpenGL::on_init_listener);
};

void BackendOpenGL::on_init_listener(IGame* game) noexcept(false) {
    RenderingBackend::on_init_listener(game);

    SDL_GL_CreateContext(m_window);
    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        throw RuntimeError(fmt::format("Failed to initialize GLEW!\nThe error message: {}", glewGetErrorString(err)));
    }
}

static void check_shader_compilation_status(GLuint handle) {
    GLint success;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        GLint log_length;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<char> log(static_cast<unsigned>(log_length));
        glGetShaderInfoLog(handle, log_length, nullptr, log.data());
        throw RuntimeError(fmt::format("Shader compilation failed!\nThe error message: {}", log.data()));
    }
}

static void check_program_link_status(GLuint handle) {
    GLint success;
    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if (success == 0) {
        GLint log_length;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<char> log(static_cast<unsigned>(log_length));
        glGetProgramInfoLog(handle, log_length, nullptr, log.data());
        throw std::runtime_error("ERROR: Shader linking failed!\n" + std::string(log.data()) + "\n");
    }
}

void BackendOpenGL::process_command_buffer(CommandBuffer&& command_buffer) noexcept {
    for (Command& command : command_buffer.commands) {
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
                glBufferData(GL_ARRAY_BUFFER, command.update_vertex_buffer.size,
                             static_cast<const void*>(command.update_vertex_buffer.data.data()), GL_STREAM_DRAW);
                break;
            case CommandType::BIND_VERTEX_BUFFER:
                if (command.bind_vertex_buffer.vao_id == nullptr || command.bind_vertex_buffer.vbo_id == nullptr) {
                    glBindVertexArray(0);
                    glBindBuffer(GL_ARRAY_BUFFER, 0);
                } else {
                    glBindVertexArray(*command.bind_vertex_buffer.vao_id);
                    glBindBuffer(GL_ARRAY_BUFFER, *command.bind_vertex_buffer.vbo_id);
                }
                break;
            case CommandType::CREATE_INDEX_BUFFER:
                glGenBuffers(1, command.create_index_buffer.id);
                break;
            case CommandType::UPDATE_INDEX_BUFFER:
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, command.update_index_buffer.size,
                             static_cast<const void*>(command.update_index_buffer.data.data()), GL_STREAM_DRAW);
                break;
            case CommandType::BIND_INDEX_BUFFER:
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *command.bind_index_buffer.id);
                break;
            case CommandType::CREATE_TEXTURE:
                glGenTextures(1, command.create_texture.id);
                glBindTexture(GL_TEXTURE_2D, *command.create_texture.id);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, command.create_texture.width, command.create_texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                             command.create_texture.pixels);
                break;
            case CommandType::BIND_TEXTURE:
                glBindTexture(GL_TEXTURE_2D, command.bind_texture.id);
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
                glUseProgram(*command.bind_program.id);
                break;
            case CommandType::DRAW_INDEXED:
                glDrawElements(GL_TRIANGLES, command.draw_indexed.size, GL_UNSIGNED_SHORT, command.draw_indexed.data);
                break;
            case CommandType::CREATE_VERTEX_ATTRIBUTE: {
                auto m_attribute_position = static_cast<uint32>(glGetAttribLocation(
                    *command.create_vertex_attribute.shader_program_id, command.create_vertex_attribute.name));
                glEnableVertexAttribArray(m_attribute_position);
                GLenum type;
                switch (command.create_vertex_attribute.type) {
                    case AttributeType::FLOAT:
                        type = GL_FLOAT;
                        break;
                    case AttributeType::UNSIGNED_BYTE:
                        type = GL_UNSIGNED_BYTE;
                        break;
                    default:
                        type = GL_DOUBLE;
                        break;
                }
                glVertexAttribPointer(m_attribute_position, command.create_vertex_attribute.size, type, GL_TRUE,
                                      command.create_vertex_attribute.stride, (GLvoid*)command.create_vertex_attribute.offset);
                break;
            }
            case CommandType::GET_UNIFORM_LOCATION:
                *command.get_uniform_location.id = static_cast<uint32>(
                    glGetUniformLocation(*command.get_uniform_location.shader_program_id, command.get_uniform_location.name));
                break;
            case CommandType::UPDATE_UNIFORM_MATRIX_4F:
                glUniformMatrix4fv(
                    *command.update_uniform_matrix_4f.id, 1, GL_FALSE, command.update_uniform_matrix_4f.matrix.data());
                break;
            case CommandType::INIT_IMGUI:
                glEnable(GL_BLEND);
                glBlendEquation(GL_FUNC_ADD);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glDisable(GL_CULL_FACE);
                glDisable(GL_DEPTH_TEST);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                break;
            default:
                break;
        }
    }

    SDL_GL_SwapWindow(m_window);
}

} // namespace render
} // namespace kw

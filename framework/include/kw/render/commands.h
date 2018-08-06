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

#include <kw/base/string.h>
#include <kw/base/types.h>
#include <kw/base/vector.h>

namespace kw {
namespace render {

enum class CommandType {
    CLEAR,

    CREATE_VERTEX_BUFFER,
    UPDATE_VERTEX_BUFFER,
    BIND_VERTEX_BUFFER,

    CREATE_INDEX_BUFFER,
    UPDATE_INDEX_BUFFER,
    BIND_INDEX_BUFFER,

    CREATE_TEXTURE,
    BIND_TEXTURE,

    CREATE_PROGRAM,
    BIND_PROGRAM,

    DRAW_INDEXED,

    CREATE_VERTEX_ATTRIBUTE,
    GET_UNIFORM_LOCATION,
    UPDATE_UNIFORM_MATRIX_4F,
    INIT_IMGUI,
};

struct CommandClear {
    float r;
    float g;
    float b;
    float a;
};

struct CommandCreateVertexBuffer {
    uint32* vao_id;
    uint32* vbo_id;
};

struct CommandUpdateVertexBuffer {
    uint32 size;
    Vector<float> data;
};

struct CommandBindVertexBuffer {
    uint32* vao_id;
    uint32* vbo_id;
};

struct CommandCreateIndexBuffer {
    uint32* id;
};

struct CommandUpdateIndexBuffer {
    uint32 size;
    Vector<uint16> data;
};

struct CommandBindIndexBuffer {
    uint32* id;
};

struct CommandCreateTexture {
    uint32* id;
    uint32 width;
    uint32 height;
    unsigned char* pixels;
};

struct CommandBindTexture {
    uint32 id;
};

struct CommandCreateProgram {
    uint32* shader_program_id;
    uint32* vertex_shader_id;
    const char* vertex_shader_code;
    uint32* fragment_shader_id;
    const char* fragment_shader_code;
};

struct CommandBindProgram {
    uint32* id;
};

enum class AttributeType { FLOAT, UNSIGNED_BYTE };

struct CommandCreateVertexAttribute {
    uint32* shader_program_id;
    AttributeType type;
    const char* name;
    uint32 size;
    uint32 stride;
    size_t offset;
};

struct CommandGetUniformLocation {
    uint32* id;
    uint32* shader_program_id;
    const char* name;
};

struct CommandUpdateUniformMatrix4f {
    uint32* id;
    Vector<float> matrix;
};

struct CommandDrawIndexed {
    uint32 size;
    const void* data;
};

struct Command {
    Command() noexcept {
    }

    Command(const Command& original) = delete;
    Command& operator=(const Command& original) = delete;

    Command(Command&& original) noexcept
        : type(original.type) {
        switch (type) {
            case CommandType::UPDATE_INDEX_BUFFER:
                update_index_buffer = eastl::move(original.update_index_buffer);
                break;
            case CommandType::UPDATE_VERTEX_BUFFER:
                update_vertex_buffer = eastl::move(original.update_vertex_buffer);
                break;
            case CommandType::UPDATE_UNIFORM_MATRIX_4F:
                update_uniform_matrix_4f = eastl::move(original.update_uniform_matrix_4f);
                break;
            default:
                memcpy(this, &original, sizeof(Command));
        }
        original.type = CommandType::CLEAR;
    }

    Command& operator=(Command&& original) = delete;

    ~Command() {
        switch (type) {
            case CommandType::UPDATE_INDEX_BUFFER:
                update_index_buffer.~CommandUpdateIndexBuffer();
                break;
            case CommandType::UPDATE_VERTEX_BUFFER:
                update_vertex_buffer.~CommandUpdateVertexBuffer();
                break;
            case CommandType::UPDATE_UNIFORM_MATRIX_4F:
                update_uniform_matrix_4f.~CommandUpdateUniformMatrix4f();
                break;
            default:
                // Other command structures do not require destruction.
                break;
        }
    }

    CommandType type = CommandType::CLEAR;

    union {
        CommandClear clear;

        CommandCreateVertexBuffer create_vertex_buffer;
        CommandUpdateVertexBuffer update_vertex_buffer;
        CommandBindVertexBuffer bind_vertex_buffer;

        CommandCreateIndexBuffer create_index_buffer;
        CommandUpdateIndexBuffer update_index_buffer;
        CommandBindIndexBuffer bind_index_buffer;

        CommandDrawIndexed draw_indexed;

        CommandCreateProgram create_program;
        CommandBindProgram bind_program;

        CommandCreateTexture create_texture;
        CommandBindTexture bind_texture;

        CommandCreateVertexAttribute create_vertex_attribute;
        CommandGetUniformLocation get_uniform_location;
        CommandUpdateUniformMatrix4f update_uniform_matrix_4f;
    };
};

struct CommandBuffer {
    Vector<Command> commands;
};

} // namespace render
} // namespace kw

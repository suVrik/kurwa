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

#include <kw/base/types.h>
#include <kw/base/vector.h>

namespace kw {
namespace render {

enum class CommandType {
    CLEAR,

    CREATE_VERTEX_BUFFER,
    UPDATE_VERTEX_BUFFER,
    BIND_VERTEX_BUFFER,

    UPDATE_INDEX_BUFFER,
    BIND_INDEX_BUFFER,

    BIND_TEXTURE,
    BIND_PROGRAM,

    DRAW_INDEXED,

    UPDATE_UNIFORM_MATRIX_4f,

    INIT_IMGUI,

};

struct CommandClear {
    float r;
    float g;
    float b;
    float a;
};

// TODO remove type ???
struct CommandCreateVertexBuffer {};

struct CommandInitImgui {};

struct CommandUpdateVertexBuffer {
    uint32 size;
    Vector<float> data;
};

struct CommandBindVertexBuffer {
    uint32 vao_id;
    uint32 vbo_id;
};

struct CommandCreateIndexBuffer {};

struct CommandUpdateIndexBuffer {
    uint32 size;
    Vector<uint16> data;
};

struct CommandBindIndexBuffer {
    uint32 id;
};

struct CommandDrawIndexed {
    uint32 size;
    const void* data;
};

struct CommandBindProgram {
    uint32 id;
};

struct CommandBindTexture {
    uint32 id;
};

// TODO to uniform buffer
struct CommandUpdateUniformMatrix4f {
    uint32 id;
    Vector<float> matrix;
};

struct Command {
    Command() {
    }

    Command(const Command& original) = delete;
    Command& operator=(const Command& original) = delete;

    Command(Command&& original)
        : type(original.type) {
        switch (type) {
            case CommandType::UPDATE_INDEX_BUFFER:
                update_index_buffer = eastl::move(original.update_index_buffer);
                break;
            case CommandType::UPDATE_VERTEX_BUFFER:
                update_vertex_buffer = eastl::move(original.update_vertex_buffer);
                break;
            case CommandType::UPDATE_UNIFORM_MATRIX_4f:
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
            case CommandType::UPDATE_UNIFORM_MATRIX_4f:
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
        CommandBindProgram bind_program;
        CommandBindTexture bind_texture;
        CommandUpdateUniformMatrix4f update_uniform_matrix_4f;
        CommandInitImgui init_imgui;
    };
};

struct CommandBuffer {
    Vector<Command> commands;
};

} // namespace render
} // namespace kw

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
    CommandType type;
    float r;
    float g;
    float b;
    float a;
};

//TODO remove type ???
struct CommandCreateVertexBuffer {
    CommandType type;
};

struct CommandInitImgui {
    CommandType type;
};

struct CommandUpdateVertexBuffer {
    CommandType type;
    uint32 size;
    const void* data;
};

struct CommandBindVertexBuffer {
    CommandType type;
    uint32 vao_id;
    uint32 vbo_id;
};

struct CommandCreateIndexBuffer {
    CommandType type;
};

struct CommandUpdateIndexBuffer {
    CommandType type;
    uint32 size;
    const void* data;
};

struct CommandBindIndexBuffer {
    CommandType type;
    uint32 id;
};

struct CommandDrawIndexed {
    CommandType type;
    uint32 size;
    const void* data;
};

struct CommandBindProgram {
    CommandType type;
    uint32 id;
};

struct CommandBindTexture {
    CommandType type;
    uint32 id;
};

//TODO to uniform buffer
struct CommandUpdateUniformMatrix4f {
    CommandType type;
    uint32 id;
    const float* matrix;
};

union Command {
    CommandType type;
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

struct CommandBuffer {
    Vector<Command> commands;
};

} // namespace render
} // namespace kw

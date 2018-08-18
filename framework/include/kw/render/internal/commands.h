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
#include <kw/render/internal/types.h>

namespace kw::render {
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
    INIT_2D,
    SCISSOR,
    SWITCH_CAPABILITY_STATUS,
};

struct CommandClear final {
    float r;
    float g;
    float b;
    float a;
};

struct CommandCreateVertexBuffer final {
    VertexArrayHandle* vao_id;
    VertexBufferHandle* vbo_id;
};

struct CommandUpdateVertexBuffer final {
    uint32 size;
    Vector<float> data;
};

struct CommandBindVertexBuffer final {
    VertexArrayHandle* vao_id;
    VertexBufferHandle* vbo_id;
};

struct CommandCreateIndexBuffer final {
    IndexBufferHandle* id;
};

struct CommandUpdateIndexBuffer final {
    uint32 size;
    Vector<uint16> data;
};

struct CommandBindIndexBuffer final {
    IndexBufferHandle* id;
};

enum class TextureFiltering {
    LINEAR,
    NEAREST,
};

enum class PixelDataType {
    RGBA,
};

struct CommandCreateTexture final {
    TextureHandle* id;
    uint32 width;
    uint32 height;
    unsigned char* pixels;
    TextureFiltering texture_filtering;
    PixelDataType pixel_data_type;
};

struct CommandBindTexture final {
    TextureHandle* id;
};

struct CommandCreateProgram final {
    ShaderProgramHandle* shader_program_id;
    ShaderHandle* vertex_shader_id;
    const char* vertex_shader_code;
    ShaderHandle* fragment_shader_id;
    const char* fragment_shader_code;
};

struct CommandBindProgram final {
    ShaderProgramHandle* id;
};

enum class AttributeType {
    FLOAT,
    UNSIGNED_BYTE,
};

struct CommandCreateVertexAttribute final {
    ShaderProgramHandle* shader_program_id;
    AttributeType type;
    const char* name;
    uint32 size;
    uint32 stride;
    size_t offset;
};

struct CommandGetUniformLocation final {
    UniformLocationHandle* id;
    ShaderProgramHandle* shader_program_id;
    const char* name;
};

struct CommandUpdateUniformMatrix4f final {
    UniformLocationHandle* id;
    Vector<float> matrix;
};

struct CommandDrawIndexed final {
    uint32 size;
    const void* data;
};

struct CommandScissor final {
    uint32 x;
    uint32 y;
    uint32 width;
    uint32 height;
};

enum class Capability {
    SCISSOR_TEST,
};

struct CommandSwitchCapabilityStatus final {
    Capability capability;
    bool enable;
};

struct Command final {
    Command() noexcept;

    Command(const Command& original) = delete;
    Command& operator=(const Command& original) = delete;
    ~Command() noexcept;
    Command(Command&& original) noexcept;
    Command& operator=(Command&& original) noexcept;

    CommandType type;

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
        CommandScissor scissor;
        CommandSwitchCapabilityStatus switch_capability_status;
    };
};

typedef Vector<Command> CommandBuffer;
typedef Vector<CommandBuffer> CommandBuffers;
} // namespace kw::render

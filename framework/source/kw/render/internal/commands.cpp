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

#include <kw/render/internal/commands.h>

namespace kw::render {

Command::Command() noexcept {
}

Command::Command(Command&& original) noexcept
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

Command::~Command() noexcept {
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

Command& Command::operator=(Command&& original) noexcept {
    this->~Command();
    new (this) Command(eastl::move(original));
    return *this;
}
} // namespace kw::render

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

namespace kw::render {
typedef uint32 Handle;
typedef Handle ShaderHandle;
typedef Handle ShaderProgramHandle;
typedef Handle TextureHandle;
typedef Handle VertexArrayHandle;
typedef Handle VertexBufferHandle;
typedef Handle IndexBufferHandle;
typedef Handle UniformLocationHandle;

inline ShaderHandle NO_SHADER = 0;
inline ShaderProgramHandle NO_SHADER_PROGRAM = 0;
inline TextureHandle NO_TEXTURE = 0;
inline VertexArrayHandle NO_VERTEX_ARRAY = 0;
inline VertexBufferHandle NO_VERTEX_BUFFER = 0;
inline IndexBufferHandle NO_INDEX_BUFFER = 0;
inline UniformLocationHandle NO_UNIFORM_LOCATION = 0;
} // namespace kw::render

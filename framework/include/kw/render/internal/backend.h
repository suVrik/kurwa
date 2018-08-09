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

#include <kw/render/internal/commands.h>

namespace kw::render {
/**
 * Backend class provides an interface to interact with GPU in rendering API agnostic way.
 */
class Backend {
public:
    /**
     * Backend::Type represents all supported rendering backends.
     */
    enum class Type {
        OPENGL,
    };

    /**
     * Execute the given `command_buffers` and present the resulting image on the screen.
     */
    virtual void process_command_buffer(CommandBuffers& command_buffers) noexcept(false) = 0;
};
} // namespace kw::render

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

#include <kw/render/rendering_backend.h>

namespace kw {
namespace render {

/**
 * BackendOpenGL is a class that implements OpenGL rendering backend.
 */
class BackendOpenGL : public RenderingBackend {
public:
    explicit BackendOpenGL(IGame* game) noexcept;
    BackendOpenGL(const BackendOpenGL& original) = delete;
    BackendOpenGL& operator=(const BackendOpenGL& original) = delete;

    /**
     * Execute the commands in a command buffer and present the resulting image to the screen.
     */
    void process_command_buffer(CommandBuffer&& command_buffer) noexcept override;

private:
    void on_init_listener(IGame* game) noexcept(false) override;
};

} // namespace render
} // namespace kw

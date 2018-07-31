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

#include "renderer.h"

namespace kw {
namespace render {

class RendererGl : public Renderer {
public:
    /**
     * Construct a RendererGl instance using the given 'game' as an event-emitter.
     */
    explicit RendererGl(kw::IGame* game) noexcept;
    RendererGl(const RendererGl& original) = delete;
    RendererGl& operator=(const RendererGl& original) = delete;

    void on_init_listener(kw::IGame* game) override;
    void process_command_buffer(CommandBuffer& command_buffer) override;
};

} // namespace render
} // namespace kw

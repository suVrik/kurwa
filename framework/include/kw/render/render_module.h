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

#include <kw/base/list.h>
#include <kw/base/optional.h>
#include <kw/base/signal.h>
#include <kw/base/unique_ptr.h>
#include "renderer.h"

namespace kw {

enum class RendererType {
    OPENGL,
    VULKAN
};

class IGame;

/**
 * Render module provides access to the render implementation.
 */
class RenderModule final : public SignalListener {
public:
    /**
     * Construct a render module using the given 'game' instance.
     */
    explicit RenderModule(kw::IGame* game) noexcept;

    RenderModule(const RenderModule& original) = delete;

    RenderModule& operator=(const RenderModule& original) = delete;

    void on_init_listener(kw::IGame* game);

    /**
     * Return a renderer instance.
     */
    Renderer* const get_renderer() const noexcept;

    /**
     * Return a specified renderer type.
     */
    const RendererType get_renderer_type() noexcept;

private:
    UniquePtr<Renderer> m_renderer;
    SDL_Window* m_window;
    RendererType m_renderer_type = RendererType::VULKAN;
};

} // namespace kw
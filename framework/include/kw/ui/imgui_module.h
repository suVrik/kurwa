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

#include <kw/base/signal.h>
#include <kw/base/types.h>
#include <kw/render/internal/types.h>

union SDL_Event;
struct SDL_Window;

namespace kw {
class IGame;
class SceneModule;
class RenderModule;
class WindowModule;

/**
 * Imgui module creates everything needed to create and manage GUI using "Dear ImGui" library.
 */
class ImguiModule final : public SignalListener {
public:
    explicit ImguiModule(IGame* game) noexcept;
    ImguiModule(const ImguiModule& original) = delete;
    ImguiModule& operator=(const ImguiModule& original) = delete;

private:
    void on_init_listener(IGame* game) noexcept;
    void on_update_listener() noexcept;
    void on_draw_listener() noexcept;
    void on_event_listener(SDL_Event& event) noexcept;

    RenderModule* m_render_module;
    WindowModule* m_window_module;

    bool is_left_click_pressed = false;
    uint64 m_time;
    render::TextureHandle m_font_texture_id = 0;
    render::ShaderProgramHandle m_shader_program_id = 0;
    render::ShaderHandle m_vertex_shader_id = 0;
    render::ShaderHandle m_fragment_shader_id = 0;
    render::UniformLocationHandle m_attribution_texture_id = 0;
    render::UniformLocationHandle m_attribution_projection_matrix = 0;
    render::VertexArrayHandle m_vao_id = 0;
    render::VertexBufferHandle m_vbo_id = 0;
    render::IndexBufferHandle m_index_buffer_id = 0;
};
} // namespace kw

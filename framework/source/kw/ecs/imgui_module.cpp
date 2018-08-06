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

#include <kw/core/i_game.h>
#include <kw/core/window_module.h>
#include <kw/ecs/imgui_module.h>
#include <kw/ecs/scene_module.h>
#include <kw/render/render_module.h>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <imgui/imgui.h>

namespace kw {
ImguiModule::ImguiModule(IGame* game) noexcept
    : m_time(0) {
    game->on_init.connect(this, &ImguiModule::on_init_listener);
    game->on_event.connect(this, &ImguiModule::on_event_listener);
}

void ImguiModule::on_event_listener(SDL_Event& event) noexcept {
    ImGuiIO& io = ImGui::GetIO();
    switch (event.type) {
        case SDL_MOUSEWHEEL: {
            if (event.wheel.x > 0)
                io.MouseWheelH += 1;
            if (event.wheel.x < 0)
                io.MouseWheelH -= 1;
            if (event.wheel.y > 0)
                io.MouseWheel += 1;
            if (event.wheel.y < 0)
                io.MouseWheel -= 1;
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            if (event.button.button == SDL_BUTTON_LEFT)
                is_left_click_pressed = true;
            break;
        }
        case SDL_TEXTINPUT: {
            io.AddInputCharactersUTF8(event.text.text);
            break;
        }
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            int key = event.key.keysym.scancode;
            IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown));
            io.KeysDown[key] = (event.type == SDL_KEYDOWN);
            io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
            io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
            io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
            io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
            break;
        }
        default:
            break;
    }
}

void ImguiModule::on_init_listener(IGame* game) noexcept {
    m_render_module = &game->get<RenderModule>();
    game->get<SceneModule>().on_populate_render_queue.connect(this, &ImguiModule::on_populate_render_queue_listener);
    m_window = game->get<WindowModule>().get_window();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    const char* vertex_shader_glsl_410_core = "#version 330 core\n"
                                              "layout (location = 0) in vec2 Position;\n"
                                              "layout (location = 1) in vec2 UV;\n"
                                              "layout (location = 2) in vec4 Color;\n"
                                              "uniform mat4 ProjMtx;\n"
                                              "out vec2 Frag_UV;\n"
                                              "out vec4 Frag_Color;\n"
                                              "void main()\n"
                                              "{\n"
                                              "    Frag_UV = UV;\n"
                                              "    Frag_Color = Color;\n"
                                              "    gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
                                              "}\n";

    const char* fragment_shader_glsl_410_core = "#version 330 core\n"
                                                "in vec2 Frag_UV;\n"
                                                "in vec4 Frag_Color;\n"
                                                "uniform sampler2D Texture;\n"
                                                "layout (location = 0) out vec4 Out_Color;\n"
                                                "void main()\n"
                                                "{\n"
                                                "    Out_Color = Frag_Color * texture(Texture, Frag_UV.st);\n"
                                                "}\n";

    render::CommandBuffer command_buffer;

    render::Command command_create_shader_program{};
    command_create_shader_program.type = kw::render::CommandType::CREATE_PROGRAM;
    command_create_shader_program.create_program.shader_program_id = &m_shader_program_id;
    command_create_shader_program.create_program.vertex_shader_id = &m_vertex_shader_id;
    command_create_shader_program.create_program.vertex_shader_code = vertex_shader_glsl_410_core;
    command_create_shader_program.create_program.fragment_shader_id = &m_fragment_shader_id;
    command_create_shader_program.create_program.fragment_shader_code = fragment_shader_glsl_410_core;
    command_buffer.commands.push_back(eastl::move(command_create_shader_program));

    render::Command command_bind_shader_program{};
    command_bind_shader_program.type = kw::render::CommandType::BIND_PROGRAM;
    command_bind_shader_program.bind_program.id = &m_shader_program_id;
    command_buffer.commands.push_back(eastl::move(command_bind_shader_program));

    ImGuiIO& io = ImGui::GetIO();
    // Build texture atlas
    unsigned char* pixels;
    int width, height;
    // Load as RGBA 32-bits (75% of the memory is wasted, but default font is so small)
    // because it is more likely to be compatible with user's existing shaders.
    // If your ImTextureId represent a higher-level concept than just a GL texture id,
    // consider calling GetTexDataAsAlpha8() instead to save on GPU memory.
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    render::Command command_create_texture{};
    command_create_texture.type = kw::render::CommandType::CREATE_TEXTURE;
    command_create_texture.create_texture.id = &m_font_texture_id;
    command_create_texture.create_texture.width = static_cast<uint32>(width);
    command_create_texture.create_texture.height = static_cast<uint32>(height);
    command_create_texture.create_texture.pixels = pixels;
    command_buffer.commands.push_back(eastl::move(command_create_texture));

    // Store our identifier
    io.Fonts->TexID = &m_font_texture_id;

    // Create buffers
    render::Command command_create_index_buffer{};
    command_create_index_buffer.type = kw::render::CommandType::CREATE_INDEX_BUFFER;
    command_create_index_buffer.create_index_buffer.id = &m_index_buffer_id;
    command_buffer.commands.push_back(eastl::move(command_create_index_buffer));

    render::Command command_create_vertex_buffer{};
    command_create_vertex_buffer.type = kw::render::CommandType::CREATE_VERTEX_BUFFER;
    command_create_vertex_buffer.create_vertex_buffer.vao_id = &m_vao_id;
    command_create_vertex_buffer.create_vertex_buffer.vbo_id = &m_vbo_id;
    command_buffer.commands.push_back(eastl::move(command_create_vertex_buffer));

    render::Command command_bind_vertex_buffer1{};
    command_bind_vertex_buffer1.type = kw::render::CommandType::BIND_VERTEX_BUFFER;
    command_bind_vertex_buffer1.bind_vertex_buffer.vao_id = &m_vao_id;
    command_bind_vertex_buffer1.bind_vertex_buffer.vbo_id = &m_vbo_id;
    command_buffer.commands.push_back(eastl::move(command_bind_vertex_buffer1));

    render::Command command_get_uniform_location1{};
    command_get_uniform_location1.type = kw::render::CommandType::GET_UNIFORM_LOCATION;
    command_get_uniform_location1.get_uniform_location.shader_program_id = &m_shader_program_id;
    command_get_uniform_location1.get_uniform_location.id = &m_attribution_texture_id;
    command_get_uniform_location1.get_uniform_location.name = "Texture";
    command_buffer.commands.push_back(eastl::move(command_get_uniform_location1));

    render::Command command_get_uniform_location2{};
    command_get_uniform_location2.type = kw::render::CommandType::GET_UNIFORM_LOCATION;
    command_get_uniform_location2.get_uniform_location.shader_program_id = &m_shader_program_id;
    command_get_uniform_location2.get_uniform_location.id = &m_attribution_projection_matrix;
    command_get_uniform_location2.get_uniform_location.name = "ProjMtx";
    command_buffer.commands.push_back(eastl::move(command_get_uniform_location2));

    render::Command command_create_vertex_attribute1{};
    command_create_vertex_attribute1.type = render::CommandType::CREATE_VERTEX_ATTRIBUTE;
    command_create_vertex_attribute1.create_vertex_attribute.shader_program_id = &m_shader_program_id;
    command_create_vertex_attribute1.create_vertex_attribute.name = "Position";
    command_create_vertex_attribute1.create_vertex_attribute.type = render::AttributeType::FLOAT;
    command_create_vertex_attribute1.create_vertex_attribute.size = 2;
    command_create_vertex_attribute1.create_vertex_attribute.stride = sizeof(ImDrawVert);
    command_create_vertex_attribute1.create_vertex_attribute.offset = IM_OFFSETOF(ImDrawVert, pos);
    command_buffer.commands.push_back(eastl::move(command_create_vertex_attribute1));

    render::Command command_create_vertex_attribute2{};
    command_create_vertex_attribute2.type = render::CommandType::CREATE_VERTEX_ATTRIBUTE;
    command_create_vertex_attribute2.create_vertex_attribute.shader_program_id = &m_shader_program_id;
    command_create_vertex_attribute2.create_vertex_attribute.name = "UV";
    command_create_vertex_attribute2.create_vertex_attribute.type = render::AttributeType::FLOAT;
    command_create_vertex_attribute2.create_vertex_attribute.size = 2;
    command_create_vertex_attribute2.create_vertex_attribute.stride = sizeof(ImDrawVert);
    command_create_vertex_attribute2.create_vertex_attribute.offset = IM_OFFSETOF(ImDrawVert, uv);
    command_buffer.commands.push_back(eastl::move(command_create_vertex_attribute2));

    render::Command command_create_vertex_attribute3{};
    command_create_vertex_attribute3.type = kw::render::CommandType::CREATE_VERTEX_ATTRIBUTE;
    command_create_vertex_attribute3.create_vertex_attribute.shader_program_id = &m_shader_program_id;
    command_create_vertex_attribute3.create_vertex_attribute.name = "Color";
    command_create_vertex_attribute3.create_vertex_attribute.type = render::AttributeType::UNSIGNED_BYTE;
    command_create_vertex_attribute3.create_vertex_attribute.size = 4;
    command_create_vertex_attribute3.create_vertex_attribute.stride = sizeof(ImDrawVert);
    command_create_vertex_attribute3.create_vertex_attribute.offset = IM_OFFSETOF(ImDrawVert, col);
    command_buffer.commands.push_back(eastl::move(command_create_vertex_attribute3));

    render::Command command_bind_vertex_buffer2{};
    command_bind_vertex_buffer2.type = kw::render::CommandType::BIND_VERTEX_BUFFER;
    command_bind_vertex_buffer2.bind_vertex_buffer.vao_id = nullptr;
    command_bind_vertex_buffer2.bind_vertex_buffer.vbo_id = nullptr;
    command_buffer.commands.push_back(eastl::move(command_bind_vertex_buffer2));

    m_render_module->push_command_buffer(eastl::move(command_buffer));
}

void ImguiModule::imgui_setup_frame() {
    ImGuiIO& io = ImGui::GetIO();
    // Font atlas needs to be built, call renderer _NewFrame() function e.g. ImGui_ImplOpenGL3_NewFrame()
    IM_ASSERT(io.Fonts->IsBuilt());
    // Setup display size (every frame to accommodate for window resizing)
    int w, h;
    int display_w, display_h;
    SDL_GetWindowSize(m_window, &w, &h);
    SDL_GL_GetDrawableSize(m_window, &display_w, &display_h);
    io.DisplaySize = ImVec2((float)w, (float)h);
    io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float)display_w / w) : 0, h > 0 ? ((float)display_h / h) : 0);
    // Setup time step (we don't use SDL_GetTicks() because it is using millisecond resolution)
    static Uint64 frequency = SDL_GetPerformanceFrequency();
    Uint64 current_time = SDL_GetPerformanceCounter();
    io.DeltaTime = m_time > 0 ? (float)((double)(current_time - m_time) / frequency) : (1.0f / 60.0f);
    m_time = current_time;

    io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);

    int mx, my;
    Uint32 mouse_buttons = SDL_GetMouseState(&mx, &my);
    // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events
    // that are shorter than 1 frame.
    io.MouseDown[0] = is_left_click_pressed || (mouse_buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
    is_left_click_pressed = false;

    if (SDL_GetWindowFlags(m_window) & SDL_WINDOW_INPUT_FOCUS) {
        io.MousePos = ImVec2((float)mx, (float)my);
    }

    ImGui::NewFrame();

    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);
}

void ImguiModule::on_populate_render_queue_listener(SceneModule* scene_module) noexcept {
    imgui_setup_frame();

    render::CommandBuffer command_buffer;

    ImGui::Render();

    ImDrawData* draw_data = ImGui::GetDrawData();
    // Avoid rendering when minimized, scale coordinates for retina displays
    // (screen coordinates != framebuffer coordinates)
    ImGuiIO& io = ImGui::GetIO();
    int fb_width = (int)(draw_data->DisplaySize.x * io.DisplayFramebufferScale.x);
    int fb_height = (int)(draw_data->DisplaySize.y * io.DisplayFramebufferScale.y);
    if (fb_width <= 0 || fb_height <= 0)
        return;
    draw_data->ScaleClipRects(io.DisplayFramebufferScale);

    render::Command command_imgui_init{};
    command_imgui_init.type = kw::render::CommandType::INIT_IMGUI;
    command_buffer.commands.push_back(eastl::move(command_imgui_init));

    float L = draw_data->DisplayPos.x;
    float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
    float T = draw_data->DisplayPos.y;
    float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
    const float ortho_projection[4][4] = {
        { 2.0f / (R - L), 0.0f, 0.0f, 0.0f },
        { 0.0f, 2.0f / (T - B), 0.0f, 0.0f },
        { 0.0f, 0.0f, -1.0f, 0.0f },
        { (R + L) / (L - R), (T + B) / (B - T), 0.0f, 1.0f },
    };

    render::Command command_bind_shader_program{};
    command_bind_shader_program.type = kw::render::CommandType::BIND_PROGRAM;
    command_bind_shader_program.bind_program.id = &m_shader_program_id;
    command_buffer.commands.push_back(eastl::move(command_bind_shader_program));

    render::Command command_update_uniform_matrix{};
    command_update_uniform_matrix.type = kw::render::CommandType::UPDATE_UNIFORM_MATRIX_4F;
    command_update_uniform_matrix.update_uniform_matrix_4f.id = &m_attribution_projection_matrix;
    // TODO redo this after LD
    new (&command_update_uniform_matrix.update_uniform_matrix_4f.matrix) Vector<float>(&ortho_projection[0][0], &ortho_projection[0][0] + 16);
    command_buffer.commands.push_back(eastl::move(command_update_uniform_matrix));

    render::Command command_bind_vertex_buffer{};
    command_bind_vertex_buffer.type = kw::render::CommandType::BIND_VERTEX_BUFFER;
    command_bind_vertex_buffer.bind_vertex_buffer.vao_id = &m_vao_id;
    command_bind_vertex_buffer.bind_vertex_buffer.vbo_id = &m_vbo_id;
    command_buffer.commands.push_back(eastl::move(command_bind_vertex_buffer));

    ImVec2 pos = draw_data->DisplayPos;
    for (int n = 0; n < draw_data->CmdListsCount; n++) {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        const ImDrawIdx* idx_buffer_offset = nullptr;

        render::Command command_update_vertex_buffer{};
        command_update_vertex_buffer.type = kw::render::CommandType::UPDATE_VERTEX_BUFFER;
        command_update_vertex_buffer.update_vertex_buffer.size = cmd_list->VtxBuffer.Size * sizeof(ImDrawVert);
        // TODO redo this after LD
        auto* vertex_data = reinterpret_cast<float*>(cmd_list->VtxBuffer.Data);
        size_t vertex_size = cmd_list->VtxBuffer.Size * sizeof(ImDrawVert) / sizeof(float);
        new (&command_update_vertex_buffer.update_vertex_buffer.data) Vector<float>(vertex_data, vertex_data + vertex_size);
        command_buffer.commands.push_back(eastl::move(command_update_vertex_buffer));

        render::Command command_bind_index_buffer{};
        command_bind_index_buffer.type = kw::render::CommandType::BIND_INDEX_BUFFER;
        command_bind_index_buffer.bind_index_buffer.id = &m_index_buffer_id;
        command_buffer.commands.push_back(eastl::move(command_bind_index_buffer));

        render::Command command_update_index_buffer{};
        command_update_index_buffer.type = kw::render::CommandType::UPDATE_INDEX_BUFFER;
        command_update_index_buffer.update_index_buffer.size = cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx);
        // TODO redo this after LD
        new (&command_update_index_buffer.update_index_buffer.data)
            Vector<uint16>(cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Data + cmd_list->IdxBuffer.Size);
        command_buffer.commands.push_back(eastl::move(command_update_index_buffer));

        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback) {
                // User callback (registered via ImDrawList::AddCallback)
                pcmd->UserCallback(cmd_list, pcmd);
            } else {
                ImVec4 clip_rect =
                    ImVec4(pcmd->ClipRect.x - pos.x, pcmd->ClipRect.y - pos.y, pcmd->ClipRect.z - pos.x, pcmd->ClipRect.w - pos.y);
                if (clip_rect.x < fb_width && clip_rect.y < fb_height && clip_rect.z >= 0.0f && clip_rect.w >= 0.0f) {
                    render::Command command_bind_texture{};
                    command_bind_texture.type = kw::render::CommandType::BIND_TEXTURE;
                    command_bind_texture.bind_texture.id = (uint32)(intptr_t)pcmd->TextureId;
                    command_buffer.commands.push_back(eastl::move(command_bind_texture));

                    render::Command command_draw{};
                    command_draw.type = kw::render::CommandType::DRAW_INDEXED;
                    command_draw.draw_indexed.size = (uint32)pcmd->ElemCount;
                    command_draw.draw_indexed.data = idx_buffer_offset;
                    command_buffer.commands.push_back(eastl::move(command_draw));
                }
            }
            idx_buffer_offset += pcmd->ElemCount;
        }
    }

    m_render_module->push_command_buffer(eastl::move(command_buffer));
}
} // namespace kw

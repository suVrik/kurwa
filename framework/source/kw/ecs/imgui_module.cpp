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
#include <kw/ecs/scene_module.h>
#include <kw/ecs/imgui_module.h>
#include <kw/render/render_module.h>
#include <imgui/imgui.h>
#include <GL/glew.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_events.h>
#include <kw/core/window_module.h>
#include <iostream>

namespace kw {
ImguiModule::ImguiModule(IGame* game) noexcept : g_Time(0) {
    game->on_init.connect(this, &ImguiModule::on_init_listener);
    game->on_event.connect(this, &ImguiModule::on_event_listener);
    game->on_destroy.connect(this, &ImguiModule::on_destroy_listener);
}


void ImguiModule::on_event_listener(SDL_Event& event) noexcept {
    ImGuiIO& io = ImGui::GetIO();
    switch (event.type)
    {
        case SDL_MOUSEWHEEL:
        {
            if (event.wheel.x > 0) io.MouseWheelH += 1;
            if (event.wheel.x < 0) io.MouseWheelH -= 1;
            if (event.wheel.y > 0) io.MouseWheel += 1;
            if (event.wheel.y < 0) io.MouseWheel -= 1;
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            if (event.button.button == SDL_BUTTON_LEFT) g_MousePressed = true;
            break;
        }
        case SDL_TEXTINPUT:
        {
            io.AddInputCharactersUTF8(event.text.text);
            break;
        }
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
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




// If you get an error please report on github. You may try different GL context version or GLSL version.
/*static bool CheckShader(GLuint handle, const char* desc)
{
    GLint status = 0, log_length = 0;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_length);
    if (status == GL_FALSE)
        fprintf(stderr, "ERROR: ImGui_ImplOpenGL3_CreateDeviceObjects: failed to compile %s!\n", desc);
    if (log_length > 0)
    {
        ImVector<char> buf;
        buf.resize((int)(log_length + 1));
        glGetShaderInfoLog(handle, log_length, nullptr, (GLchar*)buf.begin());
        fprintf(stderr, "%s\n", buf.begin());
    }
    return status == GL_TRUE;
}

// If you get an error please report on github. You may try different GL context version or GLSL version.
static bool CheckProgram(GLuint handle, const char* desc)
{
    GLint status = 0, log_length = 0;
    glGetProgramiv(handle, GL_LINK_STATUS, &status);
    glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &log_length);
    if (status == GL_FALSE)
        fprintf(stderr, "ERROR: ImGui_ImplOpenGL3_CreateDeviceObjects: failed to link %s!\n", desc);
    if (log_length > 0)
    {
        ImVector<char> buf;
        buf.resize((int)(log_length + 1));
        glGetProgramInfoLog(handle, log_length, nullptr, (GLchar*)buf.begin());
        fprintf(stderr, "%s\n", buf.begin());
    }
    return status == GL_TRUE;
}*/

void ImguiModule::on_init_listener(IGame* game) noexcept {
    auto& render_module = game->get<RenderModule>();
    m_render_module = &render_module;
    auto& scene_module = game->get<SceneModule>();
    scene_module.on_populate_render_queue.connect(this, &ImguiModule::on_populate_render_queue_listener);


    m_window = game->get<WindowModule>().get_window();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();


    // Setup back-end capabilities flags
    ImGuiIO& io = ImGui::GetIO();
    g_MouseCursors[ImGuiMouseCursor_Arrow] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);


    // Setup style
    ImGui::StyleColorsDark();



    // Backup GL state
    GLint last_texture, last_array_buffer, last_vertex_array;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);

    glCreateShader(GL_VERTEX_SHADER);

    const GLchar* vertex_shader_glsl_410_core =
            "#version 330 core\n"
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

    const GLchar* fragment_shader_glsl_410_core =
            "#version 330 core\n"
            "in vec2 Frag_UV;\n"
            "in vec4 Frag_Color;\n"
            "uniform sampler2D Texture;\n"
            "layout (location = 0) out vec4 Out_Color;\n"
            "void main()\n"
            "{\n"
            "    Out_Color = Frag_Color * texture(Texture, Frag_UV.st);\n"
            "}\n";

    // Create shaders
    g_VertHandle = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(g_VertHandle, 1, &vertex_shader_glsl_410_core, nullptr);
    glCompileShader(g_VertHandle);
    //CheckShader(g_VertHandle, "vertex shader");

    g_FragHandle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(g_FragHandle, 1, &fragment_shader_glsl_410_core, nullptr);
    glCompileShader(g_FragHandle);
    //CheckShader(g_FragHandle, "fragment shader");

    g_ShaderHandle = glCreateProgram();
    glAttachShader(g_ShaderHandle, g_VertHandle);
    glAttachShader(g_ShaderHandle, g_FragHandle);
    glLinkProgram(g_ShaderHandle);
    //CheckProgram(g_ShaderHandle, "shader program");

    g_AttribLocationTex = glGetUniformLocation(g_ShaderHandle, "Texture");
    g_AttribLocationProjMtx = glGetUniformLocation(g_ShaderHandle, "ProjMtx");
    g_AttribLocationPosition = (unsigned) glGetAttribLocation(g_ShaderHandle, "Position");
    g_AttribLocationUV = (unsigned) glGetAttribLocation(g_ShaderHandle, "UV");
    g_AttribLocationColor = (unsigned) glGetAttribLocation(g_ShaderHandle, "Color");

    glUseProgram(g_ShaderHandle);
    glUniform1i(g_AttribLocationTex, 0);

    // Create buffers
    glGenBuffers(1, &g_VboHandle);
    glGenBuffers(1, &g_ElementsHandle);





    // Build texture atlas
    unsigned char* pixels;
    int width, height;
    // Load as RGBA 32-bits (75% of the memory is wasted, but default font is so small)
    // because it is more likely to be compatible with user's existing shaders.
    // If your ImTextureId represent a higher-level concept than just a GL texture id,
    // consider calling GetTexDataAsAlpha8() instead to save on GPU memory.
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    // Upload texture to graphics system
    glGenTextures(1, &g_FontTexture);
    glBindTexture(GL_TEXTURE_2D, g_FontTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    // Store our identifier
    io.Fonts->TexID = (void *)(intptr_t)g_FontTexture;


    // Create buffers
    //glGenBuffers(1, &g_VboHandle);
    //glGenBuffers(1, &g_ElementsHandle);

    // Recreate the VAO every time
    // (This is to easily allow multiple GL contexts.
    // VAO are not shared among GL contexts, and we don't track creation/deletion of windows so we don't have an obvious key to use to cache them.)
    glGenVertexArrays(1, &vao_handle);
    glBindVertexArray(vao_handle);
    glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
    glEnableVertexAttribArray(g_AttribLocationPosition);
    glEnableVertexAttribArray(g_AttribLocationUV);
    glEnableVertexAttribArray(g_AttribLocationColor);
    glVertexAttribPointer(g_AttribLocationPosition, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, pos));
    glVertexAttribPointer(g_AttribLocationUV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, uv));
    glVertexAttribPointer(g_AttribLocationColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, col));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void ImguiModule::on_populate_render_queue_listener(SceneModule* scene_module) noexcept {
    render::CommandBuffer command_buffer;


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
    io.DeltaTime = g_Time > 0 ? (float)((double)(current_time - g_Time) / frequency) : (1.0f / 60.0f);
    g_Time = current_time;


    // Set OS mouse position if requested (rarely used, only when ImGuiConfigFlags_NavEnableSetMousePos is enabled by user)
    if (io.WantSetMousePos)
        SDL_WarpMouseInWindow(m_window, (int)io.MousePos.x, (int)io.MousePos.y);
    else
        io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);

    int mx, my;
    Uint32 mouse_buttons = SDL_GetMouseState(&mx, &my);
    // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
    io.MouseDown[0] = g_MousePressed || (mouse_buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
    g_MousePressed = false;

    if (SDL_GetWindowFlags(m_window) & SDL_WINDOW_INPUT_FOCUS) {
        io.MousePos = ImVec2((float) mx, (float) my);
    }


    ImGui::NewFrame();

    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::Render();

    //ImGuiIO& io = ImGui::GetIO();
    ImDrawData* draw_data = ImGui::GetDrawData();
    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
    int fb_width = (int)(draw_data->DisplaySize.x * io.DisplayFramebufferScale.x);
    int fb_height = (int)(draw_data->DisplaySize.y * io.DisplayFramebufferScale.y);
    if (fb_width <= 0 || fb_height <= 0)
        return;
    draw_data->ScaleClipRects(io.DisplayFramebufferScale);


        render::Command command0 {};
        command0.init_imgui.type = kw::render::CommandType::INIT_IMGUI;
        command_buffer.commands.push_back(command0);

    float L = draw_data->DisplayPos.x;
    float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
    float T = draw_data->DisplayPos.y;
    float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
    const float ortho_projection[4][4] =
            {
                    { 2.0f/(R-L),   0.0f,         0.0f,   0.0f },
                    { 0.0f,         2.0f/(T-B),   0.0f,   0.0f },
                    { 0.0f,         0.0f,        -1.0f,   0.0f },
                    { (R+L)/(L-R),  (T+B)/(B-T),  0.0f,   1.0f },
            };


    //glUseProgram(g_ShaderHandle);
    render::Command command1 {};
    command1.bind_program.type = kw::render::CommandType::BIND_PROGRAM;
    command1.bind_program.id = g_ShaderHandle;
    command_buffer.commands.push_back(command1);

    //glUniformMatrix4fv(g_AttribLocationProjMtx, 1, GL_FALSE, &ortho_projection[0][0]);
    render::Command command2 {};
    command2.update_uniform_matrix_4f.type = kw::render::CommandType::UPDATE_UNIFORM_MATRIX_4f;
    command2.update_uniform_matrix_4f.id = (unsigned) g_AttribLocationProjMtx;
    command2.update_uniform_matrix_4f.matrix = &ortho_projection[0][0];
    command_buffer.commands.push_back(command2);

    //glBindSampler(0, 0); // We use combined texture/sampler state. Applications using GL 3.3 may set that otherwise.

    //glBindVertexArray(vao_handle);
    //glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
    render::Command command3 {};
    command3.bind_vertex_buffer.type = kw::render::CommandType::BIND_VERTEX_BUFFER;
    command3.bind_vertex_buffer.vao_id = vao_handle;
    command3.bind_vertex_buffer.vbo_id = g_VboHandle;
    command_buffer.commands.push_back(command3);

    ImVec2 pos = draw_data->DisplayPos;
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        const ImDrawIdx* idx_buffer_offset = nullptr;

        //glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
        render::Command command40 {};
        command40.bind_vertex_buffer.type = kw::render::CommandType::BIND_VERTEX_BUFFER;
        command40.bind_vertex_buffer.vao_id = vao_handle;
        command40.bind_vertex_buffer.vbo_id = g_VboHandle;
        command_buffer.commands.push_back(command40);
        //glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.Size * sizeof(ImDrawVert), (const GLvoid*)cmd_list->VtxBuffer.Data, GL_STREAM_DRAW);
        render::Command command4 {};
        command4.update_vertex_buffer.type = kw::render::CommandType::UPDATE_VERTEX_BUFFER;
        command4.update_vertex_buffer.size = cmd_list->VtxBuffer.Size * sizeof(ImDrawVert);
        command4.update_vertex_buffer.data = (const void*)cmd_list->VtxBuffer.Data;
        command_buffer.commands.push_back(command4);

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ElementsHandle);
        render::Command command5 {};
        command5.bind_index_buffer.type = kw::render::CommandType::BIND_INDEX_BUFFER;
        command5.bind_index_buffer.id = g_ElementsHandle;
        command_buffer.commands.push_back(command5);

        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx), (const GLvoid*)cmd_list->IdxBuffer.Data, GL_STREAM_DRAW);
        render::Command command6 {};
        command6.update_index_buffer.type = kw::render::CommandType::UPDATE_INDEX_BUFFER;
        command6.update_index_buffer.size = cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx);
        command6.update_index_buffer.data = (const void*)cmd_list->IdxBuffer.Data;
        command_buffer.commands.push_back(command6);

        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
        {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback)
            {
                // User callback (registered via ImDrawList::AddCallback)
                pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                ImVec4 clip_rect = ImVec4(pcmd->ClipRect.x - pos.x, pcmd->ClipRect.y - pos.y, pcmd->ClipRect.z - pos.x, pcmd->ClipRect.w - pos.y);
                if (clip_rect.x < fb_width && clip_rect.y < fb_height && clip_rect.z >= 0.0f && clip_rect.w >= 0.0f)
                {
                    // Apply scissor/clipping rectangle
                    //glScissor((int)clip_rect.x, (int)(fb_height - clip_rect.w), (int)(clip_rect.z - clip_rect.x), (int)(clip_rect.w - clip_rect.y));

                    // Bind texture, Draw
                    //glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
                    render::Command command7 {};
                    command7.bind_texture.type = kw::render::CommandType::BIND_TEXTURE;
                    command7.bind_texture.id = (GLuint)(intptr_t)pcmd->TextureId;
                    command_buffer.commands.push_back(command7);

                    //glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, GL_UNSIGNED_SHORT, idx_buffer_offset);
                    render::Command command8 {};
                    command8.draw_indexed.type = kw::render::CommandType::DRAW_INDEXED;
                    command8.draw_indexed.size = (GLsizei) pcmd->ElemCount;
                    command8.draw_indexed.data = idx_buffer_offset;
                    command_buffer.commands.push_back(command8);
                }
            }
            idx_buffer_offset += pcmd->ElemCount;
        }
    }

    m_render_module->push_command_buffer(eastl::move(command_buffer));
}

void ImguiModule::on_destroy_listener(IGame* game) noexcept {
}
} // namespace kw

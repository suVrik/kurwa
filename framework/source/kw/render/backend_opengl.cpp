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
#include <kw/debug/runtime_error.h>
#include <kw/render/backend_opengl.h>

#include <GL/glew.h>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <imgui/imgui.h>

namespace kw {
namespace render {

BackendOpenGL::BackendOpenGL(kw::IGame* game) noexcept {
    game->on_init.connect(this, &BackendOpenGL::on_init_listener);
    // game->on_event.connect(this, &BackendOpenGL::on_event_listener);
    RenderingBackend::on_init_listener(game);

    SDL_GL_CreateContext(m_window);
    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;
    GLenum err       = glewInit();
    if (err != GLEW_OK) {
        throw RuntimeError(fmt::format("Failed to initialize GLEW!\nThe error message: {}", glewGetErrorString(err)));
    }
};

void BackendOpenGL::on_init_listener(kw::IGame* game) noexcept(false) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup back-end capabilities flags
    ImGuiIO& io                            = ImGui::GetIO();
    g_MouseCursors[ImGuiMouseCursor_Arrow] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);

    // Setup style
    ImGui::StyleColorsDark();

    // Backup GL state
    GLint last_texture, last_array_buffer, last_vertex_array;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);

    glCreateShader(GL_VERTEX_SHADER);

    const GLchar* vertex_shader_glsl_410_core = "#version 330 core\n"
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

    const GLchar* fragment_shader_glsl_410_core = "#version 330 core\n"
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
    // CheckShader(g_VertHandle, "vertex shader");

    g_FragHandle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(g_FragHandle, 1, &fragment_shader_glsl_410_core, nullptr);
    glCompileShader(g_FragHandle);
    // CheckShader(g_FragHandle, "fragment shader");

    g_ShaderHandle = glCreateProgram();
    glAttachShader(g_ShaderHandle, g_VertHandle);
    glAttachShader(g_ShaderHandle, g_FragHandle);
    glLinkProgram(g_ShaderHandle);
    // CheckProgram(g_ShaderHandle, "shader program");

    g_AttribLocationTex      = glGetUniformLocation(g_ShaderHandle, "Texture");
    g_AttribLocationProjMtx  = glGetUniformLocation(g_ShaderHandle, "ProjMtx");
    g_AttribLocationPosition = (unsigned)glGetAttribLocation(g_ShaderHandle, "Position");
    g_AttribLocationUV       = (unsigned)glGetAttribLocation(g_ShaderHandle, "UV");
    g_AttribLocationColor    = (unsigned)glGetAttribLocation(g_ShaderHandle, "Color");

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
    io.Fonts->TexID = (void*)(intptr_t)g_FontTexture;

    // Recreate the VAO every time
    // (This is to easily allow multiple GL contexts.
    // VAO are not shared among GL contexts, and we don't track creation/deletion of windows so we don't have an obvious
    // key to use to cache them.)
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

    // Restore modified GL state
    /*glBindTexture(GL_TEXTURE_2D, (unsigned) last_texture);
    glBindBuffer(GL_ARRAY_BUFFER, (unsigned) last_array_buffer);
    glBindVertexArray((unsigned) last_vertex_array);

    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);*/
}

void BackendOpenGL::process_command_buffer(CommandBuffer&& command_buffer) noexcept {
    /*ImGuiIO& io = ImGui::GetIO();
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



    // Set OS mouse position if requested (rarely used, only when ImGuiConfigFlags_NavEnableSetMousePos is enabled by
    user) if (io.WantSetMousePos) SDL_WarpMouseInWindow(m_window, (int)io.MousePos.x, (int)io.MousePos.y); else io.MousePos
    = ImVec2(-FLT_MAX, -FLT_MAX);

    int mx, my;
    Uint32 mouse_buttons = SDL_GetMouseState(&mx, &my);
    // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events
    that are shorter than 1 frame. io.MouseDown[0] = g_MousePressed || (mouse_buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) !=
    0; g_MousePressed = false;

    if (SDL_GetWindowFlags(m_window) & SDL_WINDOW_INPUT_FOCUS) {
        io.MousePos = ImVec2((float) mx, (float) my);
    }



    ImGui::NewFrame();

    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::Render();


    ImDrawData* draw_data = ImGui::GetDrawData();
    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer
    coordinates) int fb_width = (int)(draw_data->DisplaySize.x * io.DisplayFramebufferScale.x); int fb_height =
    (int)(draw_data->DisplaySize.y * io.DisplayFramebufferScale.y); if (fb_width <= 0 || fb_height <= 0) return;
    draw_data->ScaleClipRects(io.DisplayFramebufferScale);*/

    // Backup GL state
    /*GLenum last_active_texture; glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint*)&last_active_texture);
    glActiveTexture(GL_TEXTURE0);
    GLint last_program; glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
    GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    GLint last_sampler; glGetIntegerv(GL_SAMPLER_BINDING, &last_sampler);
    GLint last_array_buffer; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
    GLint last_vertex_array; glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);
    GLint last_polygon_mode[2]; glGetIntegerv(GL_POLYGON_MODE, last_polygon_mode);
    GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
    GLint last_scissor_box[4]; glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);
    GLenum last_blend_src_rgb; glGetIntegerv(GL_BLEND_SRC_RGB, (GLint*)&last_blend_src_rgb);
    GLenum last_blend_dst_rgb; glGetIntegerv(GL_BLEND_DST_RGB, (GLint*)&last_blend_dst_rgb);
    GLenum last_blend_src_alpha; glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint*)&last_blend_src_alpha);
    GLenum last_blend_dst_alpha; glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint*)&last_blend_dst_alpha);
    GLenum last_blend_equation_rgb; glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint*)&last_blend_equation_rgb);
    GLenum last_blend_equation_alpha; glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint*)&last_blend_equation_alpha);
    GLboolean last_enable_blend = glIsEnabled(GL_BLEND);
    GLboolean last_enable_cull_face = glIsEnabled(GL_CULL_FACE);
    GLboolean last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);
    GLboolean last_enable_scissor_test = glIsEnabled(GL_SCISSOR_TEST);*/

    // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, polygon fill
    /*glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Setup viewport, orthographic projection matrix
    // Our visible imgui space lies from draw_data->DisplayPps (top left) to
    draw_data->DisplayPos+data_data->DisplaySize (bottom right). DisplayMin is typically (0,0) for single viewport apps.
    //glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
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
    glUseProgram(g_ShaderHandle);
    glUniformMatrix4fv(g_AttribLocationProjMtx, 1, GL_FALSE, &ortho_projection[0][0]);
    //glBindSampler(0, 0); // We use combined texture/sampler state. Applications using GL 3.3 may set that otherwise.

    glBindVertexArray(vao_handle);
    glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);*/

    for (Command& command : command_buffer.commands) {
        switch (command.type) {
            case CommandType::CLEAR:
                glClearColor(command.clear.r, command.clear.g, command.clear.b, command.clear.a);
                glClear(GL_COLOR_BUFFER_BIT);
                break;
            case CommandType::UPDATE_VERTEX_BUFFER:
                glBufferData(GL_ARRAY_BUFFER, command.update_vertex_buffer.size, command.update_vertex_buffer.data, GL_STREAM_DRAW);
                break;
            case CommandType::BIND_VERTEX_BUFFER:
                glBindVertexArray(command.bind_vertex_buffer.vao_id);
                glBindBuffer(GL_ARRAY_BUFFER, command.bind_vertex_buffer.vbo_id);
                break;
            case CommandType::UPDATE_INDEX_BUFFER:
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, command.update_index_buffer.size, command.update_index_buffer.data, GL_STREAM_DRAW);
                break;
            case CommandType::BIND_INDEX_BUFFER:
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, command.bind_index_buffer.id);
                break;
            case CommandType::BIND_TEXTURE:
                glBindTexture(GL_TEXTURE_2D, command.bind_texture.id);
                break;
            case CommandType::BIND_PROGRAM:
                glUseProgram(command.bind_program.id);
                break;
            case CommandType::DRAW_INDEXED:
                glDrawElements(GL_TRIANGLES, command.draw_indexed.size, GL_UNSIGNED_SHORT, command.draw_indexed.data);
                break;
            case CommandType::UPDATE_UNIFORM_MATRIX_4f:
                glUniformMatrix4fv(command.update_uniform_matrix_4f.id, 1, GL_FALSE, command.update_uniform_matrix_4f.matrix);
                break;
            case CommandType::INIT_IMGUI:
                glEnable(GL_BLEND);
                glBlendEquation(GL_FUNC_ADD);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glDisable(GL_CULL_FACE);
                glDisable(GL_DEPTH_TEST);
                glEnable(GL_SCISSOR_TEST);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                break;
            default:
                break;
        }
    }

    // Draw
    /*ImVec2 pos = draw_data->DisplayPos;
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        const ImDrawIdx* idx_buffer_offset = nullptr;

        glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.Size * sizeof(ImDrawVert), (const
    GLvoid*)cmd_list->VtxBuffer.Data, GL_STREAM_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ElementsHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx), (const
    GLvoid*)cmd_list->IdxBuffer.Data, GL_STREAM_DRAW);

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
                ImVec4 clip_rect = ImVec4(pcmd->ClipRect.x - pos.x, pcmd->ClipRect.y - pos.y, pcmd->ClipRect.z - pos.x,
    pcmd->ClipRect.w - pos.y); if (clip_rect.x < fb_width && clip_rect.y < fb_height && clip_rect.z >= 0.0f &&
    clip_rect.w >= 0.0f)
                {
                    // Apply scissor/clipping rectangle
                    //glScissor((int)clip_rect.x, (int)(fb_height - clip_rect.w), (int)(clip_rect.z - clip_rect.x),
    (int)(clip_rect.w - clip_rect.y));

                    // Bind texture, Draw
                    glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
                    glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, GL_UNSIGNED_SHORT, idx_buffer_offset);
                }
            }
            idx_buffer_offset += pcmd->ElemCount;
        }
    }
    //glDeleteVertexArrays(1, &vao_handle);*/

    // Restore modified GL state
    /*glUseProgram(last_program);
    glBindTexture(GL_TEXTURE_2D, last_texture);
    glBindSampler(0, last_sampler);
    glActiveTexture(last_active_texture);
    glBindVertexArray(last_vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
    glBlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
    glBlendFuncSeparate(last_blend_src_rgb, last_blend_dst_rgb, last_blend_src_alpha, last_blend_dst_alpha);
    if (last_enable_blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
    if (last_enable_cull_face) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
    if (last_enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
    if (last_enable_scissor_test) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, (GLenum)last_polygon_mode[0]);
    glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
    glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);*/

    SDL_GL_SwapWindow(m_window);
}

} // namespace render
} // namespace kw

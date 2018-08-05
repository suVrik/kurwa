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

#include <imgui/imgui.h>
#include "rendering_backend.h"

struct SDL_Cursor;
union SDL_Event;

namespace kw {
class RenderModule;
namespace render {

/**
 * BackendOpenGL is a class that implements OpenGL rendering backend.
 */
class BackendOpenGL : public RenderingBackend {
public:
    explicit BackendOpenGL(kw::IGame* game) noexcept;
    BackendOpenGL(const BackendOpenGL& original) = delete;
    BackendOpenGL& operator=(const BackendOpenGL& original) = delete;

    /**
     * Execute the commands in a command buffer and present the resulting image to the screen.
     */
    void process_command_buffer(CommandBuffer&& command_buffer) noexcept override;
private:
    void on_init_listener(kw::IGame* game) noexcept(false) override;
    //void on_event_listener(SDL_Event& event) noexcept;
    void on_init_finished_listener(RenderModule* game) noexcept(false);


    uint64 g_Time;
    SDL_Cursor*  g_MouseCursors[ImGuiMouseCursor_COUNT] = { 0 };
    bool         g_MousePressed = false;


    unsigned int       g_FontTexture = 0;
    unsigned int       g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
    int          g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;
    unsigned int          g_AttribLocationPosition = 0, g_AttribLocationUV = 0, g_AttribLocationColor = 0;
    unsigned int       vao_handle = 0;
    unsigned int g_VboHandle = 0, g_ElementsHandle = 0;
};

} // namespace render
} // namespace kw

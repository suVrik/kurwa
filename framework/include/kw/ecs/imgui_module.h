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

#include <SDL2/SDL_mouse.h>
#include <imgui/imgui.h>
#include <kw/base/queue.h>
#include <kw/base/signal.h>
#include <kw/base/string.h>
#include <kw/base/types.h>
#include <kw/concurrency/atomic.h>
#include <kw/concurrency/mutex.h>
#include <kw/concurrency/semaphore.h>
#include <kw/concurrency/thread.h>
#include <kw/render/commands.h>

union SDL_Event;
struct SDL_Window;

namespace kw {
class IGame;

class SceneModule;

class RenderModule;

class RenderingBackend;

/**
 * Scene module creates an update loop, records and stores the commands to be sent to a rendering backend.
 */
class ImguiModule : public SignalListener {
public:
    explicit ImguiModule(IGame* game) noexcept;
    ImguiModule(const ImguiModule& original) = delete;
    ImguiModule& operator=(const ImguiModule& original) = delete;

private:
    void on_init_listener(IGame* game) noexcept;
    void on_destroy_listener(IGame* game) noexcept;
    void on_populate_render_queue_listener(SceneModule* scene_module) noexcept;
    // kw::Function<void (render::CommandBuffer&& command_buffer)> m_push_command_buffer;
    void on_event_listener(SDL_Event& event) noexcept;
    RenderModule* m_render_module;

    uint64 g_Time;
    SDL_Cursor* g_MouseCursors[ImGuiMouseCursor_COUNT] = { 0 };
    bool g_MousePressed = false;

    unsigned int g_FontTexture = 0;
    unsigned int g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
    int g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;
    unsigned int g_AttribLocationPosition = 0, g_AttribLocationUV = 0, g_AttribLocationColor = 0;
    unsigned int vao_handle = 0;
    unsigned int g_VboHandle = 0, g_ElementsHandle = 0;

    SDL_Window* m_window;
};
} // namespace kw

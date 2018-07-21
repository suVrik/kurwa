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

#include <kw/core/window_module.h>
#include <kw/core/game_native.h>

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>

namespace kw {
WindowModule::WindowModule(GameNative* game)
        : m_title("Game")
        , m_width(800)
        , m_height(600) {
    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                m_width, m_height, SDL_WINDOW_SHOWN);

    if (m_window == nullptr) {
        // TODO: better description with libfmt
        throw std::runtime_error("Failed to initialize a window!");
    }

    // TODO: needs to be disconnected
    game->on_event.connect(this, &WindowModule::on_event_listener);
}

WindowModule::~WindowModule() {
    if (m_window != nullptr) {
        SDL_DestroyWindow(m_window);
    }
}

const String& WindowModule::get_title() const {
    return m_title;
}

void WindowModule::set_title(const String& value) {
    m_title = value;
    SDL_SetWindowTitle(m_window, m_title.c_str());
}

uint32 WindowModule::get_width() const {
    return m_width;
}

void WindowModule::set_width(uint32 value) {
    m_width = value;
    SDL_SetWindowSize(m_window, m_width, m_height);
}

uint32 WindowModule::get_height() const {
    return m_height;
}

void WindowModule::set_height(uint32 value) {
    m_height = value;
    SDL_SetWindowSize(m_window, m_width, m_height);
}

bool WindowModule::is_fullscreen() const {
    return m_is_fullscreen;
}

void WindowModule::set_fullscreen(bool value) {
    if (value) {
        if (SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP) == 0) {
            m_is_fullscreen = true;
        }
    } else {
        SDL_SetWindowFullscreen(m_window, 0);
    }

    // Generally doing this isn't a good practice. But I really doubt it returns negative values.
    SDL_GetWindowSize(m_window, reinterpret_cast<int*>(&m_width), reinterpret_cast<int*>(&m_height));
}

bool WindowModule::is_resizable() const {
    return m_is_resizable;
}

void WindowModule::set_resizable(bool value) {
    m_is_resizable = value;
    SDL_SetWindowResizable(m_window, m_is_resizable ? SDL_TRUE : SDL_FALSE);
}

bool WindowModule::has_focus() const {
    return m_has_focus;
}

bool WindowModule::is_restored() const {
    return m_is_restored;
}

void WindowModule::on_event_listener(SDL_Event& event) {
    if (event.type == SDL_WINDOWEVENT) {
        switch (event.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
                m_width = static_cast<uint32>(event.window.data1);
                m_height = static_cast<uint32>(event.window.data2);
                on_resize.emit(m_width, m_height);
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                m_is_restored = false;
                on_state_changed.emit(m_is_restored);
                break;
            case SDL_WINDOWEVENT_RESTORED:
                m_is_restored = true;
                on_state_changed.emit(m_is_restored);
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                m_has_focus = true;
                on_focus_changed.emit(m_has_focus);
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                m_has_focus = false;
                on_focus_changed.emit(m_has_focus);
                break;
            default:
                // Not interested in other events, but compiler forces to write this.
                break;
        }
    }
}
}

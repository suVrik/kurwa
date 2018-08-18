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
#include <kw/base/string.h>
#include <kw/base/types.h>

union SDL_Event;
struct SDL_Window;

namespace kw {
class IGame;

/**
 * Window module creates a window, stores its state and allows to tune it.
 */
class WindowModule final : public SignalListener {
public:
    /**
     * Create a window and subscribe to event messages from 'game'.
     */
    explicit WindowModule(IGame* game) noexcept;
    ~WindowModule() noexcept;

    WindowModule(const WindowModule& original) = delete;
    WindowModule& operator=(const WindowModule& original) = delete;

    /**
     * Return window's title. Default is "Game".
     */
    const String& get_title() const noexcept;

    /**
     * Change window's title.
     */
    void set_title(const String& value) noexcept;

    /**
     * Return window's width. Default is 800.
     */
    uint32 get_width() const noexcept;

    /**
     * Change window's width.
     */
    void set_width(uint32 value) noexcept;

    /**
     * Return window's height. Default is 600.
     */
    uint32 get_height() const noexcept;

    /**
     * Return SDL window.
     */
    SDL_Window* get_window() const noexcept;

    /**
     * Change window's height.
     */
    void set_height(uint32 value) noexcept;

    /**
     * Return true if the window is in fullscreen mode, otherwise return false. Default is false.
     */
    bool is_fullscreen() const noexcept;

    /**
     * Change window's fullscreen mode.
     */
    void set_fullscreen(bool value) noexcept;

    /**
     * Return true if the window is resizable, otherwise return false. Default is false.
     */
    bool is_resizable() const noexcept;

    /**
     * Change window's resizability (https://en.wiktionary.org/wiki/resizability).
     */
    void set_resizable(bool value) noexcept;

    /**
     * Return true if the window has focus, otherwise return false.
     */
    bool has_focus() const noexcept;

    /**
     * Return true if the window is restored, otherwise return false.
     */
    bool is_restored() const noexcept;

    Signal<void(uint32, uint32)> on_resize; /// Emitted when window is being resized.
    Signal<void(bool)> on_focus_changed; /// Emitted when window gains or loses focus.
    Signal<void(bool)> on_state_changed; /// Emitted when window is restored or minimized.

private:
    void on_init_listener(IGame* game) noexcept(false);
    void on_event_listener(SDL_Event& event) noexcept;

    SDL_Window* m_window;

    // Cache values for fast access.
    String m_title;
    uint32 m_width;
    uint32 m_height;
    bool m_is_fullscreen = false;
    bool m_is_resizable = false;
    bool m_has_focus = false;
    bool m_is_restored = true;
};
} // namespace kw
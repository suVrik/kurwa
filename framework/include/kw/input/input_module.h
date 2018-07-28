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
#include <kw/input/gamepad.h>
#include <kw/input/keyboard.h>
#include <kw/input/mouse.h>

union SDL_Event;

namespace kw {
class IGame;

/**
 * Input module provides access to input devices such as keyboard, mouse and gamepads.
 * It also manages gamepads and emits signals 'on_gamepad_added', 'on_gamepad_removed' and 'on_gamepad_remapped'.
 */
class InputModule final : public SignalListener {
public:
    /**
     * Construct an input module using the given 'game' instance.
     */
    explicit InputModule(IGame* game) noexcept;
    InputModule(const InputModule& original) = delete;
    InputModule& operator=(const InputModule& original) = delete;

    /**
     * Return keyboard instance.
     */
    Keyboard& get_keyboard() noexcept;
    const Keyboard& get_keyboard() const noexcept;

    /**
     * Return mouse instance.
     */
    Mouse& get_mouse() noexcept;
    const Mouse& get_mouse() const noexcept;

    /**
     * Return number of currently connected gamepads.
     */
    uint32 get_num_gamepads() const noexcept;

    /**
     * Return gamepad with the given 'index'.
     * Index must be less than a value returned by 'get_num_gamepads'.
     * Keep in mind that lifetime of the reference returned by this function is limited until 'on_gamepad_removed'
     * signal with the corresponding reference is emitted. Also keep in mind, that signal is not emitted when
     * input module is destroying (so only during 'on_event' callback).
     */
    Gamepad& get_gamepad(uint32 index) noexcept;
    const Gamepad& get_gamepad(uint32 index) const noexcept;

    Signal<void(Gamepad&)> on_gamepad_added;    /// Emitted after adding a gamepad.
    Signal<void(Gamepad&)> on_gamepad_removed;  /// Emitted before removing a gamepad.
    Signal<void(Gamepad&)> on_gamepad_remapped; /// Emitted when gamepad mapping updated.

private:
    void on_event_listener(SDL_Event& event) noexcept;
    List<Gamepad>::iterator get_gamepad(int32 device_index) noexcept;

    IGame* m_game;
    Keyboard m_keyboard;
    Mouse m_mouse;
    List<Gamepad> m_gamepads;
};
} // namespace kw

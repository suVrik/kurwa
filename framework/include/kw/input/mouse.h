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

#include <kw/base/array.h>
#include <kw/base/pair.h>
#include <kw/base/signal.h>
#include <kw/base/types.h>
#include <kw/input/control.h>

union SDL_Event;

namespace kw {
class IGame;

/**
 * This class represents a mouse interface.
 */
class Mouse final : public SignalListener {
public:
    /**
     * Construct a mouse interface using the given 'game' as an event-emitter.
     */
    explicit Mouse(IGame* game) noexcept;
    Mouse(const Mouse& original) = delete;
    Mouse& operator=(const Mouse& original) = delete;

    /**
     * Return true if the given 'button' was just pressed, otherwise return false.
     */
    bool is_pressed(Control button) const noexcept;

    /**
     * Return true if the given 'button' was just released, otherwise return false.
     */
    bool is_released(Control button) const noexcept;

    /**
     * Return true if the given 'button' is pressed, otherwise return false.
     */
    bool is_down(Control button) const noexcept;

    /**
     * Return the amount scrolled vertically, positive away from the user and negative toward the user.
     */
    int32 get_wheel() const noexcept;

    /**
     * Return the mouse position.
     */
    Pair<int32, int32> get_position() const noexcept;

private:
    enum class ButtonState : uint8 { NONE = 0b00U,
                                     DOWN = 0b01U,
                                     PRESSED = 0b11U,
                                     RELEASED = 0b10U };

    void on_event_listener(SDL_Event& event) noexcept;
    void on_update_listener() noexcept;

    Array<ButtonState, 5> m_buttons_back{};
    Array<ButtonState, 5> m_buttons{};
    Pair<int32, int32> m_position;
    int32 m_wheel_back = 0;
    int32 m_wheel = 0;
};
} // namespace kw

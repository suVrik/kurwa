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
class InputModule;

/**
 * This class represents a gamepad interface.
 */
class Gamepad final : public SignalListener {
public:
    /**
     * Construct a gamepad interface using the given 'game' as an event-emitter and
     * 'joystick_index' as a specific joystick this interface will reflect.
     */
    explicit Gamepad(IGame* game, int32 joystick_index) noexcept;
    Gamepad(const Gamepad& original) = delete;
    Gamepad& operator=(const Gamepad& original) = delete;

    /**
     * Return true if the given 'control' was just pressed, otherwise return false.
     */
    bool is_pressed(Control control) const noexcept;

    /**
     * Return true if the given 'control' was just released, otherwise return false.
     */
    bool is_released(Control control) const noexcept;

    /**
     * Return true if the given 'control' is pressed, otherwise return false.
     */
    bool is_down(Control control) const noexcept;

    /**
     * Return the analog control state of the given 'control'.
     */
    Pair<float, float> get_axis(Control control) const noexcept;

private:
    enum class ControlState : uint8 { NONE = 0b00U,
                                      DOWN = 0b01U,
                                      PRESSED = 0b11U,
                                      RELEASED = 0b10U };

    // TODO: This should be an option.
    static constexpr float TRIGGER_SENSITIVITY = 0.5f;

    void on_event_listener(SDL_Event& event) noexcept;
    void on_update_listener() noexcept;
    void handle_axis_motion(uint8 axis_index, int16 value) noexcept;

    Array<ControlState, 17> m_controls_back{};
    Array<ControlState, 17> m_controls{};
    Pair<float, float> m_axes[2]{};
    int32 m_instance_id = 0;

    friend class InputModule; // To access constructor and instance id.
};
} // namespace kw

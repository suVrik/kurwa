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

#include <kw/base/hash_map.h>
#include <kw/base/numeric_limits.h>
#include <kw/core/i_game.h>
#include <kw/debug/assert.h>
#include <kw/input/gamepad.h>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_joystick.h>

namespace kw {
namespace gamepad_details {
constexpr int32 FIRST_CONTROL = static_cast<int32>(Control::CONTROL_A);
constexpr int32 CONTROL_COUNT = static_cast<int32>(Control::CONTROL_TRIGGER_RIGHT) - FIRST_CONTROL + 1;

constexpr int32 FIRST_AXIS = static_cast<int32>(Control::AXIS_LEFT);
constexpr int32 AXES_COUNT = static_cast<int32>(Control::AXIS_RIGHT) - FIRST_CONTROL + 1;

HashMap<uint8, Control> controls_conversion = { { SDL_CONTROLLER_BUTTON_A, Control::CONTROL_A }, { SDL_CONTROLLER_BUTTON_B, Control::CONTROL_B }, { SDL_CONTROLLER_BUTTON_X, Control::CONTROL_X }, { SDL_CONTROLLER_BUTTON_Y, Control::CONTROL_Y }, { SDL_CONTROLLER_BUTTON_BACK, Control::CONTROL_BACK }, { SDL_CONTROLLER_BUTTON_GUIDE, Control::CONTROL_GUIDE }, { SDL_CONTROLLER_BUTTON_START, Control::CONTROL_START }, { SDL_CONTROLLER_BUTTON_LEFTSTICK, Control::CONTROL_LEFT_STICK }, { SDL_CONTROLLER_BUTTON_RIGHTSTICK, Control::CONTROL_RIGHT_STICK }, { SDL_CONTROLLER_BUTTON_LEFTSHOULDER, Control::CONTROL_LEFT_SHOULDER }, { SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, Control::CONTROL_RIGHT_SHOULDER }, { SDL_CONTROLLER_BUTTON_DPAD_UP, Control::CONTROL_DPAD_UP }, { SDL_CONTROLLER_BUTTON_DPAD_DOWN, Control::CONTROL_DPAD_DOWN }, { SDL_CONTROLLER_BUTTON_DPAD_LEFT, Control::CONTROL_DPAD_LEFT }, { SDL_CONTROLLER_BUTTON_DPAD_RIGHT, Control::CONTROL_DPAD_RIGHT } };

Control from_sdl_control(uint8 control) {
    auto result = controls_conversion.find(control);
    if (result != controls_conversion.end()) {
        return result->second;
    }
    return Control::CONTROL_UNKNOWN;
}
} // namespace gamepad_details

Gamepad::Gamepad(IGame* game, int32 joystick_index) noexcept {
    SDL_GameController* controller = SDL_GameControllerOpen(joystick_index);
    KW_ASSERT(controller != nullptr, "Invalid SDL controller!");

    SDL_Joystick* joystick = SDL_GameControllerGetJoystick(controller);

    m_instance_id = SDL_JoystickInstanceID(joystick);
    KW_ASSERT(m_instance_id >= 0, "Invalid joystick instance index!");

    game->on_event.connect(this, &Gamepad::on_event_listener);
    game->on_update.connect(this, &Gamepad::on_update_listener);
}

bool Gamepad::is_pressed(Control control) const noexcept {
    const auto index = static_cast<int32>(control) - gamepad_details::FIRST_CONTROL;

    KW_ASSERT(index >= 0 && index <= gamepad_details::CONTROL_COUNT, "Invalid control!");

    return m_controls[index] == ControlState::PRESSED;
}

bool Gamepad::is_released(Control control) const noexcept {
    const auto index = static_cast<int32>(control) - gamepad_details::FIRST_CONTROL;

    KW_ASSERT(index >= 0 && index <= gamepad_details::CONTROL_COUNT, "Invalid control!");

    return m_controls[index] == ControlState::RELEASED;
}

bool Gamepad::is_down(Control control) const noexcept {
    const auto index = static_cast<int32>(control) - gamepad_details::FIRST_CONTROL;

    KW_ASSERT(index >= 0 && index <= gamepad_details::CONTROL_COUNT, "Invalid control!");

    return (static_cast<uint8>(m_controls[index]) & 0b01U) != 0;
}

Pair<float, float> Gamepad::get_axis(Control control) const noexcept {
    const auto index = static_cast<int32>(control) - gamepad_details::FIRST_AXIS;

    KW_ASSERT(index >= 0 && index <= gamepad_details::AXES_COUNT, "Invalid control!");

    return m_axes[index];
}

void Gamepad::on_event_listener(SDL_Event& event) noexcept {
    switch (event.type) {
        case SDL_CONTROLLERAXISMOTION:
            if (event.caxis.which == m_instance_id) {
                handle_axis_motion(event.caxis.axis, event.caxis.value);
            }
            break;
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
            if (event.cbutton.which == m_instance_id) {
                const Control button = gamepad_details::from_sdl_control(event.cbutton.button);
                if (button != Control::CONTROL_UNKNOWN) {
                    const auto index = static_cast<int32>(button) - gamepad_details::FIRST_CONTROL;
                    if (event.type == SDL_CONTROLLERBUTTONDOWN) {
                        m_controls_back[index] = ControlState::PRESSED;
                    } else {
                        m_controls_back[index] = ControlState::RELEASED;
                    }
                }
            }
            break;
        default:
            // We're not interested in other events by now.
            break;
    }
}

void Gamepad::on_update_listener() noexcept {
    // Please, inspect the Keyboard::on_update_listener() to understand the back buffer approach in input module.
    eastl::copy_n(m_controls_back.data(), m_controls_back.size(), m_controls.data());
    for (auto& control_state : m_controls_back) {
        // RELEASED => NONE
        // PRESSED, DOWN => DOWN
        control_state = static_cast<ControlState>(static_cast<uint8>(control_state) & 0b01U);
    }
}

void Gamepad::handle_axis_motion(uint8 axis_index, int16 value) noexcept {
    // Left and right triggers right now are considered as controls, not axes.
    float floating_value = static_cast<float>(value) / NumericLimits<int16>::max();
    if (floating_value < -1.f) {
        floating_value = -1.f;
    }
    switch (axis_index) {
        case SDL_CONTROLLER_AXIS_LEFTX: {
            m_axes[static_cast<int32>(Control::AXIS_LEFT) - gamepad_details::FIRST_AXIS].first = floating_value;
            break;
        }
        case SDL_CONTROLLER_AXIS_LEFTY: {
            m_axes[static_cast<int32>(Control::AXIS_LEFT) - gamepad_details::FIRST_AXIS].second = floating_value;
            break;
        }
        case SDL_CONTROLLER_AXIS_RIGHTX: {
            m_axes[static_cast<int32>(Control::AXIS_RIGHT) - gamepad_details::FIRST_AXIS].first = floating_value;
            break;
        }
        case SDL_CONTROLLER_AXIS_RIGHTY: {
            m_axes[static_cast<int32>(Control::AXIS_RIGHT) - gamepad_details::FIRST_AXIS].second = floating_value;
            break;
        }
        case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
        case SDL_CONTROLLER_AXIS_TRIGGERRIGHT: {
            int32 index = -gamepad_details::FIRST_CONTROL;
            if (axis_index == SDL_CONTROLLER_AXIS_TRIGGERLEFT) {
                index += static_cast<int32>(Control::CONTROL_TRIGGER_LEFT);
            } else {
                index += static_cast<int32>(Control::CONTROL_TRIGGER_RIGHT);
            }
            if ((static_cast<uint8>(m_controls_back[index]) & 0b01U) != 0) {
                if (floating_value <= TRIGGER_SENSITIVITY) {
                    m_controls_back[index] = ControlState::RELEASED;
                }
            } else {
                if (floating_value > TRIGGER_SENSITIVITY) {
                    m_controls_back[index] = ControlState::PRESSED;
                }
            }
            break;
        }
        default:
            // We're not interested in other axes by now.
            break;
    }
}
} // namespace kw

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

#include <kw/debug/assert.h>
#include <kw/input/control.h>

#include "key_conversion.h"

#include <SDL2/SDL_keyboard.h>

namespace kw {
namespace control_details {
String get_key_name(Control control) {
    for (auto& key : keys_conversion) {
        if (key.second == control) {
            const SDL_Keycode keycode = SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(key.first));
            return SDL_GetKeyName(keycode);
        }
    }
    return "Unknown";
}
} // namespace control_details

String ControlUtils::get_control_name(Control control) noexcept {
    KW_ASSERT(static_cast<uint32>(control) <= static_cast<uint32>(GAMEPAD_AXES_END), "Invalid control!");

    switch (control) {
        case Control::CONTROL_UNKNOWN:
            return "Unknown";
        case Control::BUTTON_LEFT:
            return "Left Mouse Button";
        case Control::BUTTON_MIDDLE:
            return "Middle Mouse Button";
        case Control::BUTTON_RIGHT:
            return "Right Mouse Button";
        case Control::BUTTON_EXTRA_1:
            return "Extra 1 Mouse Button";
        case Control::BUTTON_EXTRA_2:
            return "Extra 2 Mouse Button";
        case Control::CONTROL_A:
            return "A";
        case Control::CONTROL_B:
            return "B";
        case Control::CONTROL_X:
            return "X";
        case Control::CONTROL_Y:
            return "Y";
        case Control::CONTROL_BACK:
            return "Back";
        case Control::CONTROL_GUIDE:
            return "Guide";
        case Control::CONTROL_START:
            return "Start";
        case Control::CONTROL_LEFT_STICK:
        case Control::AXIS_LEFT:
            return "Left Stick";
        case Control::CONTROL_RIGHT_STICK:
        case Control::AXIS_RIGHT:
            return "Right Stick";
        case Control::CONTROL_LEFT_SHOULDER:
            return "Left Shoulder";
        case Control::CONTROL_RIGHT_SHOULDER:
            return "Right Shoulder";
        case Control::CONTROL_DPAD_UP:
            return "DPad Up";
        case Control::CONTROL_DPAD_DOWN:
            return "DPad Down";
        case Control::CONTROL_DPAD_LEFT:
            return "DPad Left";
        case Control::CONTROL_DPAD_RIGHT:
            return "DPad Right";
        case Control::CONTROL_TRIGGER_LEFT:
            return "Trigger Left";
        case Control::CONTROL_TRIGGER_RIGHT:
            return "Trigger Right";
        default:
            return control_details::get_key_name(control);
    }
}

ControlDeviceType ControlUtils::get_control_device_type(Control control) noexcept {
    KW_ASSERT(static_cast<uint32>(control) <= static_cast<uint32>(GAMEPAD_AXES_END), "Invalid control!");

    if (control >= KEYBOARD_BEGIN && control <= KEYBOARD_END) {
        return ControlDeviceType::KEYBOARD;
    } else if (control >= MOUSE_BEGIN && control <= MOUSE_END) {
        return ControlDeviceType::MOUSE;
    }
    return ControlDeviceType::GAMEPAD;
}
} // namespace kw

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

#include <kw/base/string.h>
#include <kw/base/types.h>

namespace kw {
/**
 * The following enum class enumerates all the possible controls for keyboard, mouse and gamepad.
 */
enum class Control : int32 {
    CONTROL_UNKNOWN = 0,

    // Keyboard controls.
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    KEY_ENTER,
    KEY_ESCAPE,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_SPACE,
    KEY_MINUS,
    KEY_EQUALS,
    KEY_LEFTBRACKET,
    KEY_RIGHTBRACKET,
    KEY_BACKSLASH,
    KEY_NONUSHASH,
    KEY_SEMICOLON,
    KEY_APOSTROPHE,
    KEY_GRAVE,
    KEY_COMMA,
    KEY_PERIOD,
    KEY_SLASH,
    KEY_CAPSLOCK,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_PRINTSCREEN,
    KEY_SCROLLLOCK,
    KEY_PAUSE,
    KEY_INSERT,
    KEY_HOME,
    KEY_PAGEUP,
    KEY_DEL,
    KEY_END,
    KEY_PAGEDOWN,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_DOWN,
    KEY_UP,
    KEY_NUMLOCKCLEAR,
    KEY_KP_DIVIDE,
    KEY_KP_MULTIPLY,
    KEY_KP_MINUS,
    KEY_KP_PLUS,
    KEY_KP_ENTER,
    KEY_KP_1,
    KEY_KP_2,
    KEY_KP_3,
    KEY_KP_4,
    KEY_KP_5,
    KEY_KP_6,
    KEY_KP_7,
    KEY_KP_8,
    KEY_KP_9,
    KEY_KP_0,
    KEY_KP_PERIOD,
    KEY_NONUSBACKSLASH,
    KEY_APPLICATION,
    KEY_POWER,
    KEY_KP_EQUALS,
    KEY_F13,
    KEY_F14,
    KEY_F15,
    KEY_F16,
    KEY_F17,
    KEY_F18,
    KEY_F19,
    KEY_F20,
    KEY_F21,
    KEY_F22,
    KEY_F23,
    KEY_F24,
    KEY_EXECUTE,
    KEY_HELP,
    KEY_MENU,
    KEY_SELECT,
    KEY_STOP,
    KEY_AGAIN,
    KEY_UNDO,
    KEY_CUT,
    KEY_COPY,
    KEY_PASTE,
    KEY_FIND,
    KEY_MUTE,
    KEY_VOLUMEUP,
    KEY_VOLUMEDOWN,
    KEY_LOCKINGCAPSLOCK,
    KEY_LOCKINGNUMLOCK,
    KEY_LOCKINGSCROLLLOCK,
    KEY_KP_COMMA,
    KEY_KP_EQUALSAS400,
    KEY_INTERNATIONAL1,
    KEY_INTERNATIONAL2,
    KEY_INTERNATIONAL3,
    KEY_INTERNATIONAL4,
    KEY_INTERNATIONAL5,
    KEY_INTERNATIONAL6,
    KEY_INTERNATIONAL7,
    KEY_INTERNATIONAL8,
    KEY_INTERNATIONAL9,
    KEY_LANG1,
    KEY_LANG2,
    KEY_LANG3,
    KEY_LANG4,
    KEY_LANG5,
    KEY_LANG6,
    KEY_LANG7,
    KEY_LANG8,
    KEY_LANG9,
    KEY_ALTERASE,
    KEY_SYSREQ,
    KEY_CANCEL,
    KEY_CLEAR,
    KEY_PRIOR,
    KEY_RETURN2,
    KEY_SEPARATOR,
    KEY_OPER,
    KEY_CLEARAGAIN,
    KEY_CRSEL,
    KEY_EXSEL,
    KEY_KP_00,
    KEY_KP_000,
    KEY_THOUSANDSSEPARATOR,
    KEY_DECIMALSEPARATOR,
    KEY_CURRENCYUNIT,
    KEY_CURRENCYSUBUNIT,
    KEY_KP_LEFTPAREN,
    KEY_KP_RIGHTPAREN,
    KEY_KP_LEFTBRACE,
    KEY_KP_RIGHTBRACE,
    KEY_KP_TAB,
    KEY_KP_BACKSPACE,
    KEY_KP_A,
    KEY_KP_B,
    KEY_KP_C,
    KEY_KP_D,
    KEY_KP_E,
    KEY_KP_F,
    KEY_KP_XOR,
    KEY_KP_POWER,
    KEY_KP_PERCENT,
    KEY_KP_LESS,
    KEY_KP_GREATER,
    KEY_KP_AMPERSAND,
    KEY_KP_DBLAMPERSAND,
    KEY_KP_VERTICALBAR,
    KEY_KP_DBLVERTICALBAR,
    KEY_KP_COLON,
    KEY_KP_HASH,
    KEY_KP_SPACE,
    KEY_KP_AT,
    KEY_KP_EXCLAM,
    KEY_KP_MEMSTORE,
    KEY_KP_MEMRECALL,
    KEY_KP_MEMCLEAR,
    KEY_KP_MEMADD,
    KEY_KP_MEMSUBTRACT,
    KEY_KP_MEMMULTIPLY,
    KEY_KP_MEMDIVIDE,
    KEY_KP_PLUSMINUS,
    KEY_KP_CLEAR,
    KEY_KP_CLEARENTRY,
    KEY_KP_BINARY,
    KEY_KP_OCTAL,
    KEY_KP_DECIMAL,
    KEY_KP_HEXADECIMAL,
    KEY_LCTRL,
    KEY_LSHIFT,
    KEY_LALT,
    KEY_LGUI,
    KEY_RCTRL,
    KEY_RSHIFT,
    KEY_RALT,
    KEY_RGUI,
    KEY_MODE,
    KEY_AUDIONEXT,
    KEY_AUDIOPREV,
    KEY_AUDIOSTOP,
    KEY_AUDIOPLAY,
    KEY_AUDIOMUTE,
    KEY_MEDIASELECT,
    KEY_WWW,
    KEY_MAIL,
    KEY_CALCULATOR,
    KEY_COMPUTER,
    KEY_AC_SEARCH,
    KEY_AC_HOME,
    KEY_AC_BACK,
    KEY_AC_FORWARD,
    KEY_AC_STOP,
    KEY_AC_REFRESH,
    KEY_AC_BOOKMARKS,
    KEY_BRIGHTNESSDOWN,
    KEY_BRIGHTNESSUP,
    KEY_DISPLAYSWITCH,
    KEY_KBDILLUMTOGGLE,
    KEY_KBDILLUMDOWN,
    KEY_KBDILLUMUP,
    KEY_EJECT,
    KEY_SLEEP,
    KEY_APP1,
    KEY_APP2,

    // Mouse controls.
    BUTTON_LEFT,
    BUTTON_MIDDLE,
    BUTTON_RIGHT,
    BUTTON_EXTRA_1,
    BUTTON_EXTRA_2,

    // Gamepad controls.
    CONTROL_A,
    CONTROL_B,
    CONTROL_X,
    CONTROL_Y,
    CONTROL_BACK,
    CONTROL_GUIDE,
    CONTROL_START,
    CONTROL_LEFT_STICK,
    CONTROL_RIGHT_STICK,
    CONTROL_LEFT_SHOULDER,
    CONTROL_RIGHT_SHOULDER,
    CONTROL_DPAD_UP,
    CONTROL_DPAD_DOWN,
    CONTROL_DPAD_LEFT,
    CONTROL_DPAD_RIGHT,

    // These are also gamepad controls now, but actually these are axes.
    CONTROL_TRIGGER_LEFT,
    CONTROL_TRIGGER_RIGHT,

    // Gamepad axes.
    AXIS_LEFT,
    AXIS_RIGHT
};

/**
 * Enumerates all possible devices controls can have.
 */
enum class ControlDeviceType {
    KEYBOARD,
    MOUSE,
    GAMEPAD
};

/**
 * The following enum class provides utilities to work with Controls.
 */
class ControlUtils final {
public:
    /**
     * These constants help to walk over separate device controls.
     */
    static constexpr Control KEYBOARD_BEGIN = Control::KEY_A;
    static constexpr Control KEYBOARD_END = Control::KEY_APP2;
    static constexpr Control MOUSE_BEGIN = Control::BUTTON_LEFT;
    static constexpr Control MOUSE_END = Control::BUTTON_EXTRA_2;
    static constexpr Control GAMEPAD_BUTTONS_BEGIN = Control::CONTROL_A;
    static constexpr Control GAMEPAD_BUTTONS_END = Control::CONTROL_TRIGGER_RIGHT;
    static constexpr Control GAMEPAD_AXES_BEGIN = Control::AXIS_LEFT;
    static constexpr Control GAMEPAD_AXES_END = Control::AXIS_RIGHT;

    /**
     * Return string representation of the given 'control'.
     * For example for Control::KEY_ESCAPE this function will return 'Escape'.
     */
    static String get_control_name(Control control) noexcept;

    /**
     * Return device type of the given 'control'.
     * Please look at 'ControlDeviceType' enum.
     */
    static ControlDeviceType get_control_device_type(Control control) noexcept;

    ControlUtils() = delete;
};
} // namespace kw

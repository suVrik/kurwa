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
#include <kw/core/i_game.h>
#include <kw/debug/assert.h>
#include <kw/input/keyboard.h>

#include "key_conversion.h"

#include <SDL2/SDL_events.h>

namespace kw {
namespace keyboard_details {
constexpr int32 FIRST_KEY = static_cast<int32>(Control::KEY_A);
constexpr int32 KEY_COUNT = static_cast<int32>(Control::KEY_APP2) - FIRST_KEY + 1;

Control from_scancode(SDL_Scancode scancode) {
    // keys_conversion is required to have a key type of uint32, but SDL_Scancode,
    // because otherwise it would require a hash function definition.
    auto result = keys_conversion.find(static_cast<uint32>(scancode));
    if (result != keys_conversion.end()) {
        return result->second;
    }
    return Control::CONTROL_UNKNOWN;
}
} // namespace keyboard_details

Keyboard::Keyboard(IGame* game) noexcept {
    game->on_event.connect(this, &Keyboard::on_event_listener);
    game->on_update.connect(this, &Keyboard::on_update_listener);
}

bool Keyboard::is_pressed(Control key) const noexcept {
    const auto index = static_cast<int32>(key) - keyboard_details::FIRST_KEY;

    KW_ASSERT(index >= 0 && index <= keyboard_details::KEY_COUNT, "Invalid control!");

    return m_keys[index] == KeyState::PRESSED;
}

bool Keyboard::is_released(Control key) const noexcept {
    const auto index = static_cast<int32>(key) - keyboard_details::FIRST_KEY;

    KW_ASSERT(index >= 0 && index <= keyboard_details::KEY_COUNT, "Invalid control!");

    return m_keys[index] == KeyState::RELEASED;
}

bool Keyboard::is_down(Control key) const noexcept {
    const auto index = static_cast<int32>(key) - keyboard_details::FIRST_KEY;

    KW_ASSERT(index >= 0 && index <= keyboard_details::KEY_COUNT, "Invalid control!");

    return (static_cast<uint8>(m_keys[index]) & 0b001U) != 0;
}

bool Keyboard::is_repeat(Control key) const noexcept {
    const auto index = static_cast<int32>(key) - keyboard_details::FIRST_KEY;

    KW_ASSERT(index >= 0 && index <= keyboard_details::KEY_COUNT, "Invalid control!");

    return (static_cast<uint8>(m_keys[index]) & 0b010U) != 0;
}

const String& Keyboard::get_text() const noexcept {
    return m_text;
}

void Keyboard::on_event_listener(SDL_Event& event) noexcept {
    switch (event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            const Control control = keyboard_details::from_scancode(event.key.keysym.scancode);
            if (control != Control::CONTROL_UNKNOWN) {
                const auto index = static_cast<int32>(control) - keyboard_details::FIRST_KEY;
                if (event.type == SDL_KEYUP) {
                    m_keys_back[index] = KeyState::RELEASED;
                } else if (event.key.repeat == 0) {
                    m_keys_back[index] = KeyState::PRESSED;
                } else {
                    m_keys_back[index] = KeyState::REPEAT;
                }
            }
            break;
        }
        case SDL_TEXTINPUT:
            m_text_back += event.text.text;
            break;
        default:
            // We're not interested in other events by now.
            break;
    }
}

void Keyboard::on_update_listener() noexcept {
    // Here, in Keyboard, I use the back buffer approach. While having an 'on_update' signal that
    // follows the 'on_event' signal, I can't simply clear the text or reset 'pressed'/'released'
    // flags, because this data will be used in other modules following the input module.
    // Instead, every frame I clear the back buffer values and fill them in the event listener.
    eastl::copy_n(m_keys_back.data(), m_keys_back.size(), m_keys.data());
    for (auto& key_state : m_keys_back) {
        // RELEASED => NONE
        // PRESSED, REPEAT, DOWN => DOWN
        key_state = static_cast<KeyState>(static_cast<uint8>(key_state) & 0b001U);
    }

    m_text = m_text_back;
    m_text_back.clear();
}
} // namespace kw

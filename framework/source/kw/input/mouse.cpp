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

#include <kw/core/i_game.h>
#include <kw/debug/assert.h>
#include <kw/input/mouse.h>

#include <SDL2/SDL_events.h>

namespace kw {
namespace mouse_details {
constexpr int32 FIRST_BUTTON = static_cast<int32>(Control::BUTTON_LEFT);
constexpr int32 BUTTON_COUNT = static_cast<int32>(Control::BUTTON_EXTRA_2) - FIRST_BUTTON + 1;

Control from_sdl_button(uint32 button) {
    // Compiler must convert this thing into something fast, because SDL_BUTTON_* enumeration is ordered.
    switch (button) {
        case SDL_BUTTON_LEFT:
            return Control::BUTTON_LEFT;
        case SDL_BUTTON_MIDDLE:
            return Control::BUTTON_MIDDLE;
        case SDL_BUTTON_RIGHT:
            return Control::BUTTON_RIGHT;
        case SDL_BUTTON_X1:
            return Control::BUTTON_EXTRA_1;
        case SDL_BUTTON_X2:
            return Control::BUTTON_EXTRA_2;
        default:
            return Control::CONTROL_UNKNOWN;
    }
}
} // namespace mouse_details

Mouse::Mouse(IGame* game) noexcept {
    game->on_event.connect(this, &Mouse::on_event_listener);
    game->on_update.connect(this, &Mouse::on_update_listener);
}

bool Mouse::is_pressed(Control button) const noexcept {
    const auto index = static_cast<int32>(button) - mouse_details::FIRST_BUTTON;

    KW_ASSERT(index >= 0 && index <= mouse_details::BUTTON_COUNT, "Invalid control!");

    return m_buttons[index] == ButtonState::PRESSED;
}

bool Mouse::is_released(Control button) const noexcept {
    const auto index = static_cast<int32>(button) - mouse_details::FIRST_BUTTON;

    KW_ASSERT(index >= 0 && index <= mouse_details::BUTTON_COUNT, "Invalid control!");

    return m_buttons[index] == ButtonState::RELEASED;
}

bool Mouse::is_down(Control button) const noexcept {
    const auto index = static_cast<int32>(button) - mouse_details::FIRST_BUTTON;

    KW_ASSERT(index >= 0 && index <= mouse_details::BUTTON_COUNT, "Invalid control!");

    return (static_cast<uint8>(m_buttons[index]) & 0b01U) != 0;
}

int32 Mouse::get_wheel() const noexcept {
    return m_wheel;
}

Pair<int32, int32> Mouse::get_position() const noexcept {
    return m_position;
}

void Mouse::on_event_listener(SDL_Event& event) noexcept {
    switch (event.type) {
        case SDL_MOUSEMOTION:
            m_position.first  = event.motion.x;
            m_position.second = event.motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP: {
            const Control button = mouse_details::from_sdl_button(event.button.button);
            if (button != Control::CONTROL_UNKNOWN) {
                const auto index = static_cast<int32>(button) - mouse_details::FIRST_BUTTON;
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    m_buttons_back[index] = ButtonState::PRESSED;
                } else {
                    m_buttons_back[index] = ButtonState::RELEASED;
                }
            }
            break;
        }
        case SDL_MOUSEWHEEL:
            m_wheel_back = event.wheel.y;
            if (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
                m_wheel_back *= 1;
            }
            break;
        default:
            // We're not interested in other events by now.
            break;
    }
}

void Mouse::on_update_listener() noexcept {
    // Please, inspect the Keyboard::on_update_listener() to understand the back buffer approach in input module.
    eastl::copy_n(m_buttons_back.data(), m_buttons_back.size(), m_buttons.data());
    for (auto& button_state : m_buttons_back) {
        // RELEASED => NONE
        // PRESSED, DOWN => DOWN
        button_state = static_cast<ButtonState>(static_cast<uint8>(button_state) & 0b01U);
    }

    m_wheel      = m_wheel_back;
    m_wheel_back = 0;
}
} // namespace kw

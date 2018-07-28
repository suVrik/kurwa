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
#include <kw/input/input_module.h>

#include <SDL2/SDL_events.h>

namespace kw {
InputModule::InputModule(IGame* game) noexcept
    : m_game(game)
    , m_keyboard(game)
    , m_mouse(game) {
    game->on_event.connect(this, &InputModule::on_event_listener);
}

Keyboard& InputModule::get_keyboard() noexcept {
    return m_keyboard;
}

const Keyboard& InputModule::get_keyboard() const noexcept {
    return m_keyboard;
}

Mouse& InputModule::get_mouse() noexcept {
    return m_mouse;
}

const Mouse& InputModule::get_mouse() const noexcept {
    return m_mouse;
}

uint32 InputModule::get_num_gamepads() const noexcept {
    return static_cast<uint32>(m_gamepads.size());
}

Gamepad& InputModule::get_gamepad(uint32 index) noexcept {
    KW_ASSERT(index < m_gamepads.size(), "Invalid gamepad index!");

    return *eastl::next(m_gamepads.begin(), index);
}

const Gamepad& InputModule::get_gamepad(uint32 index) const noexcept {
    KW_ASSERT(index < m_gamepads.size(), "Invalid gamepad index!");

    return *eastl::next(m_gamepads.begin(), index);
}

void InputModule::on_event_listener(SDL_Event& event) noexcept {
    switch (event.type) {
        case SDL_CONTROLLERDEVICEADDED:
            KW_ASSERT(SDL_IsGameController(event.cdevice.which), "Invalid SDL game controller!");
            m_gamepads.emplace_back(m_game, event.cdevice.which);
            on_gamepad_added.emit(m_gamepads.back());
            break;
        case SDL_CONTROLLERDEVICEREMOVED: {
            auto gamepad = get_gamepad(event.cdevice.which);
            if (gamepad != m_gamepads.end()) {
                on_gamepad_removed.emit(*gamepad);
                m_gamepads.erase(gamepad);
            }
            break;
        }
        case SDL_CONTROLLERDEVICEREMAPPED: {
            auto gamepad = get_gamepad(event.cdevice.which);
            if (gamepad != m_gamepads.end()) {
                on_gamepad_remapped.emit(*gamepad);
            }
            break;
        }
        default:
            // We're not interested in other events by now.
            break;
    }
}

List<Gamepad>::iterator InputModule::get_gamepad(int32 device_index) noexcept {
    for (auto it = m_gamepads.begin(); it != m_gamepads.end(); ++it) {
        if (it->m_instance_id == device_index) {
            return it;
        }
    }

    return m_gamepads.end();
}
} // namespace kw

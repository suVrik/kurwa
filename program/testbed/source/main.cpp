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

#include <kw/core/game.h>
#include <kw/core/window_module.h>
#include <kw/ecs/imgui_module.h>
#include <kw/ecs/scene_module.h>
#include <kw/input/input_module.h>
#include <kw/math/math.h>
#include <kw/render/render_module.h>
#include <kw/utilities/trace.h>

class Game final : public kw::Game<kw::WindowModule, kw::InputModule, kw::RenderModule, kw::ImguiModule, kw::SceneModule>, public kw::SignalListener {
public:
    Game();

private:
    void on_init_listener(kw::IGame* game);
    void on_update_listener();
    void test_input();
};

Game::Game() {
    on_init.connect(this, &Game::on_init_listener);
    on_update.connect(this, &Game::on_update_listener);
}

void Game::on_init_listener(kw::IGame* game) {
    auto& input_module = get<kw::InputModule>();
    input_module.on_gamepad_added.connect(this, [](kw::Gamepad& gamepad) { kw::trace("Gamepad added!"); });
    input_module.on_gamepad_removed.connect(this, [](kw::Gamepad& gamepad) { kw::trace("Gamepad removed!"); });
}

// There's no ImGui yet => No sane testbed yet
void Game::on_update_listener() {
    test_input();
}

void Game::test_input() {
    auto& input_module = get<kw::InputModule>();

    const kw::Keyboard& keyboard = input_module.get_keyboard();
    for (kw::Control i = kw::ControlUtils::KEYBOARD_BEGIN; i <= kw::ControlUtils::KEYBOARD_END; i = static_cast<kw::Control>(static_cast<kw::int32>(i) + 1)) {
        // This assert is excess, just for testing
        KW_ASSERT(kw::ControlUtils::get_control_device_type(i) == kw::ControlDeviceType::KEYBOARD);

        const bool is_pressed = keyboard.is_pressed(i);
        const bool is_down = keyboard.is_down(i);
        const bool is_repeat = keyboard.is_repeat(i);
        const bool is_released = keyboard.is_released(i);
        const kw::String& text = keyboard.get_text();
        if (is_pressed || is_down || is_repeat || is_released) {
            kw::trace("Keyboard Button #{} ('{}')     P: {}, D: {}, Rep: {}, Rel: {}, Txt: {}", static_cast<kw::int32>(i), kw::ControlUtils::get_control_name(i), is_pressed, is_down, is_repeat, is_released, text);
        }
    }

    const kw::Mouse& mouse = input_module.get_mouse();
    const auto [mx, my] = mouse.get_position();
    const kw::int32 wheel = mouse.get_wheel();
    if (wheel != 0) {
        kw::trace("Mouse Wheel {}", wheel);
    }
    for (kw::Control i = kw::ControlUtils::MOUSE_BEGIN; i <= kw::ControlUtils::MOUSE_END; i = static_cast<kw::Control>(static_cast<kw::int32>(i) + 1)) {
        // This assert is excess, just for testing
        KW_ASSERT(kw::ControlUtils::get_control_device_type(i) == kw::ControlDeviceType::MOUSE);

        const bool is_pressed = mouse.is_pressed(i);
        const bool is_down = mouse.is_down(i);
        const bool is_released = mouse.is_released(i);
        if (is_pressed || is_down || is_released) {
            kw::trace("Mouse Button #{} ('{}')     P: {}, D: {}, R: {}, X: {}, Y: {}", static_cast<kw::int32>(i), kw::ControlUtils::get_control_name(i), is_pressed, is_down, is_released, mx, my);
        }
    }

    const kw::uint32 num_gamepads = input_module.get_num_gamepads();
    for (kw::uint32 i = 0; i < num_gamepads; i++) {
        const kw::Gamepad& gamepad = input_module.get_gamepad(i);
        for (kw::Control j = kw::ControlUtils::GAMEPAD_BUTTONS_BEGIN; j <= kw::ControlUtils::GAMEPAD_BUTTONS_END; j = static_cast<kw::Control>(static_cast<kw::int32>(j) + 1)) {
            // This assert is excess, just for testing
            KW_ASSERT(kw::ControlUtils::get_control_device_type(j) == kw::ControlDeviceType::GAMEPAD);

            const bool is_pressed = gamepad.is_pressed(j);
            const bool is_down = gamepad.is_down(j);
            const bool is_released = gamepad.is_released(j);
            if (is_pressed || is_down || is_released) {
                kw::trace("Gamepad #{} Button #{} ('{}')     P: {}, D: {}, R: {}", i, static_cast<kw::int32>(j), kw::ControlUtils::get_control_name(j), is_pressed, is_down, is_released);
            }
        }
        for (kw::Control j = kw::ControlUtils::GAMEPAD_AXES_BEGIN; j <= kw::ControlUtils::GAMEPAD_AXES_END; j = static_cast<kw::Control>(static_cast<kw::int32>(j) + 1)) {
            // This assert is excess, just for testing
            KW_ASSERT(kw::ControlUtils::get_control_device_type(j) == kw::ControlDeviceType::GAMEPAD);

            const auto [x, y] = gamepad.get_axis(j);
            if (kw::Math::abs(x) > 0.1f || kw::Math::abs(y) > 0.1f) {
                kw::trace("Gamepad #{} Axis #{} ('{}')     X: {}, Y: {}", i, static_cast<kw::int32>(j), kw::ControlUtils::get_control_name(j), x, y);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    Game game;
    return game.run();
}

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
#include <kw/base/signal.h>
#include <kw/base/string.h>
#include <kw/input/control.h>

union SDL_Event;

namespace kw {
class IGame;

/**
 * This class represents a keyboard interface.
 */
class Keyboard final : public SignalListener {
public:
    /**
     * Construct a keyboard interface using the given 'game' as an event-emitter.
     */
    explicit Keyboard(IGame* game) noexcept;
    Keyboard(const Keyboard& original) = delete;
    Keyboard& operator=(const Keyboard& original) = delete;

    /**
     * Return true if the given 'key' was just pressed, otherwise return false.
     */
    bool is_pressed(Control key) const noexcept;

    /**
     * Return true if the given 'key' was just released, otherwise return false.
     */
    bool is_released(Control key) const noexcept;

    /**
     * Return true if the given 'key' is pressed, otherwise return false.
     */
    bool is_down(Control key) const noexcept;

    /**
     * Return true if the given 'key' was just repeated, otherwise return false.
     * Repeating is a system input event that happens when the key is pressed and with some
     * system-dependent interval until it's released.
     */
    bool is_repeat(Control key) const noexcept;

    /**
     * Return UTF-8 text that was written since the last frame.
     */
    const String& get_text() const noexcept;

private:
    enum class KeyState : uint8 { NONE = 0b000U,
                                  DOWN = 0b001U,
                                  REPEAT = 0b011U,
                                  PRESSED = 0b111U,
                                  RELEASED = 0b100U };

    void on_event_listener(SDL_Event& event) noexcept;
    void on_update_listener() noexcept;

    Array<KeyState, 242> m_keys_back{};
    Array<KeyState, 242> m_keys{};
    String m_text_back;
    String m_text;
};
} // namespace kw

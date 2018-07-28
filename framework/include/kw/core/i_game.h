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

#include <kw/base/signal.h>
#include <kw/base/string.h>
#include <kw/base/types.h>

union SDL_Event;

namespace kw {
/**
 * IGame is a class that encapsulates SDL calls.
 * Although, 'Game' is meant as the main class for the game, this one is very useful if you must receive or
 * store the 'Game' instance, but you don't need any modules (so you can receive or store it template-free).
 *
 * Listeners of IGame's signals 'on_event' and 'on_update' are allowed to throw exceptions
 * (prefer std::runtime_error or its child, because then IGame can produce a meaningful error message).
 */
class IGame {
public:
    /**
     * Initialize SDL subsystems.
     */
    IGame() noexcept;

    /**
     * Quit SDL subsystems.
     */
    virtual ~IGame() noexcept;

    /**
     * Run a frame loop.
     */
    int32 run() noexcept;

    /**
     * Make 'run' method return 0 after current frame.
     * Calling this function outside of a 'run' call has no effect.
     */
    void exit() noexcept;

    Signal<void(SDL_Event&)> on_event; /// Emitted for every single event before an update signal.
    Signal<void()> on_update;          /// Emitted once a frame after polling events.

protected:
    /**
     * Show an error message box with the given 'error_description'.
     * Keep in mind this is a blocking call.
     */
    void message_box(const String& error_description) const noexcept;

    /// If defined as false, the 'run' call will quit immediately. Otherwise it will run a frame loop.
    bool is_initialized;
};
} // namespace kw

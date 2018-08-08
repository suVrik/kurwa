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

#include <kw/base/hash_map.h>
#include <kw/base/signal.h>
#include <kw/base/string.h>
#include <kw/base/types.h>

#include <typeindex>

union SDL_Event;

namespace eastl {
template <>
struct hash<std::type_index> {
    size_t operator()(const std::type_index& value) const;
};
} // namespace eastl

namespace kw {
/**
 * IGame is a template-free parent of Game.
 *
 * Keep in mind that its `get` methods are quite slow, comparing to Game's ones,
 * but you're free to cache its return value.
 */
class IGame {
public:
    /**
     * Run a frame loop.
     */
    int32 run() noexcept;

    /**
     * Make `run` method return 0 after current frame.
     * Calling this function outside of a `run` call gives no effect.
     */
    void exit() noexcept;

    /**
     * Return true if the given `Module` is present. Otherwise return false.
     */
    template <typename Module>
    bool has() const noexcept;

    /**
     * Return the given `Module`.
     *
     * It is safe to cache a pointer to this `Module`.
     */
    template <typename Module>
    Module& get() noexcept;

    template <typename Module>
    const Module& get() const noexcept;

    /**
     * Emitted after all the modules are successfully initialized.
     *
     * The common mistake would be to build a destructor implementation counting that this signal emitted.
     * Actually, it might not emit, if some module is failed to initialize (even tho another module constructor
     * had been executed and its destructor will be also executed). For such logic use `on_destroy` signal.
     *
     * You are free to throw exceptions in your `on_init` listener. Every listener that have already received
     * `on_init` signal (except the throwing one) will immediately receive the `on_destroy` signal and `run`
     * method will quit with the error code.
     */
    Signal<void(IGame*)> on_init;

    /**
     * Emitted at the end of `run`, while all the modules are still valid.
     *
     * If you initialized or constructed something in your `on_init` listener, that would be a good design
     * to deinitialize or destroy it in your `on_destroy` listener. If `on_init` signal was emitted, this
     * signal will be emitted to. The opposite is correct too: if `on_init` signal was not emitted (due to
     * some problems with modules initialization, for example), `on_destroy` will never be emitted too.
     *
     * You are free to throw exceptions in your `on_destroy` listener, but keep in mind, that other listeners
     * will not receive `on_destroy` signal and will not free resources they have allocated in `on_init` listener.
     */
    Signal<void(IGame*)> on_destroy;

    /**
     * Emitted for every single event before an update signal.
     *
     * It is a mistake to think that this signal is emitted at least once a frame. If none events had come,
     * this signal will not be emitted.
     *
     * You can throw exceptions in your `on_event` listeners, which will force the `run` method to stop
     * and return the error code. Keep in mind, that `on_destroy` signal will be emitted anyway.
     */
    Signal<void(SDL_Event&)> on_event;

    /**
     * Emitted once a frame after polling events.
     * You can throw exceptions in your `on_event` listeners and they will be handled the right way.
     */
    Signal<void()> on_update;

    /**
     * Emitted once a frame after emitting `on_update`.
     * You can throw exceptions in your `on_draw` listeners and they will be handled the right way.
     */
    Signal<void()> on_draw;

protected:
    /**
     * Construct all low-level and platform-dependent structures.
     * Keep in mind that modules are not yet constructed here (they will be constructed in Game constructor).
     */
    IGame() noexcept;

    /**
     * Destroy all low-level and platform-dependent structures.
     * Keep in mind that modules are already destroyed here (in Game destructor).
     */
    ~IGame() noexcept;

    /**
     * Show an error message box with the given `error_description`.
     * The message is also duplicated in stderr stream.
     * Keep in mind this is a blocking call.
     */
    void message_box(const String& error_description) const noexcept;

    /**
     * The set of pointers to presented modules tied with their typeid.
     */
    HashMap<std::type_index, void*> modules_pointers;

    /**
     * If defined as false, the `run` call will quit immediately. Otherwise it will run a frame loop.
     * Can be changed in derived class's constructor. Changing this value outside of constructor gives no effect.
     */
    bool is_initialized;
};
} // namespace kw

#include <kw/core/internal/i_game_impl.h>

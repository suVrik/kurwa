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

#include <kw/base/types.h>
#include <kw/base/tuple.h>
#include <kw/base/string.h>
#include <kw/base/unique_ptr.h>
#include <kw/core/game_native.h>

namespace kw {
/**
 * Game is a class that manages modules: initializes them in a straight order and destroys them in reverse order.
 * By being a child of class GameNative, it also handles native related stuff such as initializing video subsystems,
 * terminating the application, running the frame loop and more (take a look at it, really).
 *
 * \code
 * class Alex : public Game<WindowModule, InputModule, TimeModule> {
 * \endcode
 *
 * In this example 'WindowModule' is initialized first, then 'InputModule' and after that, 'TimeModule'.
 * They are destroyed in reverse order: 'TimeModule', followed by an 'InputModule' and 'WindowModule' at the end.
 *
 * When module is being initialized, all SDL subsystems are guaranteed to be initialized. When module is being
 * destroyed, the SDL subsystems are still guaranteed to be initialized (they're destroyed afterwards).
 *
 * If module is failed to initialize, it's allowed to throw a std::runtime_error which will be handled in IGame class.
 * Nevertheless, possible exceptions in destructor are not handled and lead to undefined behaviour.
 */
template<typename... Modules>
class Game : public GameNative {
    public:
        /**
         * Defined as std::true_type if the given 'Module' is present, otherwise defined as false.
         */
        template<typename Module>
        using has_t = kw::has_t<Module, Tuple<Modules...>>;

        /**
         * Initialize SDL subsystems and construct all the modules.
         * In case either some SDL subsystem or some module is failed to initialize,
         * the 'run' method will return non-zero exit code without entering a frame loop.
         */
        Game() noexcept;

        /**
         * Return the given 'Module'.
         */
        template<typename Module>
        Module& get() noexcept;

        /**
         * Return the given 'Module'.
         */
        template<typename Module>
        const Module& get() const noexcept;

    private:
        Tuple<UniquePtr<Modules>...> m_modules;

};
} // namespace kw

#include <kw/core/internal/game_impl.h>

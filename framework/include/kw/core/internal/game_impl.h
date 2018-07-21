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

#include <kw/core/game.h>

namespace kw {
template<typename... Modules>
Game<Modules...>::Game() noexcept {
    // If SDL failed to initialize, we can omit initializing modules.
    if (is_initialized) {
        try {
            Tuple<UniquePtr<Modules>...> modules{make_unique<Modules>(this)...};
            m_modules = std::move(modules);
        }
        catch (const std::runtime_error &error) {
            message_box(error.what());
            is_initialized = false;
        }
        catch (...) {
            message_box("Runtime error in anonymous Module constructor!");
            is_initialized = false;
        }
    }
}

template<typename... Modules>
template<typename Module>
Module& Game<Modules...>::get() noexcept {
    return *kw::get<Module*>(m_modules);
}

template<typename... Modules>
template<typename Module>
const Module& Game<Modules...>::get() const noexcept {
    return *kw::get<Module*>(m_modules);
}
}
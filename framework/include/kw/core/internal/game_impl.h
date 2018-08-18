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
namespace game_details {
template <typename Tup, typename Game>
void construct_slow_tuple(Tup& modules, Game game, HashMap<std::type_index, void*>& modules_pointers) {
}

template <typename Tup, typename Game, typename Current, typename... Following>
void construct_slow_tuple(Tup& modules, Game game, HashMap<std::type_index, void*>& modules_pointers) {
    eastl::get<Current>(modules).construct(game);
    modules_pointers.emplace(typeid(typename Current::value_type), &(*eastl::get<Current>(modules)));
    construct_slow_tuple<Tup, Game, Following...>(modules, game, modules_pointers);
}
} // namespace game_details

template <typename... Modules>
Game<Modules...>::Game() noexcept {
    // If IGame failed to initialize, we can omit initializing modules.
    if (is_initialized) {
        try {
            using namespace game_details;

            construct_slow_tuple<decltype(m_modules), Game*, Slow<Modules>...>(m_modules, this, modules_pointers);
        } catch (const RuntimeError& error) {
            message_box(error.what());
            is_initialized = false;
        } catch (...) {
            message_box("Runtime error in anonymous Module constructor!");
            is_initialized = false;
        }
    }
}

template <typename... Modules>
template <typename Module>
bool Game<Modules...>::has() const noexcept {
    return kw::has_t<Module, Tuple<Slow<Modules>...>>::value;
}

template <typename... Modules>
template <typename Module>
Module& Game<Modules...>::get() noexcept {
    return *kw::get<Slow<Module>>(m_modules);
}

template <typename... Modules>
template <typename Module>
const Module& Game<Modules...>::get() const noexcept {
    return *kw::get<Slow<Module>>(m_modules);
}
} // namespace kw

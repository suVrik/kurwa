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

#include <kw/core/i_game.h>

namespace kw {
template <typename Module>
bool IGame::has() const noexcept {
    auto module = modules_pointers.find(typeid(Module));
    return module != modules_pointers.end();
}

template <typename Module>
Module& IGame::get() noexcept {
    auto module = modules_pointers.find(typeid(Module));

    KW_ASSERT(module != modules_pointers.end(), "The given module is not present!");

    return *reinterpret_cast<Module*>(module->second);
}

template <typename Module>
const Module& IGame::get() const noexcept {
    auto module = modules_pointers.find(typeid(Module));

    KW_ASSERT(module != modules_pointers.end(), "The given module is not present!");

    return *reinterpret_cast<const Module*>(module->second);
}
} // namespace kw

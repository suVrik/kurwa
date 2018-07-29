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
template <typename... Modules>
Game<Modules...>::Game() noexcept {
    // If SDL failed to initialize, we can omit initializing modules.
    if (is_initialized) {
        try {
            Tuple<UniquePtr<Modules>...> modules{ make_unique<Modules>(this)... };
            m_modules = std::move(modules);
        } catch (const RuntimeError& error) {
            // 'fprintf' is for developer. It's easier to examine info in console, rather than in a message box.
            fprintf(stderr, "%s\n", error.what());
            message_box(error.what());
            is_initialized = false;
        } catch (...) {
            fprintf(stderr, "Runtime error in anonymous Module constructor!\n");
            message_box("Runtime error in anonymous Module constructor!");
            is_initialized = false;
        }
    }
}

template <typename... Modules>
template <typename Module>
Module& Game<Modules...>::get() noexcept {
    return *kw::get<UniquePtr<Module>>(m_modules);
}

template <typename... Modules>
template <typename Module>
const Module& Game<Modules...>::get() const noexcept {
    return *kw::get<UniquePtr<Module>>(m_modules);
}

template <typename... Modules>
int32 Game<Modules...>::run() noexcept {
    auto all = [](bool a, bool b) noexcept->bool {
        return a && b;
    };

    if (is_initialized) {
        try {
            if (!on_init.emit(this, all, true)) {
                return ERROR_CODE;
            }
        } catch (const RuntimeError& error) {
            // 'fprintf' is for developer. It's easier to examine info in console, rather than in a message box.
            fprintf(stderr, "%s\n", error.what());
            message_box(error.what());
            is_initialized = false;
        } catch (...) {
            fprintf(stderr, "Runtime error in anonymous 'on_init' listener!\n");
            message_box("Runtime error in anonymous 'on_init' listener!");
            is_initialized = false;
        }

        int32 result = IGame::run();

        try {
            if (!on_destroy.emit(this, all, true)) {
                return ERROR_CODE;
            }
        } catch (const RuntimeError& error) {
            // 'fprintf' is for developer. It's easier to examine info in console, rather than in a message box.
            fprintf(stderr, "%s\n", error.what());
            message_box(error.what());
            is_initialized = false;
        } catch (...) {
            fprintf(stderr, "Runtime error in anonymous 'on_destroy' listener!\n");
            message_box("Runtime error in anonymous 'on_destroy' listener!");
            is_initialized = false;
        }

        return result;
    }

    return ERROR_CODE;
}
} // namespace kw

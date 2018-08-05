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
#include <kw/debug/runtime_error.h>

#include <SDL2/SDL.h>

#include <fmt/format.h>

namespace kw {
namespace i_game_details {
void death_signal(int signum) {
    const String stacktrace = kw::Stacktrace::get_stacktrace(1, 2);
    const String message = fmt::format("Segmentation fault!\n\nStacktrace:\n{}\n", stacktrace.c_str());

    fprintf(stderr, "%s", message.c_str()); // For developers. Sometimes the message box is not even shown.
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Runtime error", message.c_str(), nullptr);

    signal(signum, SIG_DFL);
    exit(3);
}
} // namespace i_game_details

IGame::IGame() noexcept {
    // Safety first.
    signal(SIGSEGV, i_game_details::death_signal);

    is_initialized = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_TIMER) == 0;
    if (!is_initialized) {
        message_box(fmt::format("Failed to initialize SDL2!\nThe error message: {}", SDL_GetError()));
    }
}

IGame::~IGame() noexcept {
    SDL_Quit();
}

int32 IGame::run() noexcept {
    if (is_initialized) {
        try {
            on_init.emit(this);
        } catch (const RuntimeError& error) {
            message_box(error.what());
            return 1;
        } catch (...) {
            message_box("Runtime error in anonymous 'on_init' callback!");
            return 1;
        }

        const int32 result = [this] {
            SDL_Event event;
            while (true) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        return 0;
                    } else {
                        try {
                            on_event.emit(event);
                        } catch (const RuntimeError& error) {
                            message_box(error.what());
                            return 1;
                        } catch (...) {
                            message_box("Runtime error in anonymous 'on_event' callback!");
                            return 1;
                        }
                    }
                }
                try {
                    on_update.emit();
                } catch (const RuntimeError& error) {
                    message_box(error.what());
                    return 1;
                } catch (...) {
                    message_box("Runtime error in anonymous 'on_update' callback!");
                    return 1;
                }
            }
        }();

        try {
            on_destroy.emit(this);
        } catch (const RuntimeError& error) {
            message_box(error.what());
            return 1;
        } catch (...) {
            message_box("Runtime error in anonymous 'on_destroy' callback!");
            return 1;
        }

        return result;
    }

    return 1;
}

void IGame::exit() noexcept {
    SDL_Event event;
    event.type = SDL_QUIT;
    // This one might fail, but we hope it will not.
    SDL_PushEvent(&event);
}

void IGame::message_box(const String& message) const noexcept {
    fputs(message.c_str(), stderr); // For developers. Sometimes the message box is not even shown.
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Runtime error", message.c_str(), nullptr);
}
} // namespace kw

namespace eastl {
size_t hash<std::type_index>::operator()(const std::type_index& value) const {
    return value.hash_code();
}
} // namespace eastl

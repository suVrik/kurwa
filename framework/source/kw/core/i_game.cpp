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

#include <SDL2/SDL.h>

#include <fmt/format.h>

#include <stdexcept>

namespace kw {
IGame::IGame() noexcept {
    is_initialized = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER) == 0;
    if (!is_initialized) {
        message_box(fmt::format("Failed to initialize SDL2!\n"
                                "The error message: {}",
                                SDL_GetError()));
    }
}

IGame::~IGame() noexcept {
    SDL_Quit();
}

int32 IGame::run() noexcept {
    constexpr int32 ERROR_CODE   = 1;
    constexpr int32 SUCCESS_CODE = 0;

    if (is_initialized) {
        SDL_Event event;
        while (true) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    return SUCCESS_CODE;
                } else {
                    try {
                        on_event.emit(event);
                    } catch (const std::runtime_error& error) {
                        message_box(error.what());
                        return ERROR_CODE;
                    } catch (...) {
                        message_box("Runtime error in anonymous 'on_event' callback!");
                        return ERROR_CODE;
                    }
                }
            }
            try {
                on_update.emit();
            } catch (const std::runtime_error& error) {
                message_box(error.what());
                return ERROR_CODE;
            } catch (...) {
                message_box("Runtime error in anonymous 'on_update' callback!");
                return ERROR_CODE;
            }
        }
    }

    return ERROR_CODE;
}

void IGame::exit() noexcept {
    SDL_Event event;
    event.type = SDL_QUIT;
    // This one might fail, but we hope it will not.
    SDL_PushEvent(&event);
}

void IGame::message_box(const String& message) const noexcept {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Runtime error", message.c_str(), nullptr);
}
} // namespace kw

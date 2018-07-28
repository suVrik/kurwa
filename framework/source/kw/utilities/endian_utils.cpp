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

#include <kw/utilities/endian_utils.h>

#include <SDL2/SDL_endian.h>

#undef ntohs
#undef ntohl
#undef ntohll
#undef htons
#undef htonl
#undef htonll

namespace kw {
uint16 EndianUtils::ntohs(uint16 value) noexcept {
    return static_cast<uint16>(SDL_SwapLE16(static_cast<Uint16>(value)));
}

int16 EndianUtils::ntohs(int16 value) noexcept {
    return static_cast<int16>(SDL_SwapLE16(static_cast<Uint16>(value)));
}

uint32 EndianUtils::ntohl(uint32 value) noexcept {
    return static_cast<uint32>(SDL_SwapLE32(static_cast<Uint32>(value)));
}

int32 EndianUtils::ntohl(int32 value) noexcept {
    return static_cast<int32>(SDL_SwapLE32(static_cast<Uint32>(value)));
}

uint64 EndianUtils::ntohll(uint64 value) noexcept {
    return static_cast<uint64>(SDL_SwapLE64(static_cast<Uint64>(value)));
}

int64 EndianUtils::ntohll(int64 value) noexcept {
    return static_cast<int64>(SDL_SwapLE64(static_cast<Uint64>(value)));
}

uint16 EndianUtils::htons(uint16 value) noexcept {
    return static_cast<uint16>(SDL_SwapLE16(static_cast<Uint16>(value)));
}

int16 EndianUtils::htons(int16 value) noexcept {
    return static_cast<int16>(SDL_SwapLE16(static_cast<Uint16>(value)));
}

uint32 EndianUtils::htonl(uint32 value) noexcept {
    return static_cast<uint32>(SDL_SwapLE32(static_cast<Uint32>(value)));
}

int32 EndianUtils::htonl(int32 value) noexcept {
    return static_cast<int32>(SDL_SwapLE32(static_cast<Uint32>(value)));
}

uint64 EndianUtils::htonll(uint64 value) noexcept {
    return static_cast<uint64>(SDL_SwapLE64(static_cast<Uint64>(value)));
}

int64 EndianUtils::htonll(int64 value) noexcept {
    return static_cast<int64>(SDL_SwapLE64(static_cast<Uint64>(value)));
}
} // namespace kw

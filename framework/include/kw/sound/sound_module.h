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

struct ALCdevice_struct;
struct ALCcontext_struct;

namespace kw {
class IGame;
/**
 * `SoundModule` initializes a hardware device and destroys it when necessary.
 */
class SoundModule {
public:
    explicit SoundModule(IGame* game) noexcept(false);
    SoundModule(SoundModule&& original) noexcept;
    SoundModule(const SoundModule&) = delete;
    ~SoundModule() noexcept;
    SoundModule& operator=(SoundModule&& original) noexcept;
    SoundModule& operator=(const SoundModule&) = delete;

private:
    ALCdevice_struct* m_sound_device;
    ALCcontext_struct* m_sound_context;
};
} // namespace kw

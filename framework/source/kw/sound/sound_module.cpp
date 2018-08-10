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

#include <kw/debug/runtime_error.h>
#include <kw/sound/sound_module.h>

#include <AL/alc.h>

namespace kw {
namespace sound_module_details {
// Preserves `SoundModule` from double construction.
bool guard = true;
} // namespace sound_module_details

SoundModule::SoundModule(IGame*) noexcept(false) {
    if (!sound_module_details::guard) {
        throw RuntimeError("Sound module must be constructed once!");
    }
    sound_module_details::guard = false;

    ALCboolean enumeration = alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT");
    if (enumeration == ALC_FALSE) {
        throw RuntimeError("ALC_ENUMERATION_EXT extension is not supported!");
    }

    const char* devices = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
    if (devices == nullptr || *devices == '\0') {
        throw RuntimeError("No sound device available!");
    }

    ALCdevice* sound_device = m_sound_device = alcOpenDevice(devices);
    if (sound_device == nullptr) {
        throw RuntimeError("Failed to open sound device!");
    }

    ALCcontext* sound_context = m_sound_context = alcCreateContext(sound_device, nullptr);
    if (sound_context == nullptr) {
        alcCloseDevice(m_sound_device);
        throw RuntimeError("Failed to create sound context!");
    }

    if (alcMakeContextCurrent(sound_context) == ALC_FALSE) {
        alcDestroyContext(m_sound_context);
        alcCloseDevice(m_sound_device);
        throw RuntimeError("Failed to make current context!");
    }

    if (alcGetError(sound_device) != ALC_NO_ERROR) {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(m_sound_context);
        alcCloseDevice(m_sound_device);
        throw RuntimeError("Failed to construct a sound module!");
    }
}

SoundModule::SoundModule(SoundModule&& original) noexcept
    : m_sound_device(original.m_sound_device)
    , m_sound_context(original.m_sound_context) {
    original.m_sound_device = nullptr;
    original.m_sound_context = nullptr;
}

SoundModule::~SoundModule() noexcept {
    if (m_sound_context != nullptr) {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(m_sound_context);
        alcCloseDevice(m_sound_device);
        sound_module_details::guard = true;
    }
}

SoundModule& SoundModule::operator=(SoundModule&& original) noexcept {
    this->~SoundModule();
    m_sound_device = original.m_sound_device;
    m_sound_context = original.m_sound_context;
    original.m_sound_device = nullptr;
    original.m_sound_context = nullptr;
    return *this;
}
} // namespace kw

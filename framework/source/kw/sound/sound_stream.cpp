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

#include <kw/debug/assert.h>
#include <kw/math/math.h>
#include <kw/sound/sound_stream.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <cstdio>

namespace kw {
SoundStream::SoundStream(SoundStream&& original) noexcept
    : m_source(original.m_source)
    , m_is_looping(original.m_is_looping)
    , m_panning(original.m_panning)
    , m_volume(original.m_volume)
    , m_duration(original.m_duration) {
    original.m_source = 0;
    original.m_is_looping = false;
    original.m_panning = 0.f;
    original.m_volume = 1.f;
    original.m_duration = 0.f;
}

SoundStream::~SoundStream() noexcept {
    if (m_source != 0) {
        alDeleteSources(1, &m_source);

        // It might be a fake destructor like this: `sound_stream->~SoundStream()`.
        // This is exactly what Sound does to its owning `SoundStream` instances, when is being destroyed itself.
        // So we must keep a valid "empty" state.
        m_source = 0;
        m_is_looping = false;
        m_panning = 0.f;
        m_volume = 1.f;
        m_duration = 0.f;
    }
}

SoundStream& SoundStream::operator=(SoundStream&& original) noexcept {
    this->~SoundStream();
    m_source = original.m_source;
    m_is_looping = original.m_is_looping;
    m_panning = original.m_panning;
    m_volume = original.m_volume;
    m_duration = original.m_duration;
    original.m_source = 0;
    original.m_is_looping = false;
    original.m_panning = 0.f;
    original.m_volume = 1.f;
    original.m_duration = 0.f;
    return *this;
}

void SoundStream::stop() noexcept {
    if (m_source != 0) {
        alSourcePause(m_source);
    }
}

void SoundStream::play() noexcept {
    if (m_source != 0) {
        alSourcePlay(m_source);
    }
}

float SoundStream::get_position() const noexcept {
    if (m_source != 0) {
        float value;
        alGetSourcef(m_source, AL_SEC_OFFSET, &value);
        return value;
    }
    return 0.f;
}

void SoundStream::set_position(float value) noexcept {
    if (m_source != 0) {
        alSourcef(m_source, AL_SEC_OFFSET, Math::clamp(value, 0.f, m_duration));
    }
}

float SoundStream::get_volume() const noexcept {
    return m_volume;
}

void SoundStream::set_volume(float value) noexcept {
    if (m_source != 0) {
        m_volume = Math::clamp(value, 0.f, 1.f);

        alSourcef(m_source, AL_GAIN, m_volume);
    }
}

float SoundStream::get_panning() const noexcept {
    return m_panning;
}

void SoundStream::set_panning(float value) noexcept {
    if (m_source != 0) {
        m_panning = Math::clamp(value, -1.f, 1.f);

        alSource3f(m_source, AL_POSITION, Math::sin(m_panning * Math::PI / 2.f), 0.f, Math::cos(m_panning * Math::PI / 2.f));
    }
}

float SoundStream::get_duration() const noexcept {
    return m_duration;
}

bool SoundStream::is_looping() const noexcept {
    return m_is_looping;
}

void SoundStream::set_looping(bool value) noexcept {
    if (m_source != 0) {
        alSourcei(m_source, AL_LOOPING, static_cast<int>(value));
    }
}

bool SoundStream::is_playing() const noexcept {
    if (m_source != 0) {
        int value;
        alGetSourcei(m_source, AL_SOURCE_STATE, &value);
        return value == AL_PLAYING;
    }
    return false;
}

SoundStream::SoundStream(uint32 buffer, float position, bool looping, float volume, float panning, float duration) noexcept {
    if (buffer != 0) {
        alGenSources(1, &m_source);
        if (alGetError() == AL_NO_ERROR) {
            alSourcei(m_source, AL_BUFFER, buffer);
            if (alGetError() == AL_NO_ERROR) {
                m_duration = duration;
                set_position(position);
                set_looping(looping);
                set_volume(volume);
                set_panning(panning);

                alSourcePlay(m_source);

                // Avoid `alDeleteSources` and `m_source = 0`.
                return;
            }
            alDeleteSources(1, &m_source);
        }
        m_source = 0;
    } else {
        m_source = 0;
        m_is_looping = false;
        m_panning = 0.f;
        m_volume = 1.f;
        m_duration = 0.f;
    }
}
} // namespace kw

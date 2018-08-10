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
#include <kw/debug/runtime_error.h>
#include <kw/filesystem/filesystem_utils.h>
#include <kw/math/math.h>
#include <kw/sound/sound.h>

#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#include <SDL2/SDL_endian.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <fstream>

namespace kw {
Sound::Sound() noexcept
    : m_buffer(0)
    , m_volume(1.f)
    , m_panning(0.f)
    , m_duration(0.f) {
}

Sound::Sound(const String& path) noexcept(false) {
    const String sound_path = FilesystemUtils::resolve(FilesystemUtils::get_resource_path(), path);

    FILE* file = fopen(sound_path.c_str(), "rb");
    if (file == nullptr) {
        throw RuntimeError("Failed to open sound file '{}'!", sound_path);
    }

    OggVorbis_File ogg_file{};
    if (ov_open(file, &ogg_file, nullptr, 0) != 0) {
        throw RuntimeError("Failed to process sound file '{}'!", sound_path);
    }

    vorbis_info* info = ov_info(&ogg_file, -1);
    if (info == nullptr) {
        throw RuntimeError("Invalid sound file '{}'!", sound_path);
    }

    if (info->channels != 1 && info->channels != 2) {
        throw RuntimeError("Invalid channels in sound file '{}'!", sound_path);
    }

    Format format = Format::MONO_16;
    if (info->channels == 2) {
        format = Format::STEREO_16;
    }

    auto frequency = static_cast<uint32>(info->rate);

    uint64 bytes;
    int32 bit_stream;
    uint8 array[1024];
    Vector<uint8> buffer_data;
    do {
        bytes = static_cast<uint64>(ov_read(&ogg_file, reinterpret_cast<char*>(array), sizeof(array), static_cast<int>(SDL_BYTEORDER == SDL_BIG_ENDIAN), 2, 1, reinterpret_cast<int*>(&bit_stream)));
        buffer_data.insert(buffer_data.end(), array, array + bytes);
    } while (bytes > 0);

    ov_clear(&ogg_file);

    new (this) Sound(buffer_data.data(), static_cast<uint64>(buffer_data.size()), format, frequency);
}

Sound::Sound(const uint8* data, uint64 size, Format format, uint32 frequency) noexcept(false)
    : m_volume(1.f)
    , m_panning(0.f) {
    KW_ASSERT(alcGetCurrentContext() != nullptr, "OpenAL device is not initialized!");

    alGenBuffers(1, &m_buffer);

    if (alGetError() != AL_NO_ERROR) {
        throw RuntimeError("Failed to generate audio buffers!");
    }

    uint32 bits;
    ALenum sound_format;
    switch (format) {
        case Format::MONO_8:
            bits = 8;
            sound_format = AL_FORMAT_MONO8;
            break;
        case Format::MONO_16:
            bits = 16;
            sound_format = AL_FORMAT_MONO16;
            break;
        case Format::STEREO_8:
            bits = 8;
            sound_format = AL_FORMAT_STEREO8;
            break;
        case Format::STEREO_16:
            bits = 16;
            sound_format = AL_FORMAT_STEREO16;
            break;
    }

    alBufferData(m_buffer, sound_format, data, static_cast<ALsizei>(size), static_cast<ALsizei>(frequency));

    if (alGetError() != AL_NO_ERROR) {
        throw RuntimeError("Not enough memory for the buffer data!");
    }

    m_duration = static_cast<float>(size) / bits / frequency;
}

Sound::Sound(Sound&& original) noexcept
    : m_owned_sound_streams(eastl::move(original.m_owned_sound_streams))
    , m_buffer(original.m_buffer)
    , m_volume(original.m_volume)
    , m_panning(original.m_panning)
    , m_duration(original.m_duration) {
    original.m_buffer = 0;
    original.m_volume = 1.f;
    original.m_panning = 0.f;
    original.m_duration = 0.f;
}

Sound::~Sound() noexcept {
    for (SharedPtr<SoundStream>& sound_stream : m_owned_sound_streams) {
        sound_stream->~SoundStream();
    }

    if (m_buffer != 0) {
        alDeleteBuffers(1, &m_buffer);
        m_buffer = 0;
    }
}

Sound& Sound::operator=(Sound&& original) noexcept {
    this->~Sound();
    m_owned_sound_streams = eastl::move(original.m_owned_sound_streams);
    m_buffer = original.m_buffer;
    m_volume = original.m_volume;
    m_panning = original.m_panning;
    m_duration = original.m_duration;
    original.m_buffer = 0;
    original.m_volume = 1.f;
    original.m_panning = 0.f;
    original.m_duration = 0.f;
    return *this;
}

SharedPtr<SoundStream> Sound::play(float position, bool looping, float volume, float panning) noexcept {
    for (SharedPtr<SoundStream>& sound_stream : m_owned_sound_streams) {
        KW_ASSERT(sound_stream.use_count() > 0, "Invalid behaviour! SoundStream instance must have at least one use!");

        // If the sound is not playing, and there's no one who can change that, use that sound again.
        if (sound_stream.use_count() == 1 && !sound_stream->is_playing()) {
            sound_stream->~SoundStream();
            new (sound_stream.get()) SoundStream(m_buffer, position, looping, volume, panning, m_duration);
            return sound_stream;
        }
    }

    // There's no suitable sounds in a pool, create a new one.
    SharedPtr<SoundStream> result(new SoundStream(m_buffer, position, looping, volume, panning, m_duration));
    m_owned_sound_streams.push_back(result);
    return result;
}

SharedPtr<SoundStream> Sound::play(float position, bool looping) noexcept {
    return play(position, looping, m_volume, m_panning);
}

float Sound::get_duration() const noexcept {
    return m_duration;
}

float Sound::get_volume() const noexcept {
    return m_volume;
}

void Sound::set_volume(float value) noexcept {
    if (m_buffer != 0) {
        m_volume = Math::clamp(value, 0.f, 1.f);
    }
}

float Sound::get_panning() const noexcept {
    return m_panning;
}

void Sound::set_panning(float value) noexcept {
    if (m_buffer != 0) {
        m_panning = Math::clamp(value, -1.f, 1.f);
    }
}
} // namespace kw

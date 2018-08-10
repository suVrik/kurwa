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

#include <kw/base/shared_ptr.h>
#include <kw/base/string.h>
#include <kw/base/types.h>
#include <kw/base/vector.h>
#include <kw/sound/sound_stream.h>

namespace kw {
/**
 * `Sound` is a container for audio data.
 */
class Sound {
public:
    /**
     * All available sound formats.
     */
    enum class Format {
        MONO_8,
        MONO_16,
        STEREO_8,
        STEREO_16,
    };

    /**
     * Construct a 0-duration `Sound` instance.
     */
    Sound() noexcept;

    /**
     * Construct a `Sound` instance using data from the given .ogg file.
     */
    explicit Sound(const String& path) noexcept(false);

    /**
     * Construct a `Sound` instance using provided `data` with the given `size`, `format` and `frequency`.
     */
    Sound(const uint8* data, uint64 size, Format format, uint32 frequency) noexcept(false);

    Sound(const Sound&) = delete;
    Sound(Sound&& original) noexcept;
    ~Sound() noexcept;
    Sound& operator=(Sound&& original) noexcept;
    Sound& operator=(const Sound&) = delete;

    /**
     * Return the `SoundStream` pointer, which will automatically start playing this sound from the given `position`.
     * If `looping` is set as true, when the `SoundStream` is finished, it starts over again.
     * The volume and panning of the `SoundStream` are calculated by the following formula:
     * \f$
     * sound_stream_volume = sound_volume * volume
     * sound_stream_panning = (sound_panning + panning) / 2
     * \f$
     */
    SharedPtr<SoundStream> play(float position, bool looping, float volume, float panning) noexcept;
    SharedPtr<SoundStream> play(float position = 0.f, bool looping = false) noexcept;

    /**
     * Return duration of the Sound in seconds.
     */
    float get_duration() const noexcept;

    /**
     * Return the default volume of the SoundStream produced by `play` method.
     *
     * In range from 0 to 1. Default value is 1.
     */
    float get_volume() const noexcept;

    /**
     * Change the default volume of `SoundSteam` produced by `play` method.
     * `value` will be clamped to range from 0 to 1.
     */
    void set_volume(float value) noexcept;

    /**
     * Return the default panning of the SoundStream produced by `play` method.
     *
     * In range from -1 to 1. Default value is 0.
     */
    float get_panning() const noexcept;

    /**
     * Change the default panning of `SoundSteam` produced by `play` method.
     * `value` will be clamped to range from -1 to 1.
     */
    void set_panning(float value) noexcept;

private:
    Vector<SharedPtr<SoundStream>> m_owned_sound_streams;
    uint32 m_buffer;
    float m_volume;
    float m_panning;
    float m_duration;
};
} // namespace kw

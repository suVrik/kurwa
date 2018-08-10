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

namespace kw {
class Sound;

/**
 * `SoundStream` produces sound.
 */
class SoundStream {
public:
    SoundStream(SoundStream&&) noexcept;
    SoundStream(const SoundStream&) = delete;
    ~SoundStream() noexcept;
    SoundStream& operator=(SoundStream&&) noexcept;
    SoundStream& operator=(const SoundStream&) = delete;

    /**
     * Pause playback. Has no effect when already paused.
     */
    void stop() noexcept;

    /**
     * Resume playback. Has no effect when already playing.
     */
    void play() noexcept;

    /**
     * Return position of the `SoundStream` at the moment. In seconds.
     */
    float get_position() const noexcept;

    /**
     * Change current `SoundStream` position. In seconds.
     */
    void set_position(float value) noexcept;

    /**
     * Return volume of the `SoundStream` in range from 0 to 1.
     */
    float get_volume() const noexcept;

    /**
     * Change volume of `SoundSteam`. `value` will be clamped to range from 0 to 1.
     */
    void set_volume(float value) noexcept;

    /**
     * Return panning of the `SoundStream` in range from -1 to 1.
     */
    float get_panning() const noexcept;

    /**
     * Change panning of the `SoundStream`. `value` will be clamped to range from -1 to 1.
     */
    void set_panning(float value) noexcept;

    /**
     * Return duration of the `Sound` this `SoundStream` is attached to. In seconds.
     */
    float get_duration() const noexcept;

    /**
     * Return true if the `SoundStream` will start playing over, when finished. Return false otherwise.
     */
    bool is_looping() const noexcept;

    /**
     * If `value` is true, the `SoundSteam` will start playing over, when finished.
     * Otherwise it will stop in such situation.
     */
    void set_looping(bool value) noexcept;

    /**
     * Return true if the `SoundStream` is playing at the moment or false otherwise.
     */
    bool is_playing() const noexcept;

private:
    SoundStream(uint32 buffer, float position, bool looping, float volume, float panning, float duration) noexcept;

    uint32 m_source;
    bool m_is_looping;
    float m_panning;
    float m_volume;
    float m_duration;

    friend class Sound; // Allow Sound to construct SoundStream instances.
};
} // namespace kw

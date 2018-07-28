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

/**
 * An utility interface to convert data from/to network byte order, where network byte order is big-endian.
 */
class EndianUtils final {
public:
    /**
     * Convert 16-bit number to network byte order.
     */
    static uint16 ntohs(uint16 value) noexcept;
    static int16 ntohs(int16 value) noexcept;

    /**
     * Convert 32-bit number to network byte order.
     */
    static uint32 ntohl(uint32 value) noexcept;
    static int32 ntohl(int32 value) noexcept;

    /**
     * Convert 64-bit number to network byte order.
     */
    static uint64 ntohll(uint64 value) noexcept;
    static int64 ntohll(int64 value) noexcept;

    /**
     * Convert 16-bit number from network byte order.
     */
    static uint16 htons(uint16 value) noexcept;
    static int16 htons(int16 value) noexcept;

    /**
     * Convert 32-bit number from network byte order.
     */
    static uint32 htonl(uint32 value) noexcept;
    static int32 htonl(int32 value) noexcept;

    /**
     * Convert 64-bit number from network byte order.
     */
    static uint64 htonll(uint64 value) noexcept;
    static int64 htonll(int64 value) noexcept;

    EndianUtils() = delete;
};
} // namespace kw

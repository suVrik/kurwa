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

#include <kw/math/math.h>

namespace kw {
template <class T>
constexpr T Math::abs(T x) noexcept {
    return x < 0 ? -x : x;
}

template <class T>
constexpr T Math::abs_min(T a, T b) noexcept {
    return abs(a) < abs(b) ? a : b;
}

template <class T>
constexpr T Math::abs_max(T a, T b) noexcept {
    return abs(a) > abs(b) ? a : b;
}

template <class T>
constexpr float Math::acos(T x) noexcept {
    return acosf(static_cast<float>(x));
}

template <class T>
constexpr float Math::angle(T from_x, T from_y, T to_x, T to_y) noexcept {
    return atan2f(static_cast<float>(to_y - from_y), static_cast<float>(to_x - from_x));
}

template <class T>
constexpr float Math::asin(T x) noexcept {
    return asinf(static_cast<float>(x));
}

template <class T>
constexpr float Math::atan(T x) noexcept {
    return atanf(static_cast<float>(x));
}

template <class T1, class T2>
constexpr float atan2(T1 y, T2 x) noexcept {
    return atan2f(static_cast<float>(y), static_cast<float>(x));
}

template <class T>
constexpr int Math::ceil(T x) noexcept {
    return static_cast<int>(ceilf(static_cast<float>(x)));
}

template <class T>
constexpr T Math::clamp(T value, T min, T max) noexcept {
    return value < min ? min : (value > max ? max : value);
}

template <class T1, class T2>
constexpr float Math::closest_direction(T1 angle_from, T2 angle_to) noexcept {
    float angle = to_PI2(angle_from) - to_PI2(angle_to);
    return abs_min(angle, angle - sign(angle) * PI_2);
}

template <class T>
constexpr float Math::cos(T x) noexcept {
    return cosf(static_cast<float>(x));
}

template <class T>
constexpr float Math::deg(T rad) noexcept {
    return static_cast<float>(rad) * 180.f / PI;
}

template <class T>
constexpr float Math::dist(T x1, T y1, T x2, T y2) noexcept {
    return sqrtf(static_cast<float>(sqr(x1 - x2)) + static_cast<float>(sqr(y1 - y2)));
}

template <class T>
constexpr T Math::dist2(T x1, T y1, T x2, T y2) noexcept {
    return sqr(x1 - x2) + sqr(y1 - y2);
}

template <class T>
constexpr float Math::exp(T x) noexcept {
    return expf(static_cast<float>(x));
}

template <class T>
constexpr int Math::floor(T x) noexcept {
    return static_cast<int>(floorf(static_cast<float>(x)));
}

template <class T>
constexpr bool Math::is_power_of_two(T value) noexcept {
    for (unsigned i = 0; i < 32; i++) {
        if (value == (1U << i)) {
            return true;
        }
    }
    return false;
}

template <class T>
constexpr T Math::next_power_of_two(T value) noexcept {
    for (unsigned int i = 0; i < 32; i++) {
        if (value <= (1U << i)) {
            return static_cast<T>(1U << i);
        }
    }
    return static_cast<T>(0);
}

template <class T>
constexpr float Math::lerp(T start, T end, float force) noexcept {
    return start + (end - start) * force;
}

template <class T1, class T2>
constexpr float Math::mod(T1 x, T2 y) noexcept {
    return fmodf(static_cast<float>(x), static_cast<float>(y));
}

template <class T>
constexpr float Math::log(T x) noexcept {
    return logf(static_cast<float>(x));
}

template <class T1, class T2>
constexpr T1 Math::max(T1 x, T2 y) noexcept {
    return x > static_cast<T1>(y) ? x : static_cast<T1>(y);
}

template <class T1, class T2>
constexpr T1 Math::min(T1 x, T2 y) noexcept {
    return x < static_cast<T1>(y) ? x : static_cast<T1>(y);
}

template <class T1, class T2>
constexpr float Math::pow(T1 base, T2 pow) noexcept {
    return powf(static_cast<float>(base), static_cast<float>(pow));
}

template <class T>
constexpr float Math::rad(T deg) noexcept {
    return static_cast<float>(deg) / 180.f * PI;
}

template <class T>
constexpr int Math::round(T x) noexcept {
    return static_cast<int>(roundf(static_cast<float>(x)));
}

template <class T>
constexpr int Math::sign(T value) noexcept {
    return value < 0 ? -1 : 1;
}

template <class T>
constexpr int Math::sign0(T value) noexcept {
    return value < 0 ? -1 : (value > 0 ? 1 : 0);
}

template <class T>
constexpr float Math::sin(T x) noexcept {
    return sinf(static_cast<float>(x));
}

template <class T>
constexpr T Math::sqr(T x) noexcept {
    return x * x;
}

template <class T>
constexpr float Math::sqrt(T x) noexcept {
    return sqrtf(static_cast<float>(x));
}

template <class T>
constexpr float Math::tan(T x) noexcept {
    return tanf(static_cast<float>(x));
}

template <class T>
constexpr float Math::to_PI(T x) noexcept {
    float _x = fmodf(static_cast<float>(x), PI_2);
    if (_x >= PI) {
        return _x - PI_2;
    } else if (_x < -PI) {
        return _x + PI_2;
    }
    return _x;
}

template <class T>
constexpr float Math::to_PI2(T x) noexcept {
    float _x = fmodf(static_cast<float>(x), PI_2);
    if (_x < 0) {
        return _x + PI_2;
    }
    return _x;
}

template <class T>
constexpr bool Math::rect_rect(T x1, T y1, T w1, T h1, T x2, T y2, T w2, T h2) noexcept {
    return !(x2 > x1 + w1 || x2 + w2 < x1 || y2 > y1 + h1 || y2 + h2 < y1);
}

template <class T>
constexpr bool Math::point_rect(T x1, T y1, T x2, T y2, T w2, T h2) noexcept {
    return x1 >= x2 && x1 <= x2 + w2 && y1 >= y2 && y1 <= y2 + h2;
}
} // namespace kw

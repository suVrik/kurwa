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

#include <cmath>

namespace kw {
/**
 * The Math class contains common mathematical methods and constants.
 */
class Math {
public:
    /**
     * A mathematical constant representing a very small floating point number.
     */
    static constexpr float EPS = 1E-7f;

    /**
     * A mathematical constant for the ratio of the circumference of a circle to its diameter,
     * expressed as pi, with a value of 3.141592653589793.
     */
    static constexpr float PI = 3.14159265358979323846f;

    /**
     * A mathematical constant for the ratio of the circumference of a circle to its diameter
     * multiplied by 2, expressed as pi, with a value of 6.28318530717958647692.
     */
    static constexpr float PI_2 = 6.28318530717958647692f;

    /**
     * A mathematical constant for the base of natural logarithms, expressed as e.
     */
    static constexpr float E = 2.71828182845905f;

    /**
     * A mathematical constant for the natural logarithm of 10,
     * expressed as loge10, with an approximate value of 2.302585092994046.
     */
    static constexpr float LN10 = 2.302585092994046f;

    /**
     * A mathematical constant for the natural logarithm of 2,
     * expressed as loge2, with an approximate value of 0.6931471805599453.
     */
    static constexpr float LN2 = 0.6931471805599453f;

    /**
     * A mathematical constant for the base-10 logarithm of the constant e (kw::Math::E),
     * expressed as log10e, with an approximate value of 0.4342944819032518.
     */
    static constexpr float LOG10E = 0.4342944819032518f;

    /**
     * A mathematical constant for the base-2 logarithm of the constant e,
     * expressed as log2e, with an approximate value of 1.442695040888963387.
     */
    static constexpr float LOG2E = 1.442695040888963387f;

    /**
     * A mathematical constant for the square root of one-half,
     * with an approximate value of 0.7071067811865476.
     */
    static constexpr float SQRT1_2 = 0.7071067811865476f;

    /**
     * A mathematical constant for the square root of 2,
     * with an approximate value of 1.4142135623730951.
     */
    static constexpr float SQRT2 = 1.4142135623730951f;

    /**
     * Compute and Return an absolute value for the number specified by the parameter x.
     */
    template <class T>
    constexpr static T abs(T x) noexcept;

    /**
     * Evaluate a and b and Return the value, whose absolute value is the smallest.
     */
    template <class T>
    constexpr static T abs_min(T a, T b) noexcept;

    /**
     * Evaluate a and b and Return the value, whose absolute value is the largest.
     */
    template <class T>
    constexpr static T abs_max(T a, T b) noexcept;

    /**
     * Compute and Return the arc cosine of the number specified in the parameter x, in radians.
     */
    template <class T>
    constexpr static float acos(T x) noexcept;

    /**
     * Compute and Return the angle of the point to_x/to_y in radians, when measured
     * counterclockwise from a circle's x axis (where from_x,from_y represents the center of the circle).
     */
    template <class T>
    constexpr static float angle(T from_x, T from_y, T to_x, T to_y) noexcept;

    /**
     * Compute and Return the arc sine for the number specified in the parameter x, in radians.
     */
    template <class T>
    constexpr static float asin(T x) noexcept;

    /**
     * Compute and Return the value, in radians, of the angle whose tangent is specified in the parameter x.
     */
    template <class T>
    constexpr static float atan(T x) noexcept;

    /**
     * Compute and Return the angle of the point y/x in radians, when measured
     * counterclockwise from a circle's x axis (where 0,0 represents the center of the circle).
     */
    template <class T1, class T2>
    constexpr static float atan2(T1 y, T2 x) noexcept;

    /**
     * Return the ceiling of the specified number or expression.
     */
    template <class T>
    constexpr static int ceil(T x) noexcept;

    /**
     * Evaluate value and min, takes the largest value, evaluates max
     * and Return the smallest value among these two.
     */
    template <class T>
    constexpr static T clamp(T value, T min, T max) noexcept;

    /**
     * Return the smallest number that represents an angle measured in radians,
     * that when added to angle_from gives an angle that is equal to angle_to.
     */
    template <class T1, class T2>
    constexpr static float closest_direction(T1 angle_from, T2 angle_to) noexcept;

    /**
     * Compute and Return the cosine of the specified angle in radians.
     */
    template <class T>
    constexpr static float cos(T x) noexcept;

    /**
     * Convert radians into degrees.
     */
    template <class T>
    constexpr static float deg(T rad) noexcept;

    /**
     * Return the distance from the first point to the second.
     */
    template <class T>
    constexpr static float dist(T x1, T y1, T x2, T y2) noexcept;

    /**
     * Return the square distance from the first point to the second.
     */
    template <class T>
    constexpr static T dist2(T x1, T y1, T x2, T y2) noexcept;

    /**
     * Return the value of the base of the natural logarithm (e),
     * to the power of the exponent specified in the parameter x.
     */
    template <class T>
    constexpr static float exp(T x) noexcept;

    /**
     * Return the floor of the number or expression specified in the parameter x.
     */
    template <class T>
    constexpr static int floor(T x) noexcept;

    /**
     * Return true if the value is power of two.
     */
    template <class T>
    constexpr static bool is_power_of_two(T value) noexcept;

    /**
     * Return the next largest power of two value.
     */
    template <class T>
    constexpr static T next_power_of_two(T value) noexcept;

    /**
     * Return the following:
     *
     * \code
     * start + (end - start) * force.
     * \endcode
     */
    template <class T>
    constexpr static float lerp(T start, T end, float force) noexcept;

    /**
     * Compute the floating-point remainder of the division operation x / y.
     */
    template <class T1, class T2>
    constexpr static float mod(T1 x, T2 y) noexcept;

    /**
     * Return the natural logarithm of the parameter x.
     */
    template <class T>
    constexpr static float log(T x) noexcept;

    /**
     * Evaluate x and y and Return the largest value.
     */
    template <class T1, class T2>
    constexpr static T1 max(T1 x, T2 y) noexcept;

    /**
     * Evaluate x and y and Return the smallest value.
     */
    template <class T1, class T2>
    constexpr static T1 min(T1 x, T2 y) noexcept;

    /**
     * Compute and Return base to the power of pow.
     */
    template <class T1, class T2>
    constexpr static float pow(T1 base, T2 pow) noexcept;

    /**
     * Convert degrees into radians.
     */
    template <class T>
    constexpr static float rad(T deg) noexcept;

    /**
     * Round the value of the parameter x up or down to the nearest integer and Return the value.
     */
    template <class T>
    constexpr static int round(T x) noexcept;

    /**
     * Return the sign of the value. Zero is considered to be a positive number.
     */
    template <class T>
    constexpr static int sign(T value) noexcept;

    /**
     * Return the sign of the value or zero.
     */
    template <class T>
    constexpr static int sign0(T value) noexcept;

    /**
     * Compute and Return the sine of the specified angle in radians.
     */
    template <class T>
    constexpr static float sin(T x) noexcept;

    /**
     * Compute and Return the square of the specified number.
     */
    template <class T>
    constexpr static T sqr(T x) noexcept;

    /**
     * Compute and Return the square root of the specified number.
     */
    template <class T>
    constexpr static float sqrt(T x) noexcept;

    /**
     * Compute and Return the tangent of the specified angle.
     */
    template <class T>
    constexpr static float tan(T x) noexcept;

    /**
     * Compute and Return the angle in the range [-PI,PI), that is equal to the specified angle.
     */
    template <class T>
    constexpr static float to_PI(T x) noexcept;

    /**
     * Compute and Return the angle in the range [0, 2 * PI), that is equal to the specified angle.
     */
    template <class T>
    constexpr static float to_PI2(T x) noexcept;

    /**
     * Return true if two given rectangles intersect, otherwise false.
     */
    template <class T>
    constexpr static bool rect_rect(T x1, T y1, T w1, T h1, T x2, T y2, T w2, T h2) noexcept;

    /**
     * Return true if the given point is inside of the given rectangle, otherwise false.
     */
    template <class T>
    constexpr static bool point_rect(T x1, T y1, T x2, T y2, T w2, T h2) noexcept;

    Math() = delete;
};
} // namespace kw

#include <kw/math/internal/math_impl.h>

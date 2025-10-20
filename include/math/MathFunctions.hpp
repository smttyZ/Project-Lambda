// MathFunctions.hpp
// Project Lambda - Mathematical helper functions
// Copyright (C) 2025
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <array>
#include <cmath>

#include "Numbers.hpp"
#include "core/TypeLimits.hpp"
#include "MathConstants.hpp"

namespace lambda::math {

    /**
     * @brief Lookup table size for degree-based trigonometric helpers.
     */
    inline constexpr int TRIG_TABLE_SIZE = 3600;
    inline constexpr double TRIG_STEP_DEGREES = 360.0 / static_cast<double>(TRIG_TABLE_SIZE);

    namespace detail {
        constexpr double NormalizeRadians(double radians) {
            double value = radians;
            while (value > TWO_PI) {
                value -= TWO_PI;
            }
            while (value < 0.0) {
                value += TWO_PI;
            }
            if (value > PI) {
                value -= TWO_PI;
            }
            return value;
        }

        constexpr double SinSeries(double radians) {
            const double x = NormalizeRadians(radians);
            double term = x;
            double sum = term;
            const double xSquared = x * x;
            for (int n = 1; n <= 12; ++n) {
                const double denominator = static_cast<double>((2 * n) * (2 * n + 1));
                term *= -xSquared / denominator;
                sum += term;
            }
            return sum;
        }

        constexpr double CosSeries(double radians) {
            const double x = NormalizeRadians(radians);
            double term = 1.0;
            double sum = term;
            const double xSquared = x * x;
            for (int n = 1; n <= 12; ++n) {
                const double denominator = static_cast<double>((2 * n - 1) * (2 * n));
                term *= -xSquared / denominator;
                sum += term;
            }
            return sum;
        }

        template<typename Func>
        consteval std::array<Real, TRIG_TABLE_SIZE> BuildTrigTable(Func func) {
            std::array<Real, TRIG_TABLE_SIZE> table{};
            for (int i = 0; i < TRIG_TABLE_SIZE; ++i) {
                const double degrees = static_cast<double>(i) * TRIG_STEP_DEGREES;
                const double radians = degrees * DEG2RAD;
                table[static_cast<std::size_t>(i)] = Real{ func(radians) };
            }
            return table;
        }

        inline constexpr std::array<Real, TRIG_TABLE_SIZE> SIN_TABLE =
            BuildTrigTable([](double radians) { return SinSeries(radians); });
        inline constexpr std::array<Real, TRIG_TABLE_SIZE> COS_TABLE =
            BuildTrigTable([](double radians) { return CosSeries(radians); });

        inline double NormalizeDegrees(double degrees) {
            double result = std::fmod(degrees, 360.0);
            if (result < 0.0) {
                result += 360.0;
            }
            return result;
        }

        inline Real LerpTable(const std::array<Real, TRIG_TABLE_SIZE>& table, Real degrees) {
            const double normalized = NormalizeDegrees(degrees.value);
            const double scaled = normalized / TRIG_STEP_DEGREES;
            const double index = std::floor(scaled);
            const int baseIndex = static_cast<int>(index) % TRIG_TABLE_SIZE;
            const double fraction = scaled - index;
            const int nextIndex = (baseIndex + 1) % TRIG_TABLE_SIZE;

            const double v0 = table[static_cast<std::size_t>(baseIndex)].value;
            const double v1 = table[static_cast<std::size_t>(nextIndex)].value;
            return Real{ v0 + (v1 - v0) * fraction };
        }
    } // namespace detail

    /**
     * @brief Returns a fast sine approximation using the degree lookup table.
     */
    inline Real SinDegrees(Real degrees) {
        return detail::LerpTable(detail::SIN_TABLE, degrees);
    }

    /// Backwards-compatible overload that accepts a double angle.
    inline Real SinDegrees(double degrees) { return SinDegrees(Real{ degrees }); }
    /// Alias preserved for existing code.
    inline Real Sin(Real degrees) { return SinDegrees(degrees); }
    /// Alias preserved for double input.
    inline Real Sin(double degrees) { return SinDegrees(Real{ degrees }); }

    /**
     * @brief Returns a fast cosine approximation using the degree lookup table.
     */
    inline Real CosDegrees(Real degrees) {
        return detail::LerpTable(detail::COS_TABLE, degrees);
    }

    /// Backwards-compatible overload that accepts a double angle.
    inline Real CosDegrees(double degrees) { return CosDegrees(Real{ degrees }); }
    /// Alias preserved for existing code.
    inline Real Cos(Real degrees) { return CosDegrees(degrees); }
    /// Alias preserved for double input.
    inline Real Cos(double degrees) { return CosDegrees(Real{ degrees }); }

    /**
     * @brief Computes the circumference of a circle.
     *
     * @param radius Circle radius measured in meters (or consistent unit).
     */
    inline Real CircleCircumference(Real radius) {
        return Real{ 2.0 } * Real{ PI } * radius;
    }

    /**
     * @brief Computes the area of a circle.
     */
    inline Real CircleArea(Real radius) {
        return Real{ PI } * radius * radius;
    }

    /**
     * @brief Computes the diameter of a circle.
     */
    inline Real CircleDiameter(Real radius) {
        return Real{ 2.0 } * radius;
    }

    /**
     * @brief Computes arc length when the angle is expressed in radians.
     */
    inline Real ArcLength(Real radius, Real angleRadians) {
        return radius * angleRadians;
    }

    /**
     * @brief Computes arc length when the angle is expressed in degrees.
     */
    inline Real ArcLengthDegrees(Real radius, Real angleDegrees) {
        return ArcLength(radius, Real{ angleDegrees.value * DEG2RAD });
    }

    /**
     * @brief Computes the area of a sector when the angle is expressed in radians.
     */
    inline Real SectorArea(Real radius, Real angleRadians) {
        return Real{ 0.5 } * radius * radius * angleRadians;
    }

    /**
     * @brief Computes the area of a sector when the angle is expressed in degrees.
     */
    inline Real SectorAreaDegrees(Real radius, Real angleDegrees) {
        return SectorArea(radius, Real{ angleDegrees.value * DEG2RAD });
    }

} // namespace lambda::math

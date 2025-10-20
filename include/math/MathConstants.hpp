// MathConstants.hpp
// Project Lambda - Mathematical constant definitions
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

#include "core/TypeLimits.hpp"

namespace lambda::math {

    /**
     * @brief Fundamental mathematical constants in double precision.
     */
    inline constexpr double PI       = 3.141592653589793238462643383279502884;
    inline constexpr double TWO_PI   = 6.283185307179586476925286766559005768;
    inline constexpr double HALF_PI  = 1.570796326794896619231321691639751442;
    inline constexpr double E        = 2.718281828459045235360287471352662498;
    inline constexpr double SQRT2    = 1.414213562373095048801688724209698079;
    inline constexpr double SQRT3    = 1.732050807568877293527446341505872366;
    inline constexpr double PHI      = 1.618033988749894848204586834365638118; ///< Golden ratio.
    inline constexpr double LN2      = 0.693147180559945309417232121458176568;
    inline constexpr double LN10     = 2.302585092994045684017991454684364208;

    /**
     * @brief Degree/radian conversion factors.
     */
    inline constexpr double DEG2RAD = PI / 180.0;
    inline constexpr double RAD2DEG = 180.0 / PI;

    /**
     * @brief Select physics-related constants reserved for future modules.
     *
     * Units are expressed in SI (meters, seconds, kilograms).
     */
    inline constexpr double SPEED_OF_LIGHT = 299792458.0;      ///< Speed of light in m/s.
    inline constexpr double PLANCK         = 6.62607015e-34;   ///< Planck constant in J·s.
    inline constexpr double GRAVITY        = 9.80665;          ///< Standard gravity in m/s².
    inline constexpr double AVOGADRO       = 6.02214076e23;    ///< Avogadro constant in mol⁻¹.

} // namespace lambda::math

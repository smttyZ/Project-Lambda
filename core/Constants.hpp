// Constants.hpp
// Project Lambda - Mathematical and physical constants
// Copyright (C) 2025
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy at http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <core/Real.hpp>

namespace lambda::core {

/**
 * @brief Mathematical and physical constants in SI units.
 * @details All constants use the Real type to ensure finite, validated values.
 */
namespace Constants {

/**
 * @brief Mathematical constant π (pi).
 * @details Approximately 3.14159265358979323846
 */
inline constexpr double PI_DOUBLE = 3.14159265358979323846264338327950288;

/**
 * @brief Mathematical constant π (pi) as Real.
 */
inline const Real PI{PI_DOUBLE};

/**
 * @brief Mathematical constant 2π (tau).
 */
inline const Real TAU{PI_DOUBLE * 2.0};

/**
 * @brief Mathematical constant π/2 (half pi).
 */
inline const Real HALF_PI{PI_DOUBLE / 2.0};

/**
 * @brief Standard gravitational acceleration on Earth.
 * @details Approximately 9.80665 m/s² (SI units).
 * Used for physics simulations assuming Earth's gravity.
 */
inline const Real G{9.80665};

/**
 * @brief Speed of light in vacuum.
 * @details Approximately 299,792,458 m/s (SI units).
 */
inline const Real C{299792458.0};

/**
 * @brief Avogadro's number.
 * @details Approximately 6.02214076e23 mol⁻¹.
 */
inline const Real AVOGADRO{6.02214076e23};

/**
 * @brief Boltzmann constant.
 * @details Approximately 1.380649e-23 J/K.
 */
inline const Real BOLTZMANN{1.380649e-23};

/**
 * @brief Planck constant.
 * @details Approximately 6.62607015e-34 J⋅s.
 */
inline const Real PLANCK{6.62607015e-34};

/**
 * @brief Elementary charge.
 * @details Approximately 1.602176634e-19 C.
 */
inline const Real ELEMENTARY_CHARGE{1.602176634e-19};

/**
 * @brief Conversion factor from degrees to radians.
 */
inline const Real DEG_TO_RAD{PI_DOUBLE / 180.0};

/**
 * @brief Conversion factor from radians to degrees.
 */
inline const Real RAD_TO_DEG{180.0 / PI_DOUBLE};

} // namespace Constants

} // namespace lambda::core


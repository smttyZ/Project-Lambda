#pragma once
#include "core/TypeLimits.hpp"

namespace lambda::math {

// --- Fundamental constants ---
constexpr double PI       = 3.141592653589793238462643383279502884;
constexpr double TWO_PI   = 6.283185307179586476925286766559005768;
constexpr double HALF_PI  = 1.570796326794896619231321691639751442;
constexpr double E        = 2.718281828459045235360287471352662498;
constexpr double SQRT2    = 1.414213562373095048801688724209698079;
constexpr double SQRT3    = 1.732050807568877293527446341505872366;
constexpr double PHI      = 1.618033988749894848204586834365638118; // golden ratio
constexpr double LN2      = 0.693147180559945309417232121458176568;
constexpr double LN10     = 2.302585092994045684017991454684364208;

// --- Degree/radian conversion ---
constexpr double DEG2RAD = PI / 180.0;
constexpr double RAD2DEG = 180.0 / PI;

// --- Physics-related constants (for later modules) ---
constexpr double SPEED_OF_LIGHT = 299792458.0;      // m/s
constexpr double PLANCK         = 6.62607015e-34;   // J·s
constexpr double GRAVITY        = 9.80665;          // m/s²
constexpr double AVOGADRO       = 6.02214076e23;    // mol⁻¹

} // namespace lambda::math
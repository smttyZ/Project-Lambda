#pragma once

#include "core/TypeLimits.hpp"
#include "MathConstants.hpp"

namespace lambda::math {

    // -- Circle functions --
    constexpr double CircleCircumference(double radius) {
        return 2.0 * lambda::math::PI * radius;
    }

    constexpr double CircleArea(double radius) {
        return lambda::math::PI * radius * radius;
    }

    constexpr double CircleDiameter(double radius) {
        return 2.0 * radius;
    }

    constexpr double ArcLength(double radius, double angle) {
        return radius * angle; // angle in radians
    }

    constexpr double ArcLengthDegrees(double radius, double angleDegrees) {
        return ArcLength(radius, angleDegrees * lambda::math::DEG2RAD);
    }

    constexpr double SectorArea(double radius, double angle) {
        return 0.5 * radius * radius * angle; // angle in radians
    }

    constexpr double SectorAreaDegrees(double radius, double angleDegrees) {
        return SectorArea(radius, angleDegrees * lambda::math::DEG2RAD);
    }
} // namespace lambda::math

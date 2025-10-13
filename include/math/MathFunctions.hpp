#pragma once

#include <cmath> // for std::sin, std::cos
#include "core/TypeLimits.hpp"
#include "MathConstants.hpp"

namespace lambda::math {

    // -- Trigonometric Table --
    inline constexpr int TRIG_TABLE_SIZE = 360;
    inline double sinTable[TRIG_TABLE_SIZE];
    inline double cosTable[TRIG_TABLE_SIZE];

    struct TrigTableInitializer {
        TrigTableInitializer() {
            for (int i = 0; i < TRIG_TABLE_SIZE; ++i) {
                double radians = (lambda::math::PI / 180.0) * i;
                sinTable[i] = std::sin(radians);
                cosTable[i] = std::cos(radians);
            }
        }
    };

    // Global instance: automatically initializes tables before main()
    inline TrigTableInitializer _initTrigTables;

    // -- Sin and Cos functions --
    inline double Sin(double degrees) {
        int index = static_cast<int>(degrees) % TRIG_TABLE_SIZE;
        if (index < 0) index += TRIG_TABLE_SIZE; // handle negative angles
        return sinTable[index];
    }

    inline double Cos(double degrees) {
        int index = static_cast<int>(degrees) % TRIG_TABLE_SIZE;
        if (index < 0) index += TRIG_TABLE_SIZE;
        return cosTable[index];
    }

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

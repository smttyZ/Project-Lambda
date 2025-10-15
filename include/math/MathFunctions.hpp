#pragma once

#include <cmath>

#include "Numbers.hpp"
#include "core/TypeLimits.hpp"
#include "MathConstants.hpp"

namespace lambda::math {

    /**
     * @brief Lookup table size for degree-based trigonometric helpers.
     */
    inline constexpr int TRIG_TABLE_SIZE = 360;

    inline Real sinTable[TRIG_TABLE_SIZE]{};
    inline Real cosTable[TRIG_TABLE_SIZE]{};

    /**
     * @brief Initializes sine and cosine degree tables at startup.
     */
    struct TrigTableInitializer {
        TrigTableInitializer() {
            for (int i = 0; i < TRIG_TABLE_SIZE; ++i) {
                const double radians = (lambda::math::PI / 180.0) * static_cast<double>(i);
                sinTable[i] = Real{ std::sin(radians) };
                cosTable[i] = Real{ std::cos(radians) };
            }
        }
    };

    /// Global instance that ensures tables are populated before main().
    inline TrigTableInitializer g_initTrigTables{};

    /**
     * @brief Returns a fast sine approximation using the degree lookup table.
     */
    inline Real SinDegrees(Real degrees) {
        int index = static_cast<int>(degrees.value) % TRIG_TABLE_SIZE;
        if (index < 0) {
            index += TRIG_TABLE_SIZE;
        }
        return sinTable[index];
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
        int index = static_cast<int>(degrees.value) % TRIG_TABLE_SIZE;
        if (index < 0) {
            index += TRIG_TABLE_SIZE;
        }
        return cosTable[index];
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

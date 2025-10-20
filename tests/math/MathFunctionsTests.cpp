// MathFunctionsTests.cpp
// Project Lambda - Unit tests for math helper functions

#include <cmath>
#include <gtest/gtest.h>

#include "math/MathConstants.hpp"
#include "math/MathFunctions.hpp"

namespace lambda::math {

TEST(MathFunctions_SinDegrees, MatchesStdSinForFractionalAngles) {
    const double degrees = 12.5;
    const Real result = SinDegrees(degrees);
    const double expected = std::sin(degrees * DEG2RAD);
    EXPECT_NEAR(result.value, expected, 1e-6);
}

TEST(MathFunctions_SinDegrees, HandlesLargeNegativeAngles) {
    const double degrees = -725.125;
    const Real result = SinDegrees(degrees);
    const double expected = std::sin(std::fmod(degrees, 360.0) * DEG2RAD);
    EXPECT_NEAR(result.value, expected, 1e-6);
}

TEST(MathFunctions_CosDegrees, MatchesStdCosForFractionalAngles) {
    const double degrees = 179.4;
    const Real result = CosDegrees(degrees);
    const double expected = std::cos(degrees * DEG2RAD);
    EXPECT_NEAR(result.value, expected, 1e-6);
}

TEST(MathFunctions_Geometry, ComputesCircleValues) {
    const Real radius{2.5};
    EXPECT_DOUBLE_EQ(CircleDiameter(radius).value, 5.0);
    EXPECT_NEAR(CircleCircumference(radius).value, 2.0 * PI * 2.5, 1e-12);
    EXPECT_NEAR(CircleArea(radius).value, PI * 2.5 * 2.5, 1e-12);
}

TEST(MathFunctions_Geometry, ArcLengthDegreesMatchesRadians) {
    const Real radius{5.0};
    const Real angle{50.0};
    const Real arcDegrees = ArcLengthDegrees(radius, angle);
    const Real arcRadians = ArcLength(radius, Real{angle.value * DEG2RAD});
    EXPECT_NEAR(arcDegrees.value, arcRadians.value, 1e-12);
}

} // namespace lambda::math

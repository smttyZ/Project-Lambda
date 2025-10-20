// VectorsTests.cpp
// Project Lambda - Unit tests for vector math utilities

#include <gtest/gtest.h>

#include "math/Vectors.hpp"

namespace lambda::math {

TEST(Vectors_Vector3, LengthAndNormalization) {
    const Vector3 vec{ Real{3.0}, Real{4.0}, Real{0.0} };
    EXPECT_DOUBLE_EQ(vec.Length().value, 5.0);

    const Vector3 normalized = vec.Normalized();
    EXPECT_NEAR(normalized.x.value, 0.6, 1e-12);
    EXPECT_NEAR(normalized.y.value, 0.8, 1e-12);
    EXPECT_NEAR(normalized.z.value, 0.0, 1e-12);
}

TEST(Vectors_Vector3, CrossProductProducesOrthogonalVector) {
    const Vector3 xAxis{ Real{1.0}, Real{0.0}, Real{0.0} };
    const Vector3 yAxis{ Real{0.0}, Real{1.0}, Real{0.0} };

    const Vector3 result = xAxis.Cross(yAxis);
    EXPECT_DOUBLE_EQ(result.x.value, 0.0);
    EXPECT_DOUBLE_EQ(result.y.value, 0.0);
    EXPECT_DOUBLE_EQ(result.z.value, 1.0);
}

TEST(Vectors_Vector4, ScalarOperations) {
    Vector4 vec{ Real{1.0}, Real{2.0}, Real{-1.0}, Real{0.5} };
    const Vector4 scaled = vec * Real{2.0};

    EXPECT_DOUBLE_EQ(scaled.x.value, 2.0);
    EXPECT_DOUBLE_EQ(scaled.y.value, 4.0);
    EXPECT_DOUBLE_EQ(scaled.z.value, -2.0);
    EXPECT_DOUBLE_EQ(scaled.w.value, 1.0);

    vec.Normalize();
    const Real length = vec.Length();
    EXPECT_NEAR(length.value, 1.0, 1e-12);
}

} // namespace lambda::math

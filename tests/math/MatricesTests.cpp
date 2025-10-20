// MatricesTests.cpp
// Project Lambda - Unit tests for matrix utilities

#include <cmath>
#include <gtest/gtest.h>
#include "math/MathConstants.hpp"
#include "math/Matrices.hpp"

namespace lambda::math {

TEST(Matrices_Matrix3, RotationZRotatesVector) {
    const Matrix3 rotation = Matrix3::RotationZ(Real{PI / 2.0});
    const Vector3 original{ Real{1.0}, Real{0.0}, Real{0.0} };
    const Vector3 rotated = rotation * original;

    EXPECT_NEAR(rotated.x.value, 0.0, 1e-12);
    EXPECT_NEAR(rotated.y.value, 1.0, 1e-12);
    EXPECT_NEAR(rotated.z.value, 0.0, 1e-12);
}

TEST(Matrices_Matrix4, TranslationPlacesVector) {
    const Vector3 translation{ Real{10.0}, Real{-2.0}, Real{5.0} };
    const Matrix4 transform = Matrix4::Translation(translation);

    EXPECT_DOUBLE_EQ(transform(0, 3).value, 10.0);
    EXPECT_DOUBLE_EQ(transform(1, 3).value, -2.0);
    EXPECT_DOUBLE_EQ(transform(2, 3).value, 5.0);
}

TEST(Matrices_Matrix4, PerspectiveProducesExpectedElements) {
    const Real fov{45.0 * DEG2RAD};
    const Real aspect{1.5};
    const Real nearPlane{0.1};
    const Real farPlane{100.0};
    const Matrix4 perspective = Matrix4::Perspective(fov, aspect, nearPlane, farPlane);

    const double f = 1.0 / std::tan(static_cast<double>(fov.value) * 0.5);
    EXPECT_NEAR(perspective(0, 0).value, f / aspect.value, 1e-12);
    EXPECT_NEAR(perspective(1, 1).value, f, 1e-12);
    EXPECT_NEAR(perspective(2, 2).value,
                (farPlane.value + nearPlane.value) / (nearPlane.value - farPlane.value),
                1e-12);
    EXPECT_NEAR(perspective(3, 2).value, -1.0, 1e-12);
}

TEST(Matrices_Transform, ToMatrixComposesTRS) {
    Transform transform{};
    transform.position = Vector3{ Real{1.0}, Real{2.0}, Real{3.0} };
    transform.scale = Vector3{ Real{2.0}, Real{2.0}, Real{2.0} };
    transform.rotation = Vector3{ Real{0.0}, Real{0.0}, Real{PI / 2.0} };

    const Matrix4 matrix = transform.ToMatrix();
    EXPECT_DOUBLE_EQ(matrix(0, 3).value, 1.0);
    EXPECT_DOUBLE_EQ(matrix(1, 3).value, 2.0);
    EXPECT_DOUBLE_EQ(matrix(2, 3).value, 3.0);

    const Vector4 point{ Real{1.0}, Real{0.0}, Real{0.0}, Real{1.0} };
    const Vector4 transformed = matrix * point;
    EXPECT_NEAR(transformed.x.value, 1.0, 1e-12);
    EXPECT_NEAR(transformed.y.value, 4.0, 1e-12);
    EXPECT_NEAR(transformed.z.value, 3.0, 1e-12);
}

} // namespace lambda::math

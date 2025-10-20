// CameraTests.cpp
// Project Lambda - Unit tests for camera utilities

#include <cmath>
#include <gtest/gtest.h>

#include "math/Camera.h"
#include "math/Matrices.hpp"

namespace lambda::math {

TEST(Camera_ViewMatrix, PositionsCameraAtOriginLookingAtTarget) {
    Camera camera{};
    camera.position = Vector3{ Real{0.0}, Real{0.0}, Real{5.0} };
    camera.target = Vector3{ Real{0.0}, Real{0.0}, Real{0.0} };
    camera.up = Vector3{ Real{0.0}, Real{1.0}, Real{0.0} };

    const Matrix4 view = camera.GetViewMatrix();
    const Vector4 eyePoint{ camera.position.x, camera.position.y, camera.position.z, Real{1.0} };
    const Vector4 cameraSpace = view * eyePoint;

    EXPECT_NEAR(cameraSpace.x.value, 0.0, 1e-12);
    EXPECT_NEAR(cameraSpace.y.value, 0.0, 1e-12);
    EXPECT_NEAR(cameraSpace.z.value, 0.0, 1e-12);
    EXPECT_NEAR(cameraSpace.w.value, 1.0, 1e-12);
}

TEST(Camera_ProjectionMatrix, MatchesPerspectiveMatrix) {
    Camera camera{};
    camera.fov = Real{60.0};
    camera.aspect = Real{1.7777777778};
    camera.nearPlane = Real{0.1};
    camera.farPlane = Real{500.0};

    const Matrix4 projection = camera.GetProjectionMatrix();
    const Real fovRadians = camera.fov * Real{DEG2RAD};
    const Matrix4 expected = Matrix4::Perspective(fovRadians, camera.aspect, camera.nearPlane, camera.farPlane);

    for (std::size_t row = 0; row < 4; ++row) {
        for (std::size_t col = 0; col < 4; ++col) {
            EXPECT_NEAR(projection(row, col).value, expected(row, col).value, 1e-12);
        }
    }
}

} // namespace lambda::math

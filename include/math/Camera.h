#pragma once
#include "MathConstants.hpp"
#include "Matrices.hpp"
#include "Vectors.hpp"

namespace lambda::math {
/**
 * @brief Look-at camera parameters used to build view and projection matrices.
 */
struct Camera {
    /// Camera position in world space.
    Vector3 position;
    /// Point in world space the camera looks toward.
    Vector3 target;
    /// Up direction hint used to resolve the camera basis.
    Vector3 up;

    /// Vertical field of view in degrees.
    Real fov;
    /// Width divided by height of the viewport.
    Real aspect;
    /// Near clipping distance (positive and non-zero).
    Real nearPlane;
    /// Far clipping distance (positive and greater than near plane).
    Real farPlane;

    /**
     * @brief Builds a right-handed view matrix looking from @ref position toward @ref target.
     *
     * Falls back to safe up vectors when @ref up aligns with the forward vector and returns
     * the identity matrix if the camera degenerates to a point.
     */
    [[nodiscard]] inline Matrix4 GetViewMatrix() const {
        const Vector3 forwardDirection = target - position;
        if (forwardDirection.LengthSquared() == Real{}) {
            return Matrix4::Identity();
        }

        const Vector3 forward = forwardDirection.Normalized();
        Vector3 upDirection = up;
        if (upDirection.LengthSquared() == Real{}) {
            upDirection = Vector3{Real{0}, Real{1}, Real{0}};
        }
        upDirection = upDirection.Normalized();

        Vector3 right = forward.Cross(upDirection);
        if (right.LengthSquared() == Real{}) {
            upDirection = Vector3{Real{0}, Real{0}, Real{1}};
            right = forward.Cross(upDirection);
            if (right.LengthSquared() == Real{}) {
                upDirection = Vector3{Real{1}, Real{0}, Real{0}};
                right = forward.Cross(upDirection);
            }
        }
        right = right.Normalized();

        const Vector3 cameraUp = right.Cross(forward).Normalized();

        Matrix4 view{};
        view(0, 0) = right.x;
        view(0, 1) = right.y;
        view(0, 2) = right.z;
        view(0, 3) = -right.Dot(position);

        view(1, 0) = cameraUp.x;
        view(1, 1) = cameraUp.y;
        view(1, 2) = cameraUp.z;
        view(1, 3) = -cameraUp.Dot(position);

        view(2, 0) = -forward.x;
        view(2, 1) = -forward.y;
        view(2, 2) = -forward.z;
        view(2, 3) = forward.Dot(position);

        view(3, 0) = Real{0};
        view(3, 1) = Real{0};
        view(3, 2) = Real{0};
        view(3, 3) = Real{1};

        return view;
    }

    /**
     * @brief Builds a perspective projection matrix using the stored frustum parameters.
     */
    [[nodiscard]] inline Matrix4 GetProjectionMatrix() const {
        const Real fovRadians = fov * Real{DEG2RAD};
        return Matrix4::Perspective(fovRadians, aspect, nearPlane, farPlane);
    }
};
} // namespace lambda::math

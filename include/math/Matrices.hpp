// Matrices.hpp
// Project Lambda - Matrix math utilities
// Copyright (C) 2025
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <array>
#include <cmath>

#include "Vectors.hpp"

namespace lambda::math {

    /**
     * @brief 3x3 matrix primarily used for rotations and normal transforms.
     *
     * Storage is row-major: element (row, column) lives at index row * 3 + column.
     */
    struct Matrix3 {
        std::array<Real, 9> data{
            Real{1}, Real{0}, Real{0},
            Real{0}, Real{1}, Real{0},
            Real{0}, Real{0}, Real{1}
        };

        /// Accesses the element at the given row and column.
        [[nodiscard]] constexpr Real& operator()(std::size_t row, std::size_t column) {
            return data[row * 3 + column];
        }
        /// Accesses the element at the given row and column.
        [[nodiscard]] constexpr Real operator()(std::size_t row, std::size_t column) const {
            return data[row * 3 + column];
        }

        /// Multiplies this matrix by another 3x3 matrix.
        [[nodiscard]] constexpr Matrix3 operator*(const Matrix3& rhs) const {
            Matrix3 result{};
            for (std::size_t row = 0; row < 3; ++row) {
                for (std::size_t col = 0; col < 3; ++col) {
                    Real sum{};
                    for (std::size_t k = 0; k < 3; ++k) {
                        sum += (*this)(row, k) * rhs(k, col);
                    }
                    result(row, col) = sum;
                }
            }
            return result;
        }

        /// Multiplies this matrix with a Vector3.
        [[nodiscard]] constexpr Vector3 operator*(Vector3 vec) const {
            return {
                (*this)(0, 0) * vec.x + (*this)(0, 1) * vec.y + (*this)(0, 2) * vec.z,
                (*this)(1, 0) * vec.x + (*this)(1, 1) * vec.y + (*this)(1, 2) * vec.z,
                (*this)(2, 0) * vec.x + (*this)(2, 1) * vec.y + (*this)(2, 2) * vec.z
            };
        }

        /// Returns the identity matrix.
        [[nodiscard]] static constexpr Matrix3 Identity() { return Matrix3{}; }

        /// Builds a rotation matrix about the X axis by the given angle in radians.
        [[nodiscard]] static Matrix3 RotationX(Real radians) {
            const auto c = Real{ std::cos(static_cast<double>(radians.value)) };
            const auto s = Real{ std::sin(static_cast<double>(radians.value)) };
            Matrix3 matrix{};
            matrix(1, 1) = c;
            matrix(1, 2) = -s;
            matrix(2, 1) = s;
            matrix(2, 2) = c;
            return matrix;
        }

        /// Builds a rotation matrix about the Y axis by the given angle in radians.
        [[nodiscard]] static Matrix3 RotationY(Real radians) {
            const auto c = Real{ std::cos(static_cast<double>(radians.value)) };
            const auto s = Real{ std::sin(static_cast<double>(radians.value)) };
            Matrix3 matrix{};
            matrix(0, 0) = c;
            matrix(0, 2) = s;
            matrix(2, 0) = -s;
            matrix(2, 2) = c;
            return matrix;
        }

        /// Builds a rotation matrix about the Z axis by the given angle in radians.
        [[nodiscard]] static Matrix3 RotationZ(Real radians) {
            const auto c = Real{ std::cos(static_cast<double>(radians.value)) };
            const auto s = Real{ std::sin(static_cast<double>(radians.value)) };
            Matrix3 matrix{};
            matrix(0, 0) = c;
            matrix(0, 1) = -s;
            matrix(1, 0) = s;
            matrix(1, 1) = c;
            return matrix;
        }
    };

    /**
     * @brief 4x4 matrix for affine transformations in homogeneous coordinates.
     *
     * Row-major storage allows direct multiplication with column vectors represented
     * by Vector4. The fourth row/column encodes translation and perspective terms.
     */
    struct Matrix4 {
        std::array<Real, 16> data{
            Real{1}, Real{0}, Real{0}, Real{0},
            Real{0}, Real{1}, Real{0}, Real{0},
            Real{0}, Real{0}, Real{1}, Real{0},
            Real{0}, Real{0}, Real{0}, Real{1}
        };

        /// Accesses the element at the given row and column.
        [[nodiscard]] constexpr Real& operator()(std::size_t row, std::size_t column) {
            return data[row * 4 + column];
        }
        /// Accesses the element at the given row and column.
        [[nodiscard]] constexpr Real operator()(std::size_t row, std::size_t column) const {
            return data[row * 4 + column];
        }

        /// Multiplies two 4x4 matrices.
        [[nodiscard]] constexpr Matrix4 operator*(const Matrix4& rhs) const {
            Matrix4 result{};
            for (std::size_t row = 0; row < 4; ++row) {
                for (std::size_t col = 0; col < 4; ++col) {
                    Real sum{};
                    for (std::size_t k = 0; k < 4; ++k) {
                        sum += (*this)(row, k) * rhs(k, col);
                    }
                    result(row, col) = sum;
                }
            }
            return result;
        }

        /// Multiplies this matrix by a Vector4.
        [[nodiscard]] constexpr Vector4 operator*(Vector4 vec) const {
            return {
                (*this)(0, 0) * vec.x + (*this)(0, 1) * vec.y + (*this)(0, 2) * vec.z + (*this)(0, 3) * vec.w,
                (*this)(1, 0) * vec.x + (*this)(1, 1) * vec.y + (*this)(1, 2) * vec.z + (*this)(1, 3) * vec.w,
                (*this)(2, 0) * vec.x + (*this)(2, 1) * vec.y + (*this)(2, 2) * vec.z + (*this)(2, 3) * vec.w,
                (*this)(3, 0) * vec.x + (*this)(3, 1) * vec.y + (*this)(3, 2) * vec.z + (*this)(3, 3) * vec.w
            };
        }

        /// Returns the identity matrix.
        [[nodiscard]] static constexpr Matrix4 Identity() { return Matrix4{}; }

        /// Builds a translation matrix by the given vector.
        [[nodiscard]] static constexpr Matrix4 Translation(Vector3 translation) {
            Matrix4 matrix{};
            matrix(0, 3) = translation.x;
            matrix(1, 3) = translation.y;
            matrix(2, 3) = translation.z;
            return matrix;
        }

        /// Builds a uniform scale matrix.
        [[nodiscard]] static constexpr Matrix4 Scale(Real uniform) {
            Matrix4 matrix{};
            matrix(0, 0) = uniform;
            matrix(1, 1) = uniform;
            matrix(2, 2) = uniform;
            return matrix;
        }

        /// Builds a non-uniform scale matrix.
        [[nodiscard]] static constexpr Matrix4 Scale(Vector3 axes) {
            Matrix4 matrix{};
            matrix(0, 0) = axes.x;
            matrix(1, 1) = axes.y;
            matrix(2, 2) = axes.z;
            return matrix;
        }

        /// Builds a rotation matrix around the X axis by the given radians.
        [[nodiscard]] static Matrix4 RotationX(Real radians) {
            Matrix4 matrix{};
            const auto rot = Matrix3::RotationX(radians);
            copyTopLeft(matrix, rot);
            return matrix;
        }

        /// Builds a rotation matrix around the Y axis by the given radians.
        [[nodiscard]] static Matrix4 RotationY(Real radians) {
            Matrix4 matrix{};
            const auto rot = Matrix3::RotationY(radians);
            copyTopLeft(matrix, rot);
            return matrix;
        }

        /// Builds a rotation matrix around the Z axis by the given radians.
        [[nodiscard]] static Matrix4 RotationZ(Real radians) {
            Matrix4 matrix{};
            const auto rot = Matrix3::RotationZ(radians);
            copyTopLeft(matrix, rot);
            return matrix;
        }

        /// Builds a perspective projection matrix using vertical fov, aspect ratio, and near/far planes.
        [[nodiscard]] static Matrix4 Perspective(Real fovYRadians, Real aspectRatio, Real nearPlane, Real farPlane) {
            const double f = 1.0 / std::tan(static_cast<double>(fovYRadians.value) * 0.5);
            Matrix4 matrix{};
            matrix(0, 0) = Real{ f / static_cast<double>(aspectRatio.value) };
            matrix(1, 1) = Real{ f };
            matrix(2, 2) = Real{ (farPlane.value + nearPlane.value) / (nearPlane.value - farPlane.value) };
            matrix(2, 3) = Real{ (Real{2} * farPlane * nearPlane).value / (nearPlane.value - farPlane.value) };
            matrix(3, 2) = Real{ -1.0 };
            matrix(3, 3) = Real{ 0.0 };
            return matrix;
        }

        /// Builds an orthographic projection matrix defined by the clipping planes.
        [[nodiscard]] static Matrix4 Orthographic(Real left, Real right, Real bottom, Real top, Real nearPlane, Real farPlane) {
            Matrix4 matrix{};
            matrix(0, 0) = Real{ 2.0 / (right.value - left.value) };
            matrix(1, 1) = Real{ 2.0 / (top.value - bottom.value) };
            matrix(2, 2) = Real{ -2.0 / (farPlane.value - nearPlane.value) };
            matrix(0, 3) = Real{ -(right.value + left.value) / (right.value - left.value) };
            matrix(1, 3) = Real{ -(top.value + bottom.value) / (top.value - bottom.value) };
            matrix(2, 3) = Real{ -(farPlane.value + nearPlane.value) / (farPlane.value - nearPlane.value) };
            return matrix;
        }

    private:
        static constexpr void copyTopLeft(Matrix4& matrix, const Matrix3& source) {
            for (std::size_t row = 0; row < 3; ++row) {
                for (std::size_t col = 0; col < 3; ++col) {
                    matrix(row, col) = source(row, col);
                }
            }
        }
    };

    /**
     * @brief Represents position, orientation, and scale for world objects.
     *
     * Combines translation, rotation, and scale to produce a model matrix. Rotation
     * is stored as Euler angles in radians (pitch, yaw, roll) for simplicity.
     */
    struct Transform {
        Vector3 position{};
        Vector3 rotation{}; // pitch (x), yaw (y), roll (z) in radians
        Vector3 scale{ Real{1}, Real{1}, Real{1} };

        /// Produces a model matrix combining scale, rotations, and translation.
        [[nodiscard]] Matrix4 ToMatrix() const {
            const Matrix4 scaling = Matrix4::Scale(scale);
            const Matrix4 rotX = Matrix4::RotationX(rotation.x);
            const Matrix4 rotY = Matrix4::RotationY(rotation.y);
            const Matrix4 rotZ = Matrix4::RotationZ(rotation.z);
            const Matrix4 translation = Matrix4::Translation(position);

            return translation * (rotZ * (rotY * (rotX * scaling)));
        }
    };

} // namespace lambda::math

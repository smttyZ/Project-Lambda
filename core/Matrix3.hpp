// Matrix3.hpp
// Project Lambda - 3x3 matrix math type
// Copyright (C) 2025
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy at http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <core/Real.hpp>
#include <core/Vector3.hpp>

#include <array>
#include <cstddef>
#include <cmath>
#include <limits>

namespace lambda::core {

/**
 * @brief 3x3 matrix using Real components.
 * @details Provides matrix operations for 3D transformations.
 * Matrix storage is row-major order: [m00, m01, m02, m10, m11, m12, m20, m21, m22]
 */
class Matrix3 final {
public:
    /**
     * @brief Creates a zero matrix (all elements set to zero).
     */
    constexpr Matrix3() noexcept = default;

    /**
     * @brief Creates an identity matrix.
     * @return Identity matrix with ones on the diagonal, zeros elsewhere.
     */
    [[nodiscard]] static Matrix3 Identity() noexcept {
        Matrix3 result{};
        result._m[0][0] = Real{1.0};
        result._m[1][1] = Real{1.0};
        result._m[2][2] = Real{1.0};
        return result;
    }

    /**
     * @brief Creates a matrix from 9 values in row-major order.
     * @param m00 Element at row 0, column 0.
     * @param m01 Element at row 0, column 1.
     * @param m02 Element at row 0, column 2.
     * @param m10 Element at row 1, column 0.
     * @param m11 Element at row 1, column 1.
     * @param m12 Element at row 1, column 2.
     * @param m20 Element at row 2, column 0.
     * @param m21 Element at row 2, column 1.
     * @param m22 Element at row 2, column 2.
     */
    Matrix3(Real m00, Real m01, Real m02,
            Real m10, Real m11, Real m12,
            Real m20, Real m21, Real m22) noexcept
        : _m{{m00, m01, m02},
             {m10, m11, m12},
             {m20, m21, m22}} {
    }

    /**
     * @brief Creates a matrix from a 3x3 array (row-major order).
     * @param values Array of 9 values in row-major order.
     */
    explicit Matrix3(const std::array<Real, 9>& values) noexcept
        : _m{{values[0], values[1], values[2]},
             {values[3], values[4], values[5]},
             {values[6], values[7], values[8]}} {
    }

    /**
     * @brief Creates a matrix from a 2D array (row-major order).
     * @param values 3x3 array of Real values.
     */
    explicit Matrix3(const Real values[3][3]) noexcept
        : _m{{values[0][0], values[0][1], values[0][2]},
             {values[1][0], values[1][1], values[1][2]},
             {values[2][0], values[2][1], values[2][2]}} {
    }

    /**
     * @brief Copy constructor.
     * @param other Matrix to copy from.
     */
    constexpr Matrix3(const Matrix3& other) noexcept = default;

    /**
     * @brief Move constructor.
     * @param other Matrix to move from.
     */
    constexpr Matrix3(Matrix3&& other) noexcept = default;

    /**
     * @brief Copy assignment operator.
     * @param other Matrix to copy from.
     * @return Reference to this matrix.
     */
    Matrix3& operator=(const Matrix3& other) noexcept = default;

    /**
     * @brief Move assignment operator.
     * @param other Matrix to move from.
     * @return Reference to this matrix.
     */
    Matrix3& operator=(Matrix3&& other) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~Matrix3() noexcept = default;

    /**
     * @brief Accesses an element by row and column indices.
     * @param row Row index (0-2).
     * @param col Column index (0-2).
     * @return Reference to the element at the specified position.
     */
    [[nodiscard]] Real& At(std::size_t row, std::size_t col) noexcept {
        return _m[row][col];
    }

    /**
     * @brief Accesses an element by row and column indices (const).
     * @param row Row index (0-2).
     * @param col Column index (0-2).
     * @return Const reference to the element at the specified position.
     */
    [[nodiscard]] const Real& At(std::size_t row, std::size_t col) const noexcept {
        return _m[row][col];
    }

    /**
     * @brief Gets an element by row and column indices.
     * @param row Row index (0-2).
     * @param col Column index (0-2).
     * @return Element value at the specified position.
     */
    [[nodiscard]] constexpr Real Get(std::size_t row, std::size_t col) const noexcept {
        return _m[row][col];
    }

    /**
     * @brief Sets an element by row and column indices.
     * @param row Row index (0-2).
     * @param col Column index (0-2).
     * @param value New element value.
     */
    void Set(std::size_t row, std::size_t col, Real value) noexcept {
        _m[row][col] = value;
    }

    /**
     * @brief Gets a row as a Vector3.
     * @param row Row index (0-2).
     * @return Vector3 containing the row elements.
     */
    [[nodiscard]] Vector3 GetRow(std::size_t row) const noexcept;

    /**
     * @brief Gets a column as a Vector3.
     * @param col Column index (0-2).
     * @return Vector3 containing the column elements.
     */
    [[nodiscard]] Vector3 GetColumn(std::size_t col) const noexcept;

    /**
     * @brief Sets a row from a Vector3.
     * @param row Row index (0-2).
     * @param values Vector3 containing the new row elements.
     */
    void SetRow(std::size_t row, const Vector3& values) noexcept;

    /**
     * @brief Sets a column from a Vector3.
     * @param col Column index (0-2).
     * @param values Vector3 containing the new column elements.
     */
    void SetColumn(std::size_t col, const Vector3& values) noexcept;

    /**
     * @brief Computes the transpose of this matrix.
     * @return Transposed matrix.
     */
    [[nodiscard]] Matrix3 Transposed() const noexcept;

    /**
     * @brief Computes the determinant of this matrix.
     * @return Determinant value.
     */
    [[nodiscard]] Real Determinant() const noexcept;

    /**
     * @brief Computes the inverse of this matrix.
     * @return Inverse matrix.
     */
    [[nodiscard]] Matrix3 Inverted() const noexcept;

    /**
     * @brief Unary plus operator.
     * @return Copy of this matrix.
     */
    [[nodiscard]] constexpr Matrix3 operator+() const noexcept {
        return *this;
    }

    /**
     * @brief Unary minus operator.
     * @return Negated matrix.
     */
    [[nodiscard]] Matrix3 operator-() const noexcept;

    /**
     * @brief Matrix addition.
     * @param other Other matrix.
     * @return Sum of the two matrices.
     */
    [[nodiscard]] Matrix3 operator+(const Matrix3& other) const noexcept;

    /**
     * @brief Matrix subtraction.
     * @param other Other matrix.
     * @return Difference of the two matrices.
     */
    [[nodiscard]] Matrix3 operator-(const Matrix3& other) const noexcept;

    /**
     * @brief Matrix multiplication.
     * @param other Other matrix.
     * @return Product of the two matrices.
     */
    [[nodiscard]] Matrix3 operator*(const Matrix3& other) const noexcept;

    /**
     * @brief Matrix-vector multiplication.
     * @param vec Vector to multiply.
     * @return Transformed vector.
     */
    [[nodiscard]] Vector3 operator*(const Vector3& vec) const noexcept;

    /**
     * @brief Scalar multiplication.
     * @param scalar Scalar value.
     * @return Matrix scaled by @p scalar.
     */
    [[nodiscard]] Matrix3 operator*(Real scalar) const noexcept;

    /**
     * @brief Scalar division.
     * @param scalar Scalar value.
     * @return Matrix divided by @p scalar.
     */
    [[nodiscard]] Matrix3 operator/(Real scalar) const noexcept;

    /**
     * @brief Equality comparison.
     * @param other Other matrix.
     * @return true if all elements are equal.
     */
    [[nodiscard]] constexpr bool operator==(const Matrix3& other) const noexcept {
        return _m[0][0] == other._m[0][0] && _m[0][1] == other._m[0][1] && _m[0][2] == other._m[0][2] &&
               _m[1][0] == other._m[1][0] && _m[1][1] == other._m[1][1] && _m[1][2] == other._m[1][2] &&
               _m[2][0] == other._m[2][0] && _m[2][1] == other._m[2][1] && _m[2][2] == other._m[2][2];
    }

    /**
     * @brief Inequality comparison.
     * @param other Other matrix.
     * @return true if any element differs.
     */
    [[nodiscard]] constexpr bool operator!=(const Matrix3& other) const noexcept {
        return !(*this == other);
    }

    /**
     * @brief Addition assignment operator.
     * @param other Other matrix.
     * @return Reference to this matrix.
     */
    Matrix3& operator+=(const Matrix3& other) noexcept;

    /**
     * @brief Subtraction assignment operator.
     * @param other Other matrix.
     * @return Reference to this matrix.
     */
    Matrix3& operator-=(const Matrix3& other) noexcept;

    /**
     * @brief Matrix multiplication assignment operator.
     * @param other Other matrix.
     * @return Reference to this matrix.
     */
    Matrix3& operator*=(const Matrix3& other) noexcept;

    /**
     * @brief Scalar multiplication assignment operator.
     * @param scalar Scalar value.
     * @return Reference to this matrix.
     */
    Matrix3& operator*=(Real scalar) noexcept;

    /**
     * @brief Scalar division assignment operator.
     * @param scalar Scalar value.
     * @return Reference to this matrix.
     */
    Matrix3& operator/=(Real scalar) noexcept;

    /**
     * @brief Re-orthonormalizes the matrix columns using Gram-Schmidt.
     */
    void Orthonormalize() noexcept;

    /**
     * @brief Computes the exponential map of a skew-symmetric matrix.
     * @param skew Skew-symmetric matrix representing angular velocity (ω×).
     * @return Matrix exponential exp(skew).
     */
    [[nodiscard]] static Matrix3 Exp(const Matrix3& skew) noexcept;

private:
    Real _m[3][3]{};  // Row-major storage
};

} // namespace lambda::core

inline void Matrix3::Orthonormalize() noexcept {
    const auto makeSafeUnit = [](const Vector3& candidate, const Vector3& fallback) noexcept -> Vector3 {
        const auto epsilon = Real{1e-8};
        if (candidate.LengthSquared() <= epsilon) {
            return fallback;
        }
        return candidate.Normalized();
    };

    auto col0 = GetColumn(0);
    auto col1 = GetColumn(1);
    auto col2 = GetColumn(2);

    col0 = makeSafeUnit(col0, Vector3{Real{1.0}, Real{0.0}, Real{0.0}});

    const auto dot01 = col0.Dot(col1);
    col1 = Vector3{
        col1.GetX() - col0.GetX() * dot01,
        col1.GetY() - col0.GetY() * dot01,
        col1.GetZ() - col0.GetZ() * dot01
    };
    col1 = makeSafeUnit(col1, Vector3{Real{0.0}, Real{1.0}, Real{0.0}});

    col2 = col0.Cross(col1);
    col2 = makeSafeUnit(col2, Vector3{Real{0.0}, Real{0.0}, Real{1.0}});

    SetColumn(0, col0);
    SetColumn(1, col1);
    SetColumn(2, col2);
}

inline Matrix3 Matrix3::Exp(const Matrix3& skew) noexcept {
    const double wx = skew.Get(2, 1).Value();
    const double wy = skew.Get(0, 2).Value();
    const double wz = skew.Get(1, 0).Value();

    const double thetaSquared = wx * wx + wy * wy + wz * wz;
    const double theta = std::sqrt(thetaSquared);

    const Matrix3 identity = Matrix3::Identity();
    const Matrix3 skewSquared = skew * skew;

    const double eps = std::numeric_limits<double>::epsilon();
    double sinTerm = 0.0;
    double cosTerm = 0.0;

    if (thetaSquared < eps) {
        // Use series expansion for small angles
        sinTerm = 1.0 - thetaSquared / 6.0;
        cosTerm = 0.5 - thetaSquared / 24.0;
    } else {
        sinTerm = std::sin(theta) / theta;
        cosTerm = (1.0 - std::cos(theta)) / thetaSquared;
    }

    const Real sinCoeff{sinTerm};
    const Real cosCoeff{cosTerm};

    return identity + (skew * sinCoeff) + (skewSquared * cosCoeff);
}

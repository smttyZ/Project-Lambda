// Matrix4.hpp
// Project Lambda - 4x4 matrix math type
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
#include <core/Vector4.hpp>

#include <array>
#include <cstddef>

namespace lambda::core {

/**
 * @brief 4x4 matrix using Real components.
 * @details Provides matrix operations for 3D transformations with homogeneous coordinates.
 * Matrix storage is row-major order: [m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33]
 */
class Matrix4 final {
public:
    /**
     * @brief Creates a zero matrix (all elements set to zero).
     */
    constexpr Matrix4() noexcept = default;

    /**
     * @brief Creates an identity matrix.
     * @return Identity matrix with ones on the diagonal, zeros elsewhere.
     */
    [[nodiscard]] static Matrix4 Identity() noexcept {
        Matrix4 result{};
        result._m[0][0] = Real{1.0};
        result._m[1][1] = Real{1.0};
        result._m[2][2] = Real{1.0};
        result._m[3][3] = Real{1.0};
        return result;
    }

    /**
     * @brief Creates a matrix from 16 values in row-major order.
     * @param m00 Element at row 0, column 0.
     * @param m01 Element at row 0, column 1.
     * @param m02 Element at row 0, column 2.
     * @param m03 Element at row 0, column 3.
     * @param m10 Element at row 1, column 0.
     * @param m11 Element at row 1, column 1.
     * @param m12 Element at row 1, column 2.
     * @param m13 Element at row 1, column 3.
     * @param m20 Element at row 2, column 0.
     * @param m21 Element at row 2, column 1.
     * @param m22 Element at row 2, column 2.
     * @param m23 Element at row 2, column 3.
     * @param m30 Element at row 3, column 0.
     * @param m31 Element at row 3, column 1.
     * @param m32 Element at row 3, column 2.
     * @param m33 Element at row 3, column 3.
     */
    Matrix4(Real m00, Real m01, Real m02, Real m03,
            Real m10, Real m11, Real m12, Real m13,
            Real m20, Real m21, Real m22, Real m23,
            Real m30, Real m31, Real m32, Real m33) noexcept
        : _m{{m00, m01, m02, m03},
             {m10, m11, m12, m13},
             {m20, m21, m22, m23},
             {m30, m31, m32, m33}} {
    }

    /**
     * @brief Creates a matrix from a 4x4 array (row-major order).
     * @param values Array of 16 values in row-major order.
     */
    explicit Matrix4(const std::array<Real, 16>& values) noexcept
        : _m{{values[0], values[1], values[2], values[3]},
             {values[4], values[5], values[6], values[7]},
             {values[8], values[9], values[10], values[11]},
             {values[12], values[13], values[14], values[15]}} {
    }

    /**
     * @brief Creates a matrix from a 2D array (row-major order).
     * @param values 4x4 array of Real values.
     */
    explicit Matrix4(const Real values[4][4]) noexcept
        : _m{{values[0][0], values[0][1], values[0][2], values[0][3]},
             {values[1][0], values[1][1], values[1][2], values[1][3]},
             {values[2][0], values[2][1], values[2][2], values[2][3]},
             {values[3][0], values[3][1], values[3][2], values[3][3]}} {
    }

    /**
     * @brief Copy constructor.
     * @param other Matrix to copy from.
     */
    constexpr Matrix4(const Matrix4& other) noexcept = default;

    /**
     * @brief Move constructor.
     * @param other Matrix to move from.
     */
    constexpr Matrix4(Matrix4&& other) noexcept = default;

    /**
     * @brief Copy assignment operator.
     * @param other Matrix to copy from.
     * @return Reference to this matrix.
     */
    Matrix4& operator=(const Matrix4& other) noexcept = default;

    /**
     * @brief Move assignment operator.
     * @param other Matrix to move from.
     * @return Reference to this matrix.
     */
    Matrix4& operator=(Matrix4&& other) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~Matrix4() noexcept = default;

    /**
     * @brief Accesses an element by row and column indices.
     * @param row Row index (0-3).
     * @param col Column index (0-3).
     * @return Reference to the element at the specified position.
     */
    [[nodiscard]] Real& At(std::size_t row, std::size_t col) noexcept {
        return _m[row][col];
    }

    /**
     * @brief Accesses an element by row and column indices (const).
     * @param row Row index (0-3).
     * @param col Column index (0-3).
     * @return Const reference to the element at the specified position.
     */
    [[nodiscard]] const Real& At(std::size_t row, std::size_t col) const noexcept {
        return _m[row][col];
    }

    /**
     * @brief Gets an element by row and column indices.
     * @param row Row index (0-3).
     * @param col Column index (0-3).
     * @return Element value at the specified position.
     */
    [[nodiscard]] constexpr Real Get(std::size_t row, std::size_t col) const noexcept {
        return _m[row][col];
    }

    /**
     * @brief Sets an element by row and column indices.
     * @param row Row index (0-3).
     * @param col Column index (0-3).
     * @param value New element value.
     */
    void Set(std::size_t row, std::size_t col, Real value) noexcept {
        _m[row][col] = value;
    }

    /**
     * @brief Gets a row as a Vector4.
     * @param row Row index (0-3).
     * @return Vector4 containing the row elements.
     */
    [[nodiscard]] Vector4 GetRow(std::size_t row) const noexcept;

    /**
     * @brief Gets a column as a Vector4.
     * @param col Column index (0-3).
     * @return Vector4 containing the column elements.
     */
    [[nodiscard]] Vector4 GetColumn(std::size_t col) const noexcept;

    /**
     * @brief Sets a row from a Vector4.
     * @param row Row index (0-3).
     * @param values Vector4 containing the new row elements.
     */
    void SetRow(std::size_t row, const Vector4& values) noexcept;

    /**
     * @brief Sets a column from a Vector4.
     * @param col Column index (0-3).
     * @param values Vector4 containing the new column elements.
     */
    void SetColumn(std::size_t col, const Vector4& values) noexcept;

    /**
     * @brief Computes the transpose of this matrix.
     * @return Transposed matrix.
     */
    [[nodiscard]] Matrix4 Transposed() const noexcept;

    /**
     * @brief Computes the determinant of this matrix.
     * @return Determinant value.
     */
    [[nodiscard]] Real Determinant() const noexcept;

    /**
     * @brief Computes the inverse of this matrix.
     * @return Inverse matrix.
     */
    [[nodiscard]] Matrix4 Inverted() const noexcept;

    /**
     * @brief Unary plus operator.
     * @return Copy of this matrix.
     */
    [[nodiscard]] constexpr Matrix4 operator+() const noexcept {
        return *this;
    }

    /**
     * @brief Unary minus operator.
     * @return Negated matrix.
     */
    [[nodiscard]] Matrix4 operator-() const noexcept;

    /**
     * @brief Matrix addition.
     * @param other Other matrix.
     * @return Sum of the two matrices.
     */
    [[nodiscard]] Matrix4 operator+(const Matrix4& other) const noexcept;

    /**
     * @brief Matrix subtraction.
     * @param other Other matrix.
     * @return Difference of the two matrices.
     */
    [[nodiscard]] Matrix4 operator-(const Matrix4& other) const noexcept;

    /**
     * @brief Matrix multiplication.
     * @param other Other matrix.
     * @return Product of the two matrices.
     */
    [[nodiscard]] Matrix4 operator*(const Matrix4& other) const noexcept;

    /**
     * @brief Matrix-vector multiplication.
     * @param vec Vector to multiply.
     * @return Transformed vector.
     */
    [[nodiscard]] Vector4 operator*(const Vector4& vec) const noexcept;

    /**
     * @brief Scalar multiplication.
     * @param scalar Scalar value.
     * @return Matrix scaled by @p scalar.
     */
    [[nodiscard]] Matrix4 operator*(Real scalar) const noexcept;

    /**
     * @brief Scalar division.
     * @param scalar Scalar value.
     * @return Matrix divided by @p scalar.
     */
    [[nodiscard]] Matrix4 operator/(Real scalar) const noexcept;

    /**
     * @brief Equality comparison.
     * @param other Other matrix.
     * @return true if all elements are equal.
     */
    [[nodiscard]] constexpr bool operator==(const Matrix4& other) const noexcept {
        return _m[0][0] == other._m[0][0] && _m[0][1] == other._m[0][1] && _m[0][2] == other._m[0][2] && _m[0][3] == other._m[0][3] &&
               _m[1][0] == other._m[1][0] && _m[1][1] == other._m[1][1] && _m[1][2] == other._m[1][2] && _m[1][3] == other._m[1][3] &&
               _m[2][0] == other._m[2][0] && _m[2][1] == other._m[2][1] && _m[2][2] == other._m[2][2] && _m[2][3] == other._m[2][3] &&
               _m[3][0] == other._m[3][0] && _m[3][1] == other._m[3][1] && _m[3][2] == other._m[3][2] && _m[3][3] == other._m[3][3];
    }

    /**
     * @brief Inequality comparison.
     * @param other Other matrix.
     * @return true if any element differs.
     */
    [[nodiscard]] constexpr bool operator!=(const Matrix4& other) const noexcept {
        return !(*this == other);
    }

    /**
     * @brief Addition assignment operator.
     * @param other Other matrix.
     * @return Reference to this matrix.
     */
    Matrix4& operator+=(const Matrix4& other) noexcept;

    /**
     * @brief Subtraction assignment operator.
     * @param other Other matrix.
     * @return Reference to this matrix.
     */
    Matrix4& operator-=(const Matrix4& other) noexcept;

    /**
     * @brief Matrix multiplication assignment operator.
     * @param other Other matrix.
     * @return Reference to this matrix.
     */
    Matrix4& operator*=(const Matrix4& other) noexcept;

    /**
     * @brief Scalar multiplication assignment operator.
     * @param scalar Scalar value.
     * @return Reference to this matrix.
     */
    Matrix4& operator*=(Real scalar) noexcept;

    /**
     * @brief Scalar division assignment operator.
     * @param scalar Scalar value.
     * @return Reference to this matrix.
     */
    Matrix4& operator/=(Real scalar) noexcept;

private:
    Real _m[4][4]{};  // Row-major storage
};

} // namespace lambda::core


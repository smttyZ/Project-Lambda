// Vector4.hpp
// Project Lambda - 4D vector math type
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

#include <cstddef>

namespace lambda::core {

/**
 * @brief Four-dimensional vector using Real components.
 * @details Provides common vector operations including arithmetic, normalization,
 * dot product, and angle calculations. Useful for homogeneous coordinates and
 * quaternion-like operations.
 */
class Vector4 final {
public:
    /**
     * @brief Creates a new vector with all components set to zero.
     */
    constexpr Vector4() noexcept = default;

    /**
     * @brief Creates a new vector with the given components.
     * @param x X component.
     * @param y Y component.
     * @param z Z component.
     * @param w W component.
     */
    explicit constexpr Vector4(Real x, Real y, Real z, Real w) noexcept : _x(x), _y(y), _z(z), _w(w) {
    }

    /**
     * @brief Copy constructor.
     * @param other Vector to copy from.
     */
    constexpr Vector4(const Vector4& other) noexcept = default;

    /**
     * @brief Move constructor.
     * @param other Vector to move from.
     */
    constexpr Vector4(Vector4&& other) noexcept = default;

    /**
     * @brief Copy assignment operator.
     * @param other Vector to copy from.
     * @return Reference to this vector.
     */
    Vector4& operator=(const Vector4& other) noexcept = default;

    /**
     * @brief Move assignment operator.
     * @param other Vector to move from.
     * @return Reference to this vector.
     */
    Vector4& operator=(Vector4&& other) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~Vector4() noexcept = default;

    /**
     * @brief Accesses a component by index.
     * @param index Component index (0=x, 1=y, 2=z, 3=w).
     * @return Reference to the component at @p index.
     */
    [[nodiscard]] Real& operator[](std::size_t index) noexcept {
        return (&_x)[index];
    }

    /**
     * @brief Accesses a component by index (const).
     * @param index Component index (0=x, 1=y, 2=z, 3=w).
     * @return Const reference to the component at @p index.
     */
    [[nodiscard]] const Real& operator[](std::size_t index) const noexcept {
        return (&_x)[index];
    }

    /**
     * @brief Computes the Euclidean length of this vector.
     * @return Length of the vector.
     */
    [[nodiscard]] Real Length() const noexcept;

    /**
     * @brief Computes the squared length of this vector.
     * @return Squared length of the vector (avoids square root).
     */
    [[nodiscard]] Real LengthSquared() const noexcept;

    /**
     * @brief Returns a normalized copy of this vector.
     * @return Unit vector in the same direction.
     */
    [[nodiscard]] Vector4 Normalized() const noexcept;

    /**
     * @brief Computes the dot product with another vector.
     * @param other Other vector.
     * @return Dot product result.
     */
    [[nodiscard]] Real Dot(const Vector4& other) const noexcept;

    /**
     * @brief Computes the angle between this vector and another.
     * @param other Other vector.
     * @return Angle in radians.
     */
    [[nodiscard]] Real AngleBetween(const Vector4& other) const noexcept;

    /**
     * @brief Gets the X component.
     * @return X component value.
     */
    [[nodiscard]] constexpr Real GetX() const noexcept {
        return _x;
    }

    /**
     * @brief Gets the Y component.
     * @return Y component value.
     */
    [[nodiscard]] constexpr Real GetY() const noexcept {
        return _y;
    }

    /**
     * @brief Gets the Z component.
     * @return Z component value.
     */
    [[nodiscard]] constexpr Real GetZ() const noexcept {
        return _z;
    }

    /**
     * @brief Gets the W component.
     * @return W component value.
     */
    [[nodiscard]] constexpr Real GetW() const noexcept {
        return _w;
    }

    /**
     * @brief Sets the X component.
     * @param x New X component value.
     */
    void SetX(Real x) noexcept {
        _x = x;
    }

    /**
     * @brief Sets the Y component.
     * @param y New Y component value.
     */
    void SetY(Real y) noexcept {
        _y = y;
    }

    /**
     * @brief Sets the Z component.
     * @param z New Z component value.
     */
    void SetZ(Real z) noexcept {
        _z = z;
    }

    /**
     * @brief Sets the W component.
     * @param w New W component value.
     */
    void SetW(Real w) noexcept {
        _w = w;
    }

    /**
     * @brief Unary plus operator.
     * @return Copy of this vector.
     */
    [[nodiscard]] constexpr Vector4 operator+() const noexcept {
        return *this;
    }

    /**
     * @brief Unary minus operator.
     * @return Negated vector.
     */
    [[nodiscard]] Vector4 operator-() const noexcept;

    /**
     * @brief Vector addition.
     * @param other Other vector.
     * @return Sum of the two vectors.
     */
    [[nodiscard]] Vector4 operator+(const Vector4& other) const noexcept;

    /**
     * @brief Vector subtraction.
     * @param other Other vector.
     * @return Difference of the two vectors.
     */
    [[nodiscard]] Vector4 operator-(const Vector4& other) const noexcept;

    /**
     * @brief Component-wise multiplication.
     * @param other Other vector.
     * @return Component-wise product.
     */
    [[nodiscard]] Vector4 operator*(const Vector4& other) const noexcept;

    /**
     * @brief Component-wise division.
     * @param other Other vector.
     * @return Component-wise quotient.
     */
    [[nodiscard]] Vector4 operator/(const Vector4& other) const noexcept;

    /**
     * @brief Equality comparison.
     * @param other Other vector.
     * @return true if all components are equal.
     */
    [[nodiscard]] constexpr bool operator==(const Vector4& other) const noexcept {
        return _x == other._x && _y == other._y && _z == other._z && _w == other._w;
    }

    /**
     * @brief Inequality comparison.
     * @param other Other vector.
     * @return true if any component differs.
     */
    [[nodiscard]] constexpr bool operator!=(const Vector4& other) const noexcept {
        return !(*this == other);
    }

    /**
     * @brief Less-than comparison (lexicographic).
     * @param other Other vector.
     * @return true if this vector is lexicographically less than @p other.
     */
    [[nodiscard]] constexpr bool operator<(const Vector4& other) const noexcept {
        if (_x != other._x) {
            return _x < other._x;
        }
        if (_y != other._y) {
            return _y < other._y;
        }
        if (_z != other._z) {
            return _z < other._z;
        }
        return _w < other._w;
    }

    /**
     * @brief Less-than-or-equal comparison (lexicographic).
     * @param other Other vector.
     * @return true if this vector is lexicographically less than or equal to @p other.
     */
    [[nodiscard]] constexpr bool operator<=(const Vector4& other) const noexcept {
        return !(other < *this);
    }

    /**
     * @brief Greater-than comparison (lexicographic).
     * @param other Other vector.
     * @return true if this vector is lexicographically greater than @p other.
     */
    [[nodiscard]] constexpr bool operator>(const Vector4& other) const noexcept {
        return other < *this;
    }

    /**
     * @brief Greater-than-or-equal comparison (lexicographic).
     * @param other Other vector.
     * @return true if this vector is lexicographically greater than or equal to @p other.
     */
    [[nodiscard]] constexpr bool operator>=(const Vector4& other) const noexcept {
        return !(*this < other);
    }

    /**
     * @brief Addition assignment operator.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    Vector4& operator+=(const Vector4& other) noexcept;

    /**
     * @brief Subtraction assignment operator.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    Vector4& operator-=(const Vector4& other) noexcept;

    /**
     * @brief Component-wise multiplication assignment operator.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    Vector4& operator*=(const Vector4& other) noexcept;

    /**
     * @brief Component-wise division assignment operator.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    Vector4& operator/=(const Vector4& other) noexcept;

private:
    Real _x{};
    Real _y{};
    Real _z{};
    Real _w{};
};

} // namespace lambda::core


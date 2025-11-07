// Vector3.hpp
// Project Lambda - 3D vector math type
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
 * @brief Three-dimensional vector using Real components.
 * @details Provides common vector operations including arithmetic, normalization,
 * dot product, cross product, and angle calculations.
 */
class Vector3 final {
public:
    /**
     * @brief Creates a new vector with all components set to zero.
     */
    constexpr Vector3() noexcept = default;

    /**
     * @brief Creates a new vector with the given components.
     * @param x X component.
     * @param y Y component.
     * @param z Z component.
     */
    explicit constexpr Vector3(Real x, Real y, Real z) noexcept : _x(x), _y(y), _z(z) {}

    /**
     * @brief Copy constructor.
     * @param other Vector to copy from.
     */
    constexpr Vector3(const Vector3& other) noexcept = default;

    /**
     * @brief Move constructor.
     * @param other Vector to move from.
     */
    constexpr Vector3(Vector3&& other) noexcept = default;

    /**
     * @brief Copy assignment operator.
     * @param other Vector to copy from.
     * @return Reference to this vector.
     */
    Vector3& operator=(const Vector3& other) noexcept = default;

    /**
     * @brief Move assignment operator.
     * @param other Vector to move from.
     * @return Reference to this vector.
     */
    Vector3& operator=(Vector3&& other) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~Vector3() noexcept = default;

    /**
     * @brief Accesses a component by index.
     * @param index Component index (0=x, 1=y, 2=z).
     * @return Reference to the component at @p index.
     */
    [[nodiscard]] Real& operator[](std::size_t index) noexcept {
        return (&_x)[index];
    }

    /**
     * @brief Accesses a component by index (const).
     * @param index Component index (0=x, 1=y, 2=z).
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
    [[nodiscard]] Vector3 Normalized() const noexcept;

    /**
     * @brief Computes the dot product with another vector.
     * @param other Other vector.
     * @return Dot product result.
     */
    [[nodiscard]] Real Dot(const Vector3& other) const noexcept;

    /**
     * @brief Computes the cross product with another vector.
     * @param other Other vector.
     * @return Cross product result.
     */
    [[nodiscard]] Vector3 Cross(const Vector3& other) const noexcept;

    /**
     * @brief Computes the angle between this vector and another.
     * @param other Other vector.
     * @return Angle in radians.
     */
    [[nodiscard]] Real AngleBetween(const Vector3& other) const noexcept;

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
     * @brief Unary plus operator.
     * @return Copy of this vector.
     */
    [[nodiscard]] constexpr Vector3 operator+() const noexcept {
        return *this;
    }

    /**
     * @brief Unary minus operator.
     * @return Negated vector.
     */
    [[nodiscard]] Vector3 operator-() const noexcept;

    /**
     * @brief Vector addition.
     * @param other Other vector.
     * @return Sum of the two vectors.
     */
    [[nodiscard]] Vector3 operator+(const Vector3& other) const noexcept;

    /**
     * @brief Vector subtraction.
     * @param other Other vector.
     * @return Difference of the two vectors.
     */
    [[nodiscard]] Vector3 operator-(const Vector3& other) const noexcept;

    /**
     * @brief Component-wise multiplication.
     * @param other Other vector.
     * @return Component-wise product.
     */
    [[nodiscard]] Vector3 operator*(const Vector3& other) const noexcept;

    /**
     * @brief Component-wise division.
     * @param other Other vector.
     * @return Component-wise quotient.
     */
    [[nodiscard]] Vector3 operator/(const Vector3& other) const noexcept;

    /**
     * @brief Equality comparison.
     * @param other Other vector.
     * @return true if all components are equal.
     */
    [[nodiscard]] constexpr bool operator==(const Vector3& other) const noexcept {
        return _x == other._x && _y == other._y && _z == other._z;
    }

    /**
     * @brief Inequality comparison.
     * @param other Other vector.
     * @return true if any component differs.
     */
    [[nodiscard]] constexpr bool operator!=(const Vector3& other) const noexcept {
        return !(*this == other);
    }

    /**
     * @brief Less-than comparison (lexicographic).
     * @param other Other vector.
     * @return true if this vector is lexicographically less than @p other.
     */
    [[nodiscard]] constexpr bool operator<(const Vector3& other) const noexcept {
        if (_x != other._x) {
            return _x < other._x;
        }
        if (_y != other._y) {
            return _y < other._y;
        }
        return _z < other._z;
    }

    /**
     * @brief Less-than-or-equal comparison (lexicographic).
     * @param other Other vector.
     * @return true if this vector is lexicographically less than or equal to @p other.
     */
    [[nodiscard]] constexpr bool operator<=(const Vector3& other) const noexcept {
        return !(other < *this);
    }

    /**
     * @brief Greater-than comparison (lexicographic).
     * @param other Other vector.
     * @return true if this vector is lexicographically greater than @p other.
     */
    [[nodiscard]] constexpr bool operator>(const Vector3& other) const noexcept {
        return other < *this;
    }

    /**
     * @brief Greater-than-or-equal comparison (lexicographic).
     * @param other Other vector.
     * @return true if this vector is lexicographically greater than or equal to @p other.
     */
    [[nodiscard]] constexpr bool operator>=(const Vector3& other) const noexcept {
        return !(*this < other);
    }

    /**
     * @brief Addition assignment operator.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    Vector3& operator+=(const Vector3& other) noexcept;

    /**
     * @brief Subtraction assignment operator.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    Vector3& operator-=(const Vector3& other) noexcept;

    /**
     * @brief Component-wise multiplication assignment operator.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    Vector3& operator*=(const Vector3& other) noexcept;

    /**
     * @brief Component-wise division assignment operator.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    Vector3& operator/=(const Vector3& other) noexcept;

private:
    Real _x{};
    Real _y{};
    Real _z{};
};

} // namespace lambda::core

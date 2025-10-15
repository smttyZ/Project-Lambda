#pragma once

#include <cmath>

#include "Numbers.hpp"

namespace lambda::math {

    /**
     * @brief 2D vector storing two @c Real components.
     */
    struct Vector2 {
        Real x{};
        Real y{};

        /// Constructs a zero vector.
        constexpr Vector2() = default;
        /// Constructs a vector initialized with the provided components.
        constexpr Vector2(Real ix, Real iy) : x(ix), y(iy) {}

        /// Adds two vectors component-wise.
        [[nodiscard]] constexpr Vector2 operator+(Vector2 rhs) const {
            return { x + rhs.x, y + rhs.y };
        }
        /// Subtracts two vectors component-wise.
        [[nodiscard]] constexpr Vector2 operator-(Vector2 rhs) const {
            return { x - rhs.x, y - rhs.y };
        }
        /// Negates this vector.
        [[nodiscard]] constexpr Vector2 operator-() const { return { -x, -y }; }

        /// Multiplies each component by a scalar.
        [[nodiscard]] constexpr Vector2 operator*(Real scalar) const {
            return { x * scalar, y * scalar };
        }
        /// Divides each component by a scalar.
        [[nodiscard]] constexpr Vector2 operator/(Real scalar) const {
            return { x / scalar, y / scalar };
        }

        /// Adds the rhs vector to this one.
        constexpr Vector2& operator+=(Vector2 rhs) {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }
        /// Subtracts the rhs vector from this one.
        constexpr Vector2& operator-=(Vector2 rhs) {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }
        /// Scales this vector by a scalar factor.
        constexpr Vector2& operator*=(Real scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }
        /// Divides this vector by a scalar factor.
        constexpr Vector2& operator/=(Real scalar) {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        /// Equality comparison between two vectors.
        [[nodiscard]] constexpr bool operator==(Vector2 rhs) const {
            return x == rhs.x && y == rhs.y;
        }
        /// Inequality comparison between two vectors.
        [[nodiscard]] constexpr bool operator!=(Vector2 rhs) const { return !(*this == rhs); }

        /// Computes the dot product with @p rhs.
        [[nodiscard]] constexpr Real Dot(Vector2 rhs) const {
            return (x * rhs.x) + (y * rhs.y);
        }
        /// Returns the squared length (magnitude) of the vector.
        [[nodiscard]] constexpr Real LengthSquared() const { return Dot(*this); }
        /// Returns the length (magnitude) of the vector.
        [[nodiscard]] Real Length() const {
            return Real{ std::sqrt(static_cast<double>(LengthSquared())) };
        }
        /// Produces a normalized copy of this vector.
        [[nodiscard]] Vector2 Normalized() const {
            const Real len = Length();
            if (len == Real{}) {
                return *this;
            }
            return *this / len;
        }
        /// Normalizes this vector in place.
        void Normalize() {
            const Real len = Length();
            if (len != Real{}) {
                *this /= len;
            }
        }
    };

    /// Scalar multiplication with the scalar on the left.
    [[nodiscard]] constexpr Vector2 operator*(Real scalar, Vector2 vector) {
        return vector * scalar;
    }

    /**
     * @brief 3D vector storing three @c Real components.
     */
    struct Vector3 {
        Real x{};
        Real y{};
        Real z{};

        /// Constructs a zero vector.
        constexpr Vector3() = default;
        /// Constructs a vector initialized with the provided components.
        constexpr Vector3(Real ix, Real iy, Real iz) : x(ix), y(iy), z(iz) {}

        /// Adds two vectors component-wise.
        [[nodiscard]] constexpr Vector3 operator+(Vector3 rhs) const {
            return { x + rhs.x, y + rhs.y, z + rhs.z };
        }
        /// Subtracts two vectors component-wise.
        [[nodiscard]] constexpr Vector3 operator-(Vector3 rhs) const {
            return { x - rhs.x, y - rhs.y, z - rhs.z };
        }
        /// Negates this vector.
        [[nodiscard]] constexpr Vector3 operator-() const { return { -x, -y, -z }; }

        /// Multiplies each component by a scalar.
        [[nodiscard]] constexpr Vector3 operator*(Real scalar) const {
            return { x * scalar, y * scalar, z * scalar };
        }
        /// Divides each component by a scalar.
        [[nodiscard]] constexpr Vector3 operator/(Real scalar) const {
            return { x / scalar, y / scalar, z / scalar };
        }

        /// Adds the rhs vector to this one.
        constexpr Vector3& operator+=(Vector3 rhs) {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }
        /// Subtracts the rhs vector from this one.
        constexpr Vector3& operator-=(Vector3 rhs) {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }
        /// Scales this vector by a scalar factor.
        constexpr Vector3& operator*=(Real scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }
        /// Divides this vector by a scalar factor.
        constexpr Vector3& operator/=(Real scalar) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        /// Equality comparison between two vectors.
        [[nodiscard]] constexpr bool operator==(Vector3 rhs) const {
            return x == rhs.x && y == rhs.y && z == rhs.z;
        }
        /// Inequality comparison between two vectors.
        [[nodiscard]] constexpr bool operator!=(Vector3 rhs) const { return !(*this == rhs); }

        /// Computes the dot product with @p rhs.
        [[nodiscard]] constexpr Real Dot(Vector3 rhs) const {
            return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
        }
        /// Computes the cross product with @p rhs.
        [[nodiscard]] constexpr Vector3 Cross(Vector3 rhs) const {
            return {
                (y * rhs.z) - (z * rhs.y),
                (z * rhs.x) - (x * rhs.z),
                (x * rhs.y) - (y * rhs.x)
            };
        }
        /// Returns the squared length (magnitude) of the vector.
        [[nodiscard]] constexpr Real LengthSquared() const { return Dot(*this); }
        /// Returns the length (magnitude) of the vector.
        [[nodiscard]] Real Length() const {
            return Real{ std::sqrt(static_cast<double>(LengthSquared())) };
        }
        /// Produces a normalized copy of this vector.
        [[nodiscard]] Vector3 Normalized() const {
            const Real len = Length();
            if (len == Real{}) {
                return *this;
            }
            return *this / len;
        }
        /// Normalizes this vector in place.
        void Normalize() {
            const Real len = Length();
            if (len != Real{}) {
                *this /= len;
            }
        }
    };

    /// Scalar multiplication with the scalar on the left.
    [[nodiscard]] constexpr Vector3 operator*(Real scalar, Vector3 vector) {
        return vector * scalar;
    }

    /**
     * @brief 4D vector storing four @c Real components.
     */
    struct Vector4 {
        Real x{};
        Real y{};
        Real z{};
        Real w{};

        /// Constructs a zero vector.
        constexpr Vector4() = default;
        /// Constructs a vector initialized with the provided components.
        constexpr Vector4(Real ix, Real iy, Real iz, Real iw) : x(ix), y(iy), z(iz), w(iw) {}

        /// Adds two vectors component-wise.
        [[nodiscard]] constexpr Vector4 operator+(Vector4 rhs) const {
            return { x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w };
        }
        /// Subtracts two vectors component-wise.
        [[nodiscard]] constexpr Vector4 operator-(Vector4 rhs) const {
            return { x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w };
        }
        /// Negates this vector.
        [[nodiscard]] constexpr Vector4 operator-() const { return { -x, -y, -z, -w }; }

        /// Multiplies each component by a scalar.
        [[nodiscard]] constexpr Vector4 operator*(Real scalar) const {
            return { x * scalar, y * scalar, z * scalar, w * scalar };
        }
        /// Divides each component by a scalar.
        [[nodiscard]] constexpr Vector4 operator/(Real scalar) const {
            return { x / scalar, y / scalar, z / scalar, w / scalar };
        }

        /// Adds the rhs vector to this one.
        constexpr Vector4& operator+=(Vector4 rhs) {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            w += rhs.w;
            return *this;
        }
        /// Subtracts the rhs vector from this one.
        constexpr Vector4& operator-=(Vector4 rhs) {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            w -= rhs.w;
            return *this;
        }
        /// Scales this vector by a scalar factor.
        constexpr Vector4& operator*=(Real scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            w *= scalar;
            return *this;
        }
        /// Divides this vector by a scalar factor.
        constexpr Vector4& operator/=(Real scalar) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;
            return *this;
        }

        /// Equality comparison between two vectors.
        [[nodiscard]] constexpr bool operator==(Vector4 rhs) const {
            return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
        }
        /// Inequality comparison between two vectors.
        [[nodiscard]] constexpr bool operator!=(Vector4 rhs) const { return !(*this == rhs); }

        /// Computes the dot product with @p rhs.
        [[nodiscard]] constexpr Real Dot(Vector4 rhs) const {
            return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w);
        }
        /// Returns the squared length (magnitude) of the vector.
        [[nodiscard]] constexpr Real LengthSquared() const { return Dot(*this); }
        /// Returns the length (magnitude) of the vector.
        [[nodiscard]] Real Length() const {
            return Real{ std::sqrt(static_cast<double>(LengthSquared())) };
        }
        /// Produces a normalized copy of this vector.
        [[nodiscard]] Vector4 Normalized() const {
            const Real len = Length();
            if (len == Real{}) {
                return *this;
            }
            return *this / len;
        }
        /// Normalizes this vector in place.
        void Normalize() {
            const Real len = Length();
            if (len != Real{}) {
                *this /= len;
            }
        }
    };

    /// Scalar multiplication with the scalar on the left.
    [[nodiscard]] constexpr Vector4 operator*(Real scalar, Vector4 vector) {
        return vector * scalar;
    }

} // namespace lambda::math

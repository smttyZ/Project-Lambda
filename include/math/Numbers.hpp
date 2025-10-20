// Numbers.hpp
// Project Lambda - Numeric type helpers
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

#include <cstdint>
#include <numeric>
#include <stdexcept>

namespace lambda::math {

    /**
     * @brief Represents a real number backed by double precision.
     */
    struct Real {
        double value{};

        /// Constructs a real number from a double value.
        constexpr Real(double v = 0.0) : value(v) {}

        /// Adds two real numbers.
        constexpr Real operator+(Real rhs) const { return Real{value + rhs.value}; }
        /// Subtracts two real numbers.
        constexpr Real operator-(Real rhs) const { return Real{value - rhs.value}; }
        /// Multiplies two real numbers.
        constexpr Real operator*(Real rhs) const { return Real{value * rhs.value}; }
        /// Divides two real numbers.
        constexpr Real operator/(Real rhs) const { return Real{value / rhs.value}; }
        /// Unary plus returns the same real number.
        constexpr Real operator+() const { return *this; }
        /// Unary minus negates the real number.
        constexpr Real operator-() const { return Real{-value}; }

        /// Adds the rhs value to this real number.
        constexpr Real& operator+=(Real rhs) { value += rhs.value; return *this; }
        /// Subtracts the rhs value from this real number.
        constexpr Real& operator-=(Real rhs) { value -= rhs.value; return *this; }
        /// Multiplies this real number by rhs.
        constexpr Real& operator*=(Real rhs) { value *= rhs.value; return *this; }
        /// Divides this real number by rhs.
        constexpr Real& operator/=(Real rhs) { value /= rhs.value; return *this; }

        /// Equality comparison between two real numbers.
        [[nodiscard]] constexpr bool operator==(Real rhs) const { return value == rhs.value; }
        /// Inequality comparison between two real numbers.
        [[nodiscard]] constexpr bool operator!=(Real rhs) const { return !(*this == rhs); }
        /// Less-than comparison.
        [[nodiscard]] constexpr bool operator<(Real rhs) const { return value < rhs.value; }
        /// Less-than or equal comparison.
        [[nodiscard]] constexpr bool operator<=(Real rhs) const { return value <= rhs.value; }
        /// Greater-than comparison.
        [[nodiscard]] constexpr bool operator>(Real rhs) const { return value > rhs.value; }
        /// Greater-than or equal comparison.
        [[nodiscard]] constexpr bool operator>=(Real rhs) const { return value >= rhs.value; }

        /// Converts the real number to a double.
        constexpr explicit operator double() const { return value; }
    };

    /**
     * @brief Represents an integer with 64-bit signed precision.
     */
    struct Integer {
        std::int64_t value{};

        /// Constructs an integer from a signed 64-bit value.
        constexpr Integer(std::int64_t v = 0) : value(v) {}

        /// Adds two integers.
        constexpr Integer operator+(Integer rhs) const { return Integer{value + rhs.value}; }
        /// Subtracts rhs from this integer.
        constexpr Integer operator-(Integer rhs) const { return Integer{value - rhs.value}; }
        /// Multiplies two integers.
        constexpr Integer operator*(Integer rhs) const { return Integer{value * rhs.value}; }
        /// Divides this integer by rhs.
        constexpr Integer operator/(Integer rhs) const { return Integer{value / rhs.value}; }
        /// Computes the remainder of division.
        constexpr Integer operator%(Integer rhs) const { return Integer{value % rhs.value}; }
        /// Unary plus returns the same integer.
        constexpr Integer operator+() const { return *this; }
        /// Unary minus negates the integer.
        constexpr Integer operator-() const { return Integer{-value}; }

        /// Adds rhs to this integer.
        constexpr Integer& operator+=(Integer rhs) { value += rhs.value; return *this; }
        /// Subtracts rhs from this integer.
        constexpr Integer& operator-=(Integer rhs) { value -= rhs.value; return *this; }
        /// Multiplies this integer by rhs.
        constexpr Integer& operator*=(Integer rhs) { value *= rhs.value; return *this; }
        /// Divides this integer by rhs.
        constexpr Integer& operator/=(Integer rhs) { value /= rhs.value; return *this; }
        /// Computes the modulus of this integer with rhs.
        constexpr Integer& operator%=(Integer rhs) { value %= rhs.value; return *this; }

        /// Equality comparison between integers.
        [[nodiscard]] constexpr bool operator==(Integer rhs) const { return value == rhs.value; }
        /// Inequality comparison between integers.
        [[nodiscard]] constexpr bool operator!=(Integer rhs) const { return !(*this == rhs); }
        /// Less-than comparison.
        [[nodiscard]] constexpr bool operator<(Integer rhs) const { return value < rhs.value; }
        /// Less-than or equal comparison.
        [[nodiscard]] constexpr bool operator<=(Integer rhs) const { return value <= rhs.value; }
        /// Greater-than comparison.
        [[nodiscard]] constexpr bool operator>(Integer rhs) const { return value > rhs.value; }
        /// Greater-than or equal comparison.
        [[nodiscard]] constexpr bool operator>=(Integer rhs) const { return value >= rhs.value; }

        /// Converts the integer to a Real type.
        constexpr explicit operator Real() const { return Real{static_cast<double>(value)}; }
    };

    /**
     * @brief Represents a rational number as a numerator and denominator.
     */
    struct Rational {
        Integer numerator{};
        Integer denominator{1};

        /// Constructs a rational number with zero numerator and denominator of one.
        constexpr Rational() = default;
        /// Constructs a rational number from numerator and denominator.
        constexpr Rational(Integer num, Integer denom) : numerator(num), denominator(denom) {
            if (denominator.value == 0) {
                throw std::runtime_error("Rational denominator cannot be zero");
            }
            normalize();
        }
        /// Constructs a rational number from an integer.
        constexpr explicit Rational(Integer num) : numerator(num), denominator(1) {}

        /// Adds two rational numbers.
        constexpr Rational operator+(Rational rhs) const {
            return Rational{ numerator * rhs.denominator + rhs.numerator * denominator,
                             denominator * rhs.denominator };
        }
        /// Subtracts rhs from this rational number.
        constexpr Rational operator-(Rational rhs) const {
            return Rational{ numerator * rhs.denominator - rhs.numerator * denominator,
                             denominator * rhs.denominator };
        }
        /// Multiplies two rational numbers.
        constexpr Rational operator*(Rational rhs) const {
            return Rational{ numerator * rhs.numerator, denominator * rhs.denominator };
        }
        /// Divides this rational number by rhs.
        constexpr Rational operator/(Rational rhs) const {
            if (rhs.numerator.value == 0) {
                throw std::runtime_error("Cannot divide by zero rational");
            }
            return Rational{ numerator * rhs.denominator, denominator * rhs.numerator };
        }

        /// Adds rhs to this rational number.
        constexpr Rational& operator+=(Rational rhs) { return *this = *this + rhs; }
        /// Subtracts rhs from this rational number.
        constexpr Rational& operator-=(Rational rhs) { return *this = *this - rhs; }
        /// Multiplies this rational number by rhs.
        constexpr Rational& operator*=(Rational rhs) { return *this = *this * rhs; }
        /// Divides this rational number by rhs.
        constexpr Rational& operator/=(Rational rhs) { return *this = *this / rhs; }

        /// Equality comparison between two rational numbers.
        [[nodiscard]] constexpr bool operator==(Rational rhs) const {
            return numerator == rhs.numerator && denominator == rhs.denominator;
        }
        /// Inequality comparison between two rational numbers.
        [[nodiscard]] constexpr bool operator!=(Rational rhs) const { return !(*this == rhs); }
        /// Less-than comparison between two rational numbers.
        [[nodiscard]] constexpr bool operator<(Rational rhs) const {
            return (numerator * rhs.denominator).value < (rhs.numerator * denominator).value;
        }
        /// Less-than or equal comparison between two rational numbers.
        [[nodiscard]] constexpr bool operator<=(Rational rhs) const { return !(*this > rhs); }
        /// Greater-than comparison between two rational numbers.
        [[nodiscard]] constexpr bool operator>(Rational rhs) const {
            return (numerator * rhs.denominator).value > (rhs.numerator * denominator).value;
        }
        /// Greater-than or equal comparison between two rational numbers.
        [[nodiscard]] constexpr bool operator>=(Rational rhs) const { return !(*this < rhs); }

        /// Converts the rational number to a Real.
        constexpr explicit operator Real() const {
            return Real(static_cast<double>(numerator.value) /
                        static_cast<double>(denominator.value));
        }

    private:
        /// Ensures the rational number is in normalized form.
        constexpr void normalize() {
            if (denominator.value < 0) {
                numerator.value = -numerator.value;
                denominator.value = -denominator.value;
            }
            const auto common = std::gcd(numerator.value, denominator.value);
            if (common != 0) {
                numerator.value /= common;
                denominator.value /= common;
            }
        }
    };

    /**
     * @brief Represents a complex number with real and imaginary parts.
     */
    struct Complex {
        Real real{};
        Real imaginary{};

        /// Constructs a complex number from real and imaginary components.
        constexpr Complex(Real r = {}, Real i = {}) : real(r), imaginary(i) {}

        /// Adds two complex numbers.
        constexpr Complex operator+(Complex rhs) const {
            return { real + rhs.real, imaginary + rhs.imaginary };
        }
        /// Subtracts rhs from this complex number.
        constexpr Complex operator-(Complex rhs) const {
            return { real - rhs.real, imaginary - rhs.imaginary };
        }
        /// Multiplies two complex numbers.
        constexpr Complex operator*(Complex rhs) const {
            return { (real * rhs.real) - (imaginary * rhs.imaginary),
                     (real * rhs.imaginary) + (imaginary * rhs.real) };
        }
        /// Divides this complex number by rhs.
        constexpr Complex operator/(Complex rhs) const {
            const Real denom = (rhs.real * rhs.real) + (rhs.imaginary * rhs.imaginary);
            if (denom == Real{}) {
                throw std::runtime_error("Cannot divide by zero complex number");
            }
            return { ((real * rhs.real) + (imaginary * rhs.imaginary)) / denom,
                     ((imaginary * rhs.real) - (real * rhs.imaginary)) / denom };
        }

        /// Adds rhs to this complex number.
        constexpr Complex& operator+=(Complex rhs) { real += rhs.real; imaginary += rhs.imaginary; return *this; }
        /// Subtracts rhs from this complex number.
        constexpr Complex& operator-=(Complex rhs) { real -= rhs.real; imaginary -= rhs.imaginary; return *this; }
        /// Multiplies this complex number by rhs.
        constexpr Complex& operator*=(Complex rhs) { return *this = *this * rhs; }
        /// Divides this complex number by rhs.
        constexpr Complex& operator/=(Complex rhs) { return *this = *this / rhs; }

        /// Equality comparison between two complex numbers.
        [[nodiscard]] constexpr bool operator==(Complex rhs) const {
            return real == rhs.real && imaginary == rhs.imaginary;
        }
        /// Inequality comparison between two complex numbers.
        [[nodiscard]] constexpr bool operator!=(Complex rhs) const { return !(*this == rhs); }

        /// Converts the complex number to its real component.
        constexpr explicit operator Real() const { return real; }
    };

} // namespace lambda::math

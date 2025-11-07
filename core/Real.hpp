// Real.hpp
// Project Lambda - Core strict real-number type
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

#include <cmath>
#include <stdexcept>

namespace lambda::core {

/**
 * @brief Strongly-typed real number enforcing finite, valid values only.
 * @details The Real type forbids NaN and infinity by construction.
 * Any invalid input triggers a compile-time or runtime exception depending on context.
 */
class Real final {
public:
    constexpr Real() noexcept = default;

    explicit Real(double value) : _value(value) {
        if (!std::isfinite(value)) {
            throw std::invalid_argument("Real numbers must be finite (no NaN or infinity)");
        }
    }

    [[nodiscard]] constexpr double Value() const noexcept { return _value; }

    [[nodiscard]] explicit constexpr operator double() const noexcept { return _value; }

    // Unary operators
    [[nodiscard]] Real operator+() const {
        return Real{_value};
    }

    [[nodiscard]] Real operator-() const {
        return Real{-_value};
    }

    // Arithmetic operators
    [[nodiscard]] Real operator+(Real rhs) const {
        const double result = _value + rhs._value;
        if (!std::isfinite(result)) {
            throw std::invalid_argument("Real addition produced non-finite result");
        }
        return Real{result};
    }

    [[nodiscard]] Real operator-(Real rhs) const {
        const double result = _value - rhs._value;
        if (!std::isfinite(result)) {
            throw std::invalid_argument("Real subtraction produced non-finite result");
        }
        return Real{result};
    }

    [[nodiscard]] Real operator*(Real rhs) const {
        const double result = _value * rhs._value;
        if (!std::isfinite(result)) {
            throw std::invalid_argument("Real multiplication produced non-finite result");
        }
        return Real{result};
    }

    [[nodiscard]] Real operator/(Real rhs) const {
        if (rhs._value == 0.0) {
            throw std::invalid_argument("Division by zero in Real");
        }
        const double result = _value / rhs._value;
        if (!std::isfinite(result)) {
            throw std::invalid_argument("Real division produced non-finite result");
        }
        return Real{result};
    }

    // Compound assignment operators
    Real& operator+=(Real rhs) {
        *this = *this + rhs;
        return *this;
    }

    Real& operator-=(Real rhs) {
        *this = *this - rhs;
        return *this;
    }

    Real& operator*=(Real rhs) {
        *this = *this * rhs;
        return *this;
    }

    Real& operator/=(Real rhs) {
        *this = *this / rhs;
        return *this;
    }

    // Comparisons
    [[nodiscard]] constexpr bool operator==(Real rhs) const noexcept { return _value == rhs._value; }

    [[nodiscard]] constexpr bool operator!=(Real rhs) const noexcept { return !(*this == rhs); }

    [[nodiscard]] constexpr bool operator<(Real rhs) const noexcept { return _value < rhs._value; }

    [[nodiscard]] constexpr bool operator<=(Real rhs) const noexcept { return _value <= rhs._value; }

    [[nodiscard]] constexpr bool operator>(Real rhs) const noexcept { return _value > rhs._value; }

    [[nodiscard]] constexpr bool operator>=(Real rhs) const noexcept { return _value >= rhs._value; }

private:
    double _value = 0.0;  // Always finite
};

} // namespace lambda::core

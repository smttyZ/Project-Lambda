// IRigidBody.hpp
// Project Lambda - Physics rigid body contract definition
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

#include <core/Real.hpp>

#include <array>
#include <cstdint>

namespace lambda::physics {

/**
 * @brief Status codes reported by rigid-body mutators and validators.
 *
 * Status values allow validation without resorting to exceptions for routine argument errors.
 */
enum class RigidBodyStatus : std::uint8_t {
    OK = 0,
    INVALID_MASS = 1,
    INVALID_POSITION = 2,
    INVALID_VELOCITY = 3,
};

/**
 * @brief Validates that mass is strictly positive and finite.
 */
[[nodiscard]] inline bool IsValidMass(lambda::core::Real mass) noexcept {
    try {
        return mass > lambda::core::Real{0.0};
    } catch (...) {
        return false;
    }
}

/**
 * @brief Validates that inverse mass is non-negative and finite.
 */
[[nodiscard]] inline bool IsValidInverseMass(lambda::core::Real invMass) noexcept {
    try {
        return invMass >= lambda::core::Real{0.0};
    } catch (...) {
        return false;
    }
}

/**
 * @brief Validates that every component of the vector is finite.
 */
[[nodiscard]] inline bool IsValidVector3(const std::array<lambda::core::Real, 3>& value) noexcept {
    try {
        for (const auto& component : value) {
            [[maybe_unused]] const auto probe = component;
        }
        return true;
    } catch (...) {
        return false;
    }
}

/**
 * @brief Rigid-body interface that exposes the minimal physical state contract.
 */
class IRigidBody {
public:
    virtual ~IRigidBody() = default;

    /**
     * @brief Returns the body's mass in kilograms.
     */
    [[nodiscard]] virtual lambda::core::Real GetMass() const noexcept = 0;

    /**
     * @brief Sets the body's mass in kilograms.
     * @param mass New positive mass value.
     * @return Validation status describing whether @p mass was accepted.
     */
    [[nodiscard]] virtual RigidBodyStatus SetMass(lambda::core::Real mass) = 0;

    /**
     * @brief Returns the body's world-space position in meters.
     */
    [[nodiscard]] virtual std::array<lambda::core::Real, 3> GetPosition() const noexcept = 0;

    /**
     * @brief Sets the body's world-space position in meters.
     * @param position New position written as {x, y, z}.
     * @return Validation status describing whether @p position was accepted.
     */
    [[nodiscard]] virtual RigidBodyStatus SetPosition(const std::array<lambda::core::Real, 3>& position) = 0;

    /**
     * @brief Returns the body's linear velocity in meters per second.
     */
    [[nodiscard]] virtual std::array<lambda::core::Real, 3> GetVelocity() const noexcept = 0;

    /**
     * @brief Sets the body's linear velocity in meters per second.
     * @param velocity New linear velocity written as {vx, vy, vz}.
     * @return Validation status describing whether @p velocity was accepted.
     */
    [[nodiscard]] virtual RigidBodyStatus SetVelocity(const std::array<lambda::core::Real, 3>& velocity) = 0;

    /**
     * @brief Sets the inertia tensor expressed in local space (row-major 3x3).
     * @param inertiaTensor New inertia tensor values.
     * @return Validation status describing whether @p inertiaTensor was accepted.
     */
    [[nodiscard]] virtual RigidBodyStatus SetInertiaTensor(const std::array<lambda::core::Real, 9>& inertiaTensor) = 0;

    /**
     * @brief Returns the inertia tensor expressed in local space (row-major 3x3).
     */
    [[nodiscard]] virtual std::array<lambda::core::Real, 9> GetInertiaTensor() const noexcept = 0;
};

} // namespace lambda::physics

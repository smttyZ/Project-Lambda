// RigidBody.hpp
// Project Lambda - Placeholder rigid body implementation stub
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

#include <lambda/physics/IRigidBody.hpp>

#include <array>
#include <stdexcept>

namespace lambda::physics {

/**
 * @brief Basic IRigidBody implementation that defers real behavior to future work.
 *
 * Every call currently throws to highlight missing behavior while preserving the public API surface.
 */
class RigidBody final : public IRigidBody {
public:
    RigidBody() = default;
    ~RigidBody() override = default;

    /** @copydoc IRigidBody::GetMass */
    [[nodiscard]] lambda::core::Real GetMass() const noexcept override {
        throw std::runtime_error("RigidBody::GetMass not implemented");
    }

    /** @copydoc IRigidBody::SetMass */
    [[nodiscard]] RigidBodyStatus SetMass(lambda::core::Real /*mass*/) override {
        throw std::runtime_error("RigidBody::SetMass not implemented");
    }

    /** @copydoc IRigidBody::GetPosition */
    [[nodiscard]] std::array<lambda::core::Real, 3> GetPosition() const noexcept override {
        throw std::runtime_error("RigidBody::GetPosition not implemented");
    }

    /** @copydoc IRigidBody::SetPosition */
    [[nodiscard]] RigidBodyStatus SetPosition(const std::array<lambda::core::Real, 3>& /*position*/) override {
        throw std::runtime_error("RigidBody::SetPosition not implemented");
    }

    /** @copydoc IRigidBody::GetVelocity */
    [[nodiscard]] std::array<lambda::core::Real, 3> GetVelocity() const noexcept override {
        throw std::runtime_error("RigidBody::GetVelocity not implemented");
    }

    /** @copydoc IRigidBody::SetVelocity */
    [[nodiscard]] RigidBodyStatus SetVelocity(const std::array<lambda::core::Real, 3>& /*velocity*/) override {
        throw std::runtime_error("RigidBody::SetVelocity not implemented");
    }

    /** @copydoc IRigidBody::SetInertiaTensor */
    [[nodiscard]] RigidBodyStatus SetInertiaTensor(const std::array<lambda::core::Real, 9>& /*tensor*/) override {
        throw std::runtime_error("RigidBody::SetInertiaTensor not implemented");
    }

    /** @copydoc IRigidBody::GetInertiaTensor */
    [[nodiscard]] std::array<lambda::core::Real, 9> GetInertiaTensor() const noexcept override {
        throw std::runtime_error("RigidBody::GetInertiaTensor not implemented");
    }

    /**
     * @brief Returns the inverse mass (1 / mass).
     * @return Inverse mass value.
     */
    [[nodiscard]] lambda::core::Real GetInverseMass() const noexcept {
        throw std::runtime_error("RigidBody::GetInverseMass not implemented");
    }

    /**
     * @brief Returns the inverse inertia tensor in local space.
     * @return Inverse inertia tensor values.
     */
    [[nodiscard]] std::array<lambda::core::Real, 9> GetInverseInertiaTensor() const noexcept {
        throw std::runtime_error("RigidBody::GetInverseInertiaTensor not implemented");
    }

    /**
     * @brief Returns the angular velocity in radians per second.
     * @return Angular velocity components.
     */
    [[nodiscard]] std::array<lambda::core::Real, 3> GetAngularVelocity() const noexcept {
        throw std::runtime_error("RigidBody::GetAngularVelocity not implemented");
    }

    /**
     * @brief Sets the angular velocity in radians per second.
     * @param angularVelocity New angular velocity components.
     * @return Status flag describing validation outcome.
     */
    [[nodiscard]] RigidBodyStatus SetAngularVelocity(const std::array<lambda::core::Real, 3>& /*angularVelocity*/) {
        throw std::runtime_error("RigidBody::SetAngularVelocity not implemented");
    }

    /**
     * @brief Returns the accumulated force in newtons.
     * @return Force accumulator contents.
     */
    [[nodiscard]] std::array<lambda::core::Real, 3> GetAccumulatedForce() const noexcept {
        throw std::runtime_error("RigidBody::GetAccumulatedForce not implemented");
    }

    /**
     * @brief Returns the accumulated torque in newton-meters.
     * @return Torque accumulator contents.
     */
    [[nodiscard]] std::array<lambda::core::Real, 3> GetAccumulatedTorque() const noexcept {
        throw std::runtime_error("RigidBody::GetAccumulatedTorque not implemented");
    }

    /**
     * @brief Applies a force in world space.
     * @param force Force vector in newtons.
     */
    void ApplyForce(const std::array<lambda::core::Real, 3>& /*force*/) {
        throw std::runtime_error("RigidBody::ApplyForce not implemented");
    }

    /**
     * @brief Applies a torque in world space.
     * @param torque Torque vector in newton-meters.
     */
    void ApplyTorque(const std::array<lambda::core::Real, 3>& /*torque*/) {
        throw std::runtime_error("RigidBody::ApplyTorque not implemented");
    }

    /**
     * @brief Applies an impulse to the center of mass.
     * @param impulse Impulse vector in newton-seconds.
     */
    void ApplyImpulse(const std::array<lambda::core::Real, 3>& /*impulse*/) {
        throw std::runtime_error("RigidBody::ApplyImpulse not implemented");
    }

    /**
     * @brief Applies an impulse at a world-space offset.
     * @param impulse Impulse vector in newton-seconds.
     * @param relativePosition Application point relative to the center of mass.
     */
    void ApplyImpulseAtPoint(const std::array<lambda::core::Real, 3>& /*impulse*/,
                             const std::array<lambda::core::Real, 3>& /*relativePosition*/) {
        throw std::runtime_error("RigidBody::ApplyImpulseAtPoint not implemented");
    }

private:
    lambda::core::Real _mass{};
    lambda::core::Real _inverseMass{};
    std::array<lambda::core::Real, 9> _inertiaTensor{};
    std::array<lambda::core::Real, 9> _inverseInertiaTensor{};

    std::array<lambda::core::Real, 3> _position{};
    std::array<lambda::core::Real, 3> _linearVelocity{};
    std::array<lambda::core::Real, 3> _angularVelocity{};

    std::array<lambda::core::Real, 3> _forceAccumulator{};
    std::array<lambda::core::Real, 3> _torqueAccumulator{};
};

} // namespace lambda::physics

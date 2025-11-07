// RigidBody.hpp
// Project Lambda - Rigid body physics implementation
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

#include <lambda/physics/IRigidBody.hpp>

#include <array>

namespace lambda::physics {

/**
 * @brief IRigidBody implementation with full physics state management.
 * @details Manages mass, inertia, position, velocity, and force/torque accumulators
 * for rigid body dynamics simulation.
 */
class RigidBody final : public IRigidBody {
public:
    /**
     * @brief Default constructor.
     * @details Creates a rigid body with zero mass, position, and velocity.
     */
    RigidBody() = default;

    /**
     * @brief Destructor.
     */
    ~RigidBody() override = default;

    /** @copydoc IRigidBody::GetMass */
    [[nodiscard]] lambda::core::Real GetMass() const noexcept override;

    /** @copydoc IRigidBody::SetMass */
    [[nodiscard]] RigidBodyStatus SetMass(lambda::core::Real mass) override;

    /** @copydoc IRigidBody::GetPosition */
    [[nodiscard]] std::array<lambda::core::Real, 3> GetPosition() const noexcept override;

    /** @copydoc IRigidBody::SetPosition */
    [[nodiscard]] RigidBodyStatus SetPosition(const std::array<lambda::core::Real, 3>& position) override;

    /** @copydoc IRigidBody::GetVelocity */
    [[nodiscard]] std::array<lambda::core::Real, 3> GetVelocity() const noexcept override;

    /** @copydoc IRigidBody::SetVelocity */
    [[nodiscard]] RigidBodyStatus SetVelocity(const std::array<lambda::core::Real, 3>& velocity) override;

    /** @copydoc IRigidBody::SetInertiaTensor */
    [[nodiscard]] RigidBodyStatus SetInertiaTensor(const std::array<lambda::core::Real, 9>& tensor) override;

    /** @copydoc IRigidBody::GetInertiaTensor */
    [[nodiscard]] std::array<lambda::core::Real, 9> GetInertiaTensor() const noexcept override;

    /**
     * @brief Returns the current orientation matrix (row-major 3x3).
     */
    [[nodiscard]] std::array<lambda::core::Real, 9> GetOrientationMatrix() const noexcept;

    /**
     * @brief Sets the current orientation matrix (row-major 3x3).
     * @param orientation Orientation matrix coefficients.
     * @return Validation status describing whether @p orientation was accepted.
     */
    [[nodiscard]] RigidBodyStatus SetOrientationMatrix(const std::array<lambda::core::Real, 9>& orientation);

    /**
     * @brief Returns the inverse mass (1 / mass).
     * @return Inverse mass value.
     */
    [[nodiscard]] lambda::core::Real GetInverseMass() const noexcept;

    /**
     * @brief Returns the inverse inertia tensor in local space.
     * @return Inverse inertia tensor values.
     */
    [[nodiscard]] std::array<lambda::core::Real, 9> GetInverseInertiaTensor() const noexcept;

    /**
     * @brief Returns the angular velocity in radians per second.
     * @return Angular velocity components.
     */
    [[nodiscard]] std::array<lambda::core::Real, 3> GetAngularVelocity() const noexcept;

    /**
     * @brief Sets the angular velocity in radians per second.
     * @param angularVelocity New angular velocity components.
     * @return Status flag describing validation outcome.
     */
    [[nodiscard]] RigidBodyStatus SetAngularVelocity(const std::array<lambda::core::Real, 3>& angularVelocity);

    /**
     * @brief Returns the accumulated force in newtons.
     * @return Force accumulator contents.
     */
    [[nodiscard]] std::array<lambda::core::Real, 3> GetAccumulatedForce() const noexcept;

    /**
     * @brief Returns the accumulated torque in newton-meters.
     * @return Torque accumulator contents.
     */
    [[nodiscard]] std::array<lambda::core::Real, 3> GetAccumulatedTorque() const noexcept;

    /**
     * @brief Applies a force in world space.
     * @param force Force vector in newtons.
     */
    void ApplyForce(const std::array<lambda::core::Real, 3>& force);

    /**
     * @brief Applies a torque in world space.
     * @param torque Torque vector in newton-meters.
     */
    void ApplyTorque(const std::array<lambda::core::Real, 3>& torque);

    /**
     * @brief Applies an impulse to the center of mass.
     * @param impulse Impulse vector in newton-seconds.
     */
    void ApplyImpulse(const std::array<lambda::core::Real, 3>& impulse);

    /**
     * @brief Applies an impulse at a world-space offset.
     * @param impulse Impulse vector in newton-seconds.
     * @param relativePosition Application point relative to the center of mass.
     */
    void ApplyImpulseAtPoint(const std::array<lambda::core::Real, 3>& impulse,
                             const std::array<lambda::core::Real, 3>& relativePosition);

    /**
     * @brief Clears the force and torque accumulators.
     * @details Called at the start of each physics step to reset accumulators.
     */
    void ClearAccumulators() noexcept;

private:
    /**
     * @brief Computes the inverse inertia tensor from the current inertia tensor.
     * @details Uses matrix inversion for 3x3 matrices. Sets _inverseInertiaTensor.
     */
    void ComputeInverseInertiaTensor();

    lambda::core::Real _mass{};
    lambda::core::Real _inverseMass{};
    std::array<lambda::core::Real, 9> _inertiaTensor{};
    std::array<lambda::core::Real, 9> _inverseInertiaTensor{};
    std::array<lambda::core::Real, 9> _orientationMatrix{
        lambda::core::Real{1.0}, lambda::core::Real{0.0}, lambda::core::Real{0.0},
        lambda::core::Real{0.0}, lambda::core::Real{1.0}, lambda::core::Real{0.0},
        lambda::core::Real{0.0}, lambda::core::Real{0.0}, lambda::core::Real{1.0}
    };

    std::array<lambda::core::Real, 3> _position{};
    std::array<lambda::core::Real, 3> _linearVelocity{};
    std::array<lambda::core::Real, 3> _angularVelocity{};

    std::array<lambda::core::Real, 3> _forceAccumulator{};
    std::array<lambda::core::Real, 3> _torqueAccumulator{};
};

} // namespace lambda::physics

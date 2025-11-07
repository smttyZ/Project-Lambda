#pragma once

#include <array>
#include <stdexcept>
#include <lambda/physics/IRigidBody.hpp>

/**
 * @brief Basic implementation of IRigidBody providing stubs for all required fields and accessors.
 * @note All methods currently throw std::runtime_error("Unimplemented") until defined.
 */
class RigidBody final : public IRigidBody {
public:
    RigidBody() = default;
    ~RigidBody() override = default;

    /** @copydoc IRigidBody::GetMass */
    [[nodiscard]] lambda::core::Real GetMass() const noexcept override {
        throw std::runtime_error("Unimplemented");
    }

    /** @copydoc IRigidBody::SetMass */
    [[nodiscard]] RigidBodyStatus SetMass(lambda::core::Real) override {
        throw std::runtime_error("Unimplemented");
    }

    /** @copydoc IRigidBody::GetPosition */
    [[nodiscard]] std::array<lambda::core::Real,3> GetPosition() const noexcept override {
        throw std::runtime_error("Unimplemented");
    }

    /** @copydoc IRigidBody::SetPosition */
    [[nodiscard]] RigidBodyStatus SetPosition(const std::array<lambda::core::Real,3>&) override {
        throw std::runtime_error("Unimplemented");
    }

    /** @copydoc IRigidBody::GetVelocity */
    [[nodiscard]] std::array<lambda::core::Real,3> GetVelocity() const noexcept override {
        throw std::runtime_error("Unimplemented");
    }

    /** @copydoc IRigidBody::SetVelocity */
    [[nodiscard]] RigidBodyStatus SetVelocity(const std::array<lambda::core::Real,3>&) override {
        throw std::runtime_error("Unimplemented");
    }

    /** @copydoc IRigidBody::SetInertiaTensor */
    [[nodiscard]] RigidBodyStatus SetInertiaTensor(const std::array<lambda::core::Real,9>&) override {
        throw std::runtime_error("Unimplemented");
    }

    /** @copydoc IRigidBody::GetInertiaTensor */
    [[nodiscard]] std::array<lambda::core::Real,9> GetInertiaTensor() const noexcept override {
        throw std::runtime_error("Unimplemented");
    }

    /**
     * @brief Gets the inverse mass of the rigid body (1 / mass).
     */
    [[nodiscard]] lambda::core::Real GetInverseMass() const noexcept {
        throw std::runtime_error("Unimplemented");
    }

    /**
     * @brief Gets the inverse inertia tensor of the rigid body.
     */
    [[nodiscard]] std::array<lambda::core::Real,9> GetInverseInertiaTensor() const noexcept {
        throw std::runtime_error("Unimplemented");
    }

    /**
     * @brief Returns the angular velocity (rad/s).
     */
    [[nodiscard]] std::array<lambda::core::Real,3> GetAngularVelocity() const noexcept {
        throw std::runtime_error("Unimplemented");
    }

    /**
     * @brief Sets the angular velocity (rad/s).
     */
    [[nodiscard]] RigidBodyStatus SetAngularVelocity(const std::array<lambda::core::Real,3>&) {
        throw std::runtime_error("Unimplemented");
    }

    /**
     * @brief Returns the accumulated force vector (N).
     */
    [[nodiscard]] std::array<lambda::core::Real,3> GetAccumulatedForce() const noexcept {
        throw std::runtime_error("Unimplemented");
    }

    /**
     * @brief Returns the accumulated torque vector (N·m).
     */
    [[nodiscard]] std::array<lambda::core::Real,3> GetAccumulatedTorque() const noexcept {
        throw std::runtime_error("Unimplemented");
    }

    /**
     * @brief Applies a force to the rigid body.
     * @param force The force vector to apply.
     */
    void ApplyForce(const std::array<lambda::core::Real,3>& force) {
        throw std::runtime_error("Unimplemented");
    }

    /**
     * @brief Applies a torque to the rigid body.
     * @param torque The torque vector to apply.
     */
    void ApplyTorque(const std::array<lambda::core::Real,3>& torque) {
        throw std::runtime_error("Unimplemented");
    }

    /**
     * @brief Applies an impulse to the rigid body.
     * @param impulse The impulse vector to apply.
     */
    void ApplyImpulse(const std::array<lambda::core::Real,3>& impulse) {
        throw std::runtime_error("Unimplemented");
    }

    /**
     * @brief Applies an impulse at a specific point relative to the center of mass.
     * @param impulse The impulse vector to apply.
     * @param relPos The position relative to the center of mass where the impulse is applied.
     */
    void ApplyImpulseAtPoint(const std::array<lambda::core::Real,3>& impulse, const std::array<lambda::core::Real,3>& relPos) {
        throw std::runtime_error("Unimplemented");
    }

private:
    lambda::core::Real _mass;
    lambda::core::Real _invMass;
    std::array<lambda::core::Real,9> _inertiaTensor;
    std::array<lambda::core::Real,9> _invInertiaTensor;

    std::array<lambda::core::Real,3> _position;
    std::array<lambda::core::Real,3> _velocityLinear;
    std::array<lambda::core::Real,3> _velocityAngular;

    std::array<lambda::core::Real,3> _forceAccumulator;
    std::array<lambda::core::Real,3> _torqueAccumulator;
};
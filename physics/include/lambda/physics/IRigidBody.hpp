#pragma once

#include <array>      // std::array
#include <cstdint>    // std::uint64_t
#include "core/Real.hpp" 
using namespace lambda::core;

namespace lambda::physics {

/**
 * @brief Status codes for routine validation outcomes.
 * @note Exceptions are reserved for unrecoverable errors; use status codes for argument checks.
 */
enum class RigidBodyStatus : std::uint8_t {
    OK = 0,
    INVALID_MASS = 1,
    INVALID_POSITION = 2,
    INVALID_VELOCITY = 3,
};

/**
 * @brief Utility: validates that mass is strictly positive and finite.
 */
[[nodiscard]] inline bool IsValidMass(lambda::core::Real mass) noexcept {
    try {
        return (mass > Real{0.0});
    } catch (...) {
        return false;
    }
}

/**
 * @brief Utility: validates that the inverse mass is non-negative and finite.
 */
[[nodiscard]] inline bool IsValidInverseMass(lambda::core::Real invMass) noexcept {
    try {
        return (invMass >= Real{0.0});
    } catch (...) {
        return false;
    }

/**
 * @brief Utility: validates that the position is finite and not NaN.
 */
[[nodiscard]] inline bool IsValidVector3(const std::array<lambda::core::Real,3>& v) noexcept {
    try {
        for (const auto& component : v) {
            // Just constructing verifies finiteness
            Real value = component;
            (void)value;
        }
        return true;
    } catch (...) {
        return false;
    }
}

/**
 * @brief Rigid body interface describing the minimum state/contract for bodies.
 *
 * This is an interface (pure virtual) on purpose: it encodes the rules and required
 * accessors/modifiers without prescribing storage or algorithms. Concrete implementations
 * (e.g., BasicRigidBody, ArticulatedBody, SoftProxy) will implement these methods.
 */
class IRigidBody {
public:
    virtual ~IRigidBody() = default;

    /**
     * @brief Returns the body's mass (kg). Guaranteed to be strictly positive.
     */
    [[nodiscard]] virtual lambda::core::Real GetMass() const noexcept = 0;

    /**
     * @brief Sets the body's mass (kg).
     * @param mass New mass value; must be finite and strictly greater than zero.
     * @return RigidBodyStatus::OK on success; RigidBodyStatus::INVALID_MASS if validation fails.
     * @note Implementations must NOT modify internal state on failure.
     */
    [[nodiscard]] virtual RigidBodyStatus SetMass(lambda::core::Real mass) = 0;

    /**
    * @brief Returns the body's position in world space (meters).
    */
    [[nodiscard]] virtual std::array<lambda::core::Real,3> GetPosition() const noexcept = 0;

    /**
    * @brief Sets the body's position in world space (meters).
    * @param position New COM coordinates in meters.
    * @return RigidBodyStatus::OK if valid; INVALID_POSITION otherwise.
    */
    [[nodiscard]] virtual RigidBodyStatus SetPosition(const std::array<lambda::core::Real,3>& position) = 0;

    /**
    * @brief Returns the body's linear velocity in world space (m/s).
    */
    [[nodiscard]] virtual std::array<lambda::core::Real,3> GetVelocity() const noexcept = 0;

    /**
    * @brief Sets the body's linear velocity in world space (m/s).
    * @param velocity New velocity components (m/s).
    * @return RigidBodyStatus::OK if valid; INVALID_VELOCITY otherwise.
    */
    [[nodiscard]] virtual RigidBodyStatus SetVelocity(const std::array<lambda::core::Real,3>& velocity) = 0;

    /**
     * @brief Set's the inertia tensor of the rigid body in local space (kg·m²).
     * @param inertiaTensor New inertia tensor as a 3x3 matrix in row-major order.
     * @return RigidBodyStatus::OK on success; appropriate error code on failure.
     */
    [[nodiscard]] virtual RigidBodyStatus SetInertiaTensor(const std::array<lambda::core::Real,9>& inertiaTensor) = 0;

    /**
     * @brief Returns the body's inertia tensor in local space (kg·m²) as a 3x3 matrix in row-major order.
     */
    [[nodiscard]] virtual std::array<lambda::core::Real,9> GetInertiaTensor() const noexcept = 0;

    
    
};
} // namespace lambda::physics
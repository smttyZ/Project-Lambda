// RigidBody.cpp
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

#include <lambda/physics/RigidBody.hpp>

#include <core/Matrix3.hpp>
#include <core/Real.hpp>
#include <core/Vector3.hpp>

namespace lambda::physics {

lambda::core::Real RigidBody::GetMass() const noexcept {
    return _mass;
}

RigidBodyStatus RigidBody::SetMass(lambda::core::Real mass) {
    if (!IsValidMass(mass)) {
        return RigidBodyStatus::INVALID_MASS;
    }

    _mass = mass;
    try {
        _inverseMass = lambda::core::Real{1.0} / _mass;
    } catch (...) {
        // Division by zero should not happen if IsValidMass passed
        return RigidBodyStatus::INVALID_MASS;
    }

    return RigidBodyStatus::OK;
}

std::array<lambda::core::Real, 3> RigidBody::GetPosition() const noexcept {
    return _position;
}

RigidBodyStatus RigidBody::SetPosition(const std::array<lambda::core::Real, 3>& position) {
    if (!IsValidVector3(position)) {
        return RigidBodyStatus::INVALID_POSITION;
    }

    _position = position;
    return RigidBodyStatus::OK;
}

std::array<lambda::core::Real, 3> RigidBody::GetVelocity() const noexcept {
    return _linearVelocity;
}

RigidBodyStatus RigidBody::SetVelocity(const std::array<lambda::core::Real, 3>& velocity) {
    if (!IsValidVector3(velocity)) {
        return RigidBodyStatus::INVALID_VELOCITY;
    }

    _linearVelocity = velocity;
    return RigidBodyStatus::OK;
}

RigidBodyStatus RigidBody::SetInertiaTensor(const std::array<lambda::core::Real, 9>& tensor) {
    // Validate all components are finite
    for (const auto& component : tensor) {
        try {
            [[maybe_unused]] const auto probe = component;
        } catch (...) {
            return RigidBodyStatus::INVALID_MASS;  // Reuse status code for invalid tensor
        }
    }

    _inertiaTensor = tensor;
    ComputeInverseInertiaTensor();
    return RigidBodyStatus::OK;
}

std::array<lambda::core::Real, 9> RigidBody::GetInertiaTensor() const noexcept {
    return _inertiaTensor;
}

std::array<lambda::core::Real, 9> RigidBody::GetOrientationMatrix() const noexcept {
    return _orientationMatrix;
}

RigidBodyStatus RigidBody::SetOrientationMatrix(const std::array<lambda::core::Real, 9>& orientation) {
    for (const auto& component : orientation) {
        try {
            [[maybe_unused]] const auto probe = component;
        } catch (...) {
            return RigidBodyStatus::INVALID_ORIENTATION;
        }
    }

    _orientationMatrix = orientation;
    return RigidBodyStatus::OK;
}

lambda::core::Real RigidBody::GetInverseMass() const noexcept {
    return _inverseMass;
}

std::array<lambda::core::Real, 9> RigidBody::GetInverseInertiaTensor() const noexcept {
    return _inverseInertiaTensor;
}

std::array<lambda::core::Real, 3> RigidBody::GetAngularVelocity() const noexcept {
    return _angularVelocity;
}

RigidBodyStatus RigidBody::SetAngularVelocity(const std::array<lambda::core::Real, 3>& angularVelocity) {
    if (!IsValidVector3(angularVelocity)) {
        return RigidBodyStatus::INVALID_VELOCITY;
    }

    _angularVelocity = angularVelocity;
    return RigidBodyStatus::OK;
}

std::array<lambda::core::Real, 3> RigidBody::GetAccumulatedForce() const noexcept {
    return _forceAccumulator;
}

std::array<lambda::core::Real, 3> RigidBody::GetAccumulatedTorque() const noexcept {
    return _torqueAccumulator;
}

void RigidBody::ApplyForce(const std::array<lambda::core::Real, 3>& force) {
    if (!IsValidVector3(force)) {
        return;
    }

    _forceAccumulator[0] = _forceAccumulator[0] + force[0];
    _forceAccumulator[1] = _forceAccumulator[1] + force[1];
    _forceAccumulator[2] = _forceAccumulator[2] + force[2];
}

void RigidBody::ApplyTorque(const std::array<lambda::core::Real, 3>& torque) {
    if (!IsValidVector3(torque)) {
        return;
    }

    _torqueAccumulator[0] = _torqueAccumulator[0] + torque[0];
    _torqueAccumulator[1] = _torqueAccumulator[1] + torque[1];
    _torqueAccumulator[2] = _torqueAccumulator[2] + torque[2];
}

void RigidBody::ApplyImpulse(const std::array<lambda::core::Real, 3>& impulse) {
    if (!IsValidVector3(impulse)) {
        return;
    }

    // Apply impulse directly to velocity: Δv = J / m
    const auto deltaVx = impulse[0] * _inverseMass;
    const auto deltaVy = impulse[1] * _inverseMass;
    const auto deltaVz = impulse[2] * _inverseMass;

    _linearVelocity[0] = _linearVelocity[0] + deltaVx;
    _linearVelocity[1] = _linearVelocity[1] + deltaVy;
    _linearVelocity[2] = _linearVelocity[2] + deltaVz;
}

void RigidBody::ApplyImpulseAtPoint(const std::array<lambda::core::Real, 3>& impulse,
                                    const std::array<lambda::core::Real, 3>& relativePosition) {
    if (!IsValidVector3(impulse) || !IsValidVector3(relativePosition)) {
        return;
    }

    // Apply linear impulse
    ApplyImpulse(impulse);

    // Compute angular impulse: τ = r × J
    // Angular velocity change: Δω = I⁻¹ * τ
    const auto torqueX = relativePosition[1] * impulse[2] - relativePosition[2] * impulse[1];
    const auto torqueY = relativePosition[2] * impulse[0] - relativePosition[0] * impulse[2];
    const auto torqueZ = relativePosition[0] * impulse[1] - relativePosition[1] * impulse[0];

    const lambda::core::Vector3 torqueVector{torqueX, torqueY, torqueZ};
    const lambda::core::Matrix3 inverseInertia{_inverseInertiaTensor};
    const auto deltaAngularVelocity = inverseInertia * torqueVector;

    _angularVelocity[0] = _angularVelocity[0] + deltaAngularVelocity.GetX();
    _angularVelocity[1] = _angularVelocity[1] + deltaAngularVelocity.GetY();
    _angularVelocity[2] = _angularVelocity[2] + deltaAngularVelocity.GetZ();
}

void RigidBody::ClearAccumulators() noexcept {
    _forceAccumulator[0] = lambda::core::Real{0.0};
    _forceAccumulator[1] = lambda::core::Real{0.0};
    _forceAccumulator[2] = lambda::core::Real{0.0};

    _torqueAccumulator[0] = lambda::core::Real{0.0};
    _torqueAccumulator[1] = lambda::core::Real{0.0};
    _torqueAccumulator[2] = lambda::core::Real{0.0};
}

void RigidBody::ComputeInverseInertiaTensor() {
    // Extract matrix elements (row-major order)
    const auto& m = _inertiaTensor;
    
    // For a 3x3 matrix, compute determinant
    // det = m00*(m11*m22 - m12*m21) - m01*(m10*m22 - m12*m20) + m02*(m10*m21 - m11*m20)
    const auto det = m[0] * (m[4] * m[8] - m[5] * m[7]) -
                     m[1] * (m[3] * m[8] - m[5] * m[6]) +
                     m[2] * (m[3] * m[7] - m[4] * m[6]);

    // Check for singular matrix (determinant near zero)
    try {
        const auto invDet = lambda::core::Real{1.0} / det;

        // Compute inverse matrix (row-major)
        _inverseInertiaTensor[0] = (m[4] * m[8] - m[5] * m[7]) * invDet;  // [0][0]
        _inverseInertiaTensor[1] = (m[2] * m[7] - m[1] * m[8]) * invDet;  // [0][1]
        _inverseInertiaTensor[2] = (m[1] * m[5] - m[2] * m[4]) * invDet;  // [0][2]
        _inverseInertiaTensor[3] = (m[5] * m[6] - m[3] * m[8]) * invDet;  // [1][0]
        _inverseInertiaTensor[4] = (m[0] * m[8] - m[2] * m[6]) * invDet;  // [1][1]
        _inverseInertiaTensor[5] = (m[2] * m[3] - m[0] * m[5]) * invDet;  // [1][2]
        _inverseInertiaTensor[6] = (m[3] * m[7] - m[4] * m[6]) * invDet;  // [2][0]
        _inverseInertiaTensor[7] = (m[1] * m[6] - m[0] * m[7]) * invDet;  // [2][1]
        _inverseInertiaTensor[8] = (m[0] * m[4] - m[1] * m[3]) * invDet;  // [2][2]
    } catch (...) {
        // Singular matrix - set inverse to zero
        for (auto& element : _inverseInertiaTensor) {
            element = lambda::core::Real{0.0};
        }
    }
}

} // namespace lambda::physics

// PhysicsWorld.cpp
// Project Lambda - Physics world implementation
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

#include <lambda/physics/PhysicsWorld.hpp>
#include <lambda/physics/RigidBody.hpp>

#include <core/Constants.hpp>
#include <core/Matrix3.hpp>
#include <core/Real.hpp>
#include <core/Vector3.hpp>

#include <algorithm>
#include <array>
#include <cassert>

namespace {

[[nodiscard]] lambda::core::Vector3 ToVector3(const std::array<lambda::core::Real, 3>& values) noexcept {
    return lambda::core::Vector3{values[0], values[1], values[2]};
}

[[nodiscard]] std::array<lambda::core::Real, 9> ToArray(const lambda::core::Matrix3& mat) noexcept {
    return {
        mat.Get(0, 0), mat.Get(0, 1), mat.Get(0, 2),
        mat.Get(1, 0), mat.Get(1, 1), mat.Get(1, 2),
        mat.Get(2, 0), mat.Get(2, 1), mat.Get(2, 2)
    };
}

[[nodiscard]] lambda::core::Real ClampSymmetric(lambda::core::Real value, lambda::core::Real limit) noexcept {
    if (value > limit) {
        return limit;
    }

    if (value < -limit) {
        return -limit;
    }

    return value;
}

} // namespace

namespace lambda::physics {

PhysicsWorld::PhysicsWorld() {
    Bang();
}

PhysicsWorld::~PhysicsWorld() {
    // Cleanup if needed
}

void PhysicsWorld::Bang() {
    _simulationTimeSeconds = 0.0L;
    _rigidBodies.clear();
}

void PhysicsWorld::Simulate(lambda::core::Real dt) {
    const auto zero = lambda::core::Real{0.0};
    assert((dt > zero) && "Physics timestep must be positive");

    const auto maxDt = lambda::core::Real{0.05};
    if (dt > maxDt) {
        dt = maxDt;
    }

    ApplyGlobalForces();
    IntegrateBodies(dt);
    DetectCollisions();
    ResolveCollisions();
    _simulationTimeSeconds += static_cast<long double>(dt.Value());
}

lambda::core::Real PhysicsWorld::GetSimulationTime() const {
    return lambda::core::Real{static_cast<double>(_simulationTimeSeconds)};
}

bool PhysicsWorld::AddRigidBody(RigidBody* body) {
    if (body == nullptr) {
        return false;
    }

    if (std::find(_rigidBodies.begin(), _rigidBodies.end(), body) != _rigidBodies.end()) {
        return false;
    }

    _rigidBodies.push_back(body);
    return true;
}

bool PhysicsWorld::RemoveRigidBody(RigidBody* body) {
    if (body == nullptr) {
        return false;
    }

    const auto it = std::find(_rigidBodies.begin(), _rigidBodies.end(), body);
    if (it == _rigidBodies.end()) {
        return false;
    }

    _rigidBodies.erase(it);
    return true;
}

void PhysicsWorld::FetchResults(bool /*waitForResults*/) noexcept {
    // Currently no async operations, so this is a no-op
    // Future: synchronize async physics computations if needed
}

void PhysicsWorld::ApplyGlobalForces() {
    using namespace lambda::core::Constants;

    // Apply gravity to all bodies
    const std::array<lambda::core::Real, 3> gravity{
        lambda::core::Real{0.0},
        -G,
        lambda::core::Real{0.0}
    };

    for (auto* rigidBody : _rigidBodies) {
        if (rigidBody == nullptr) {
            continue;
        }

        if (rigidBody->GetInverseMass() == lambda::core::Real{0.0}) {
            continue;
        }

        // Apply gravity force: F = m * g
        const auto mass = rigidBody->GetMass();
        const std::array<lambda::core::Real, 3> gravityForce{
            gravity[0] * mass,
            gravity[1] * mass,
            gravity[2] * mass
        };

        rigidBody->ApplyForce(gravityForce);
    }
}

void PhysicsWorld::IntegrateBodies(lambda::core::Real dt) {
    const auto zero = lambda::core::Real{0.0};
    const auto maxAngularVelocity = lambda::core::Real{100.0};

    for (auto* rigidBody : _rigidBodies) {
        if (rigidBody == nullptr) {
            continue;
        }

        const auto inverseMass = rigidBody->GetInverseMass();
        if (inverseMass == zero) {
            continue;
        }

        const auto force = rigidBody->GetAccumulatedForce();
        const std::array<lambda::core::Real, 3> linearAcceleration{
            force[0] * inverseMass,
            force[1] * inverseMass,
            force[2] * inverseMass
        };

        auto linearVelocity = rigidBody->GetVelocity();
        linearVelocity[0] = linearVelocity[0] + linearAcceleration[0] * dt;
        linearVelocity[1] = linearVelocity[1] + linearAcceleration[1] * dt;
        linearVelocity[2] = linearVelocity[2] + linearAcceleration[2] * dt;
        rigidBody->SetVelocity(linearVelocity);

        auto position = rigidBody->GetPosition();
        position[0] = position[0] + linearVelocity[0] * dt;
        position[1] = position[1] + linearVelocity[1] * dt;
        position[2] = position[2] + linearVelocity[2] * dt;
        rigidBody->SetPosition(position);

        const auto torque = ToVector3(rigidBody->GetAccumulatedTorque());
        const lambda::core::Matrix3 inverseInertia{rigidBody->GetInverseInertiaTensor()};
        const auto angularAcceleration = inverseInertia * torque;

        auto angularVelocity = rigidBody->GetAngularVelocity();
        angularVelocity[0] = angularVelocity[0] + angularAcceleration.GetX() * dt;
        angularVelocity[1] = angularVelocity[1] + angularAcceleration.GetY() * dt;
        angularVelocity[2] = angularVelocity[2] + angularAcceleration.GetZ() * dt;

        angularVelocity[0] = ClampSymmetric(angularVelocity[0], maxAngularVelocity);
        angularVelocity[1] = ClampSymmetric(angularVelocity[1], maxAngularVelocity);
        angularVelocity[2] = ClampSymmetric(angularVelocity[2], maxAngularVelocity);
        rigidBody->SetAngularVelocity(angularVelocity);

        lambda::core::Matrix3 orientation{rigidBody->GetOrientationMatrix()};
        const lambda::core::Matrix3 omegaCross(
            lambda::core::Real{0.0}, -angularVelocity[2], angularVelocity[1],
            angularVelocity[2], lambda::core::Real{0.0}, -angularVelocity[0],
            -angularVelocity[1], angularVelocity[0], lambda::core::Real{0.0}
        );

        const auto deltaRotation = lambda::core::Matrix3::Exp(omegaCross * dt);
        orientation *= deltaRotation;
        orientation.Orthonormalize();
        static_cast<void>(rigidBody->SetOrientationMatrix(ToArray(orientation)));

        rigidBody->ClearAccumulators();
    }
}

void PhysicsWorld::DetectCollisions() {
    // TODO: Implement collision detection
    // For now, this is a placeholder
}

void PhysicsWorld::ResolveCollisions() {
    // TODO: Implement collision resolution
    // For now, this is a placeholder
}

} // namespace lambda::physics

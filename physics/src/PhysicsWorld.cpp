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
#include <cstddef>
#include <vector>

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

    // Forces applied by callers before this step are held constant across it:
    // velocity Verlet evaluates forces at both ends of the step, so they are
    // captured here and re-applied after positions move.
    std::vector<std::array<lambda::core::Real, 3>> externalForces;
    externalForces.reserve(_rigidBodies.size());
    for (auto* rigidBody : _rigidBodies) {
        externalForces.push_back(rigidBody != nullptr
                                     ? rigidBody->GetAccumulatedForce()
                                     : std::array<lambda::core::Real, 3>{});
    }

    ApplyGlobalForces();
    IntegrateBodies(dt, externalForces);
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

// Linear motion uses velocity Verlet:
//   x(t+dt) = x + v*dt + 1/2*a(t)*dt^2
//   v(t+dt) = v + 1/2*(a(t) + a(t+dt))*dt
// with forces re-evaluated at the new positions for a(t+dt). Angular motion
// is unchanged (semi-implicit Euler on angular velocity, exponential map
// for orientation).
void PhysicsWorld::IntegrateBodies(lambda::core::Real dt,
                                   const std::vector<std::array<lambda::core::Real, 3>>& externalForces) {
    const auto zero = lambda::core::Real{0.0};
    const auto half = lambda::core::Real{0.5};
    const auto maxAngularVelocity = lambda::core::Real{100.0};

    std::vector<std::array<lambda::core::Real, 3>> startAcceleration(_rigidBodies.size());

    // Pass 1: move positions using a(t); integrate rotation.
    for (std::size_t i = 0; i < _rigidBodies.size(); ++i) {
        auto* rigidBody = _rigidBodies[i];
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

        startAcceleration[i] = linearAcceleration;

        const auto linearVelocity = rigidBody->GetVelocity();
        auto position = rigidBody->GetPosition();
        for (std::size_t k = 0; k < 3; ++k) {
            position[k] = position[k] + linearVelocity[k] * dt + half * linearAcceleration[k] * dt * dt;
        }
        static_cast<void>(rigidBody->SetPosition(position));

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
        static_cast<void>(rigidBody->SetAngularVelocity(angularVelocity));

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
        rigidBody->ApplyForce(externalForces[i]);
    }

    // Pass 2: forces at the new positions give a(t+dt); finish the velocity update.
    ApplyGlobalForces();
    for (std::size_t i = 0; i < _rigidBodies.size(); ++i) {
        auto* rigidBody = _rigidBodies[i];
        if (rigidBody == nullptr) {
            continue;
        }

        const auto inverseMass = rigidBody->GetInverseMass();
        if (inverseMass == zero) {
            continue;
        }

        const auto force = rigidBody->GetAccumulatedForce();
        auto linearVelocity = rigidBody->GetVelocity();
        for (std::size_t k = 0; k < 3; ++k) {
            const auto endAcceleration = force[k] * inverseMass;
            linearVelocity[k] = linearVelocity[k] + half * (startAcceleration[i][k] + endAcceleration) * dt;
        }
        static_cast<void>(rigidBody->SetVelocity(linearVelocity));
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

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

#include <core/Real.hpp>
#include <core/Constants.hpp>

#include <algorithm>
#include <array>

namespace lambda::physics {

PhysicsWorld::PhysicsWorld() {
    Bang();
}

PhysicsWorld::~PhysicsWorld() {
    // Cleanup if needed
}

void PhysicsWorld::Bang() {
    _simulationTime = 0.0;
    _rigidBodies.clear();
}

void PhysicsWorld::Simulate(lambda::core::Real dt) {
    // Physics simulation pipeline:
    // 1. Apply global forces (gravity)
    ApplyGlobalForces();

    // 2. Integrate bodies (semi-implicit Euler)
    IntegrateBodies(dt);

    // 3. Detect collisions
    DetectCollisions();

    // 4. Resolve collisions
    ResolveCollisions();

    // 5. Update simulation time
    _simulationTime += dt.Value();
}

void PhysicsWorld::AddRigidBody(IRigidBody* body) {
    if (body == nullptr) {
        return;
    }

    // Check if already added
    if (std::find(_rigidBodies.begin(), _rigidBodies.end(), body) != _rigidBodies.end()) {
        return;
    }

    _rigidBodies.push_back(body);
}

void PhysicsWorld::RemoveRigidBody(IRigidBody* body) {
    if (body == nullptr) {
        return;
    }

    const auto it = std::find(_rigidBodies.begin(), _rigidBodies.end(), body);
    if (it != _rigidBodies.end()) {
        _rigidBodies.erase(it);
    }
}

void PhysicsWorld::FetchResults(bool /*waitForResults*/) {
    // Currently no async operations, so this is a no-op
    // Future: synchronize async physics computations if needed
}

bool PhysicsWorld::TryAddRigidBody(IRigidBody* body) {
    if (body == nullptr) {
        return false;
    }

    // Check if already added
    if (std::find(_rigidBodies.begin(), _rigidBodies.end(), body) != _rigidBodies.end()) {
        return false;
    }

    _rigidBodies.push_back(body);
    return true;
}

bool PhysicsWorld::TryRemoveRigidBody(IRigidBody* body) {
    if (body == nullptr) {
        return false;
    }

    const auto it = std::find(_rigidBodies.begin(), _rigidBodies.end(), body);
    if (it != _rigidBodies.end()) {
        _rigidBodies.erase(it);
        return true;
    }

    return false;
}

void PhysicsWorld::ApplyGlobalForces() {
    using namespace lambda::core::Constants;

    // Apply gravity to all bodies
    const std::array<lambda::core::Real, 3> gravity{Real{0.0}, -G, Real{0.0}};

    for (auto* body : _rigidBodies) {
        if (body == nullptr) {
            continue;
        }

        // Skip static bodies (infinite mass)
        if (body->GetMass().Value() <= 0.0) {
            continue;
        }

        // Apply gravity force: F = m * g
        const auto mass = body->GetMass();
        const std::array<lambda::core::Real, 3> gravityForce{
            gravity[0] * mass,
            gravity[1] * mass,
            gravity[2] * mass
        };

        // Cast to RigidBody to access ApplyForce
        auto* rigidBody = dynamic_cast<RigidBody*>(body);
        if (rigidBody != nullptr) {
            rigidBody->ApplyForce(gravityForce);
        }
    }
}

void PhysicsWorld::IntegrateBodies(lambda::core::Real dt) {
    for (auto* body : _rigidBodies) {
        if (body == nullptr) {
            continue;
        }

        // Cast to RigidBody to access methods
        auto* rigidBody = dynamic_cast<RigidBody*>(body);
        if (rigidBody == nullptr) {
            continue;
        }

        // Skip static bodies (infinite mass, zero inverse mass)
        const auto inverseMass = rigidBody->GetInverseMass();
        if (inverseMass == lambda::core::Real{0.0}) {
            continue;
        }

        // 1. Compute linear acceleration: a = F / m
        const auto force = rigidBody->GetAccumulatedForce();
        const std::array<lambda::core::Real, 3> acceleration{
            force[0] * inverseMass,
            force[1] * inverseMass,
            force[2] * inverseMass
        };

        // 2. Update linear velocity: v_{t+Δt} = v_t + a * dt
        auto velocity = rigidBody->GetVelocity();
        velocity[0] = velocity[0] + acceleration[0] * dt;
        velocity[1] = velocity[1] + acceleration[1] * dt;
        velocity[2] = velocity[2] + acceleration[2] * dt;
        rigidBody->SetVelocity(velocity);

        // 3. Update position: x_{t+Δt} = x_t + v_{t+Δt} * dt
        // Note: Using updated velocity (semi-implicit Euler)
        auto position = rigidBody->GetPosition();
        position[0] = position[0] + velocity[0] * dt;
        position[1] = position[1] + velocity[1] * dt;
        position[2] = position[2] + velocity[2] * dt;
        rigidBody->SetPosition(position);

        // 4. Angular motion: ω_{t+Δt} = ω_t + I⁻¹ * τ * dt
        const auto torque = rigidBody->GetAccumulatedTorque();
        auto angVel = rigidBody->GetAngularVelocity();

        // Compute angular acceleration (α = I⁻¹ * τ)
        // Simplified for diagonal inertia tensor
        const auto invInertia = rigidBody->GetInverseInertiaTensor();
        const std::array<lambda::core::Real, 3> angularAccel{
            torque[0] * invInertia[0],  // [0][0]
            torque[1] * invInertia[4],  // [1][1]
            torque[2] * invInertia[8]   // [2][2]
        };

        // Update angular velocity: ω = ω + α * dt
        angVel[0] = angVel[0] + angularAccel[0] * dt;
        angVel[1] = angVel[1] + angularAccel[1] * dt;
        angVel[2] = angVel[2] + angularAccel[2] * dt;

        // Clamp angular velocity to prevent numerical drift
        constexpr double maxAngVel = 100.0;  // rad/s
        const auto clampValue = lambda::core::Real{maxAngVel};
        angVel[0] = (angVel[0] > clampValue) ? clampValue : 
                    ((angVel[0] < -clampValue) ? -clampValue : angVel[0]);
        angVel[1] = (angVel[1] > clampValue) ? clampValue : 
                    ((angVel[1] < -clampValue) ? -clampValue : angVel[1]);
        angVel[2] = (angVel[2] > clampValue) ? clampValue : 
                    ((angVel[2] < -clampValue) ? -clampValue : angVel[2]);

        rigidBody->SetAngularVelocity(angVel);

        // 5. Clear accumulators for next step
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

void PhysicsWorld::ClearAccumulators() {
    for (auto* body : _rigidBodies) {
        if (body == nullptr) {
            continue;
        }

        auto* rigidBody = dynamic_cast<RigidBody*>(body);
        if (rigidBody != nullptr) {
            rigidBody->ClearAccumulators();
        }
    }
}

} // namespace lambda::physics

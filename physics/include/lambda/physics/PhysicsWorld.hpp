// PhysicsWorld.hpp
// Project Lambda - High level physics world coordination interface
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

#include <core/Real.hpp>
#include <core/Clock.hpp>
#include <lambda/physics/IRigidBody.hpp>

#include <vector>

namespace lambda::physics {

/**
 * @brief Orchestrates integration, collision detection, and solver passes for rigid bodies.
 */
class PhysicsWorld final {
public:
    /**
     * @brief Constructor.
     */
    PhysicsWorld();

    /**
     * @brief Destructor.
     */
    ~PhysicsWorld();

    /**
     * @brief Initializes global state and prepares integration data structures.
     */
    void Bang();

    /**
     * @brief Advances the simulation by @p dt seconds.
     * @param dt Time step expressed in seconds.
     */
    void Simulate(lambda::core::Real dt);

    /**
     * @brief Registers a rigid body with the world.
     * @param body Instance to register; must outlive the world or be explicitly removed.
     */
    void AddRigidBody(IRigidBody* body);

    /**
     * @brief Removes a rigid body that was previously registered.
     * @param body Instance to remove.
     */
    void RemoveRigidBody(IRigidBody* body);

    /**
     * @brief Synchronizes world state back to the owning systems after simulation.
     * @param waitForResults When true, blocks until outstanding integration completes.
     */
    void FetchResults(bool waitForResults = true);

    /**
     * @brief Attempts to register a body but reports failure instead of throwing.
     * @param body Instance to register.
     * @return true when the body is registered successfully.
     */
    [[nodiscard]] bool TryAddRigidBody(IRigidBody* body);

    /**
     * @brief Attempts to remove a body but reports failure instead of throwing.
     * @param body Instance to remove.
     * @return true when the body is removed successfully.
     */
    [[nodiscard]] bool TryRemoveRigidBody(IRigidBody* body);

private:
    /**
     * @brief Applies global forces (e.g., gravity) to all bodies.
     */
    void ApplyGlobalForces();

    /**
     * @brief Integrates all bodies forward in time using semi-implicit Euler.
     * @param dt Time step in seconds.
     */
    void IntegrateBodies(lambda::core::Real dt);

    /**
     * @brief Detects collisions between rigid bodies.
     */
    void DetectCollisions();

    /**
     * @brief Resolves detected collisions.
     */
    void ResolveCollisions();

    /**
     * @brief Clears force and torque accumulators on all bodies.
     */
    void ClearAccumulators();

    std::vector<IRigidBody*> _rigidBodies;
    double _simulationTime{0.0};
};

} // namespace lambda::physics

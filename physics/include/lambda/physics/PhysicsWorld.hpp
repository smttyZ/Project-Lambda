#pragma once

#include "static/Clock.hpp"
#include <core/Real.hpp>

// note: stop putting [[nodiscard]] on void functions
// they already return nothing, so there's nothing to discard

class PhysicsWorld {
public:

namespace core = lambda::core;
namespace physics = lambda::physics;

    PhysicsWorld();
    ~PhysicsWorld();

    /**
     * @brief Initializes the physics world.
     * @return True if initialization was successful, false otherwise.
     * @note Bang = big bang of universe, aka world.
     */
    void Bang();

    /**
     * @brief Steps the physics simulation forward by the specified time delta.
     * @param dt Time step in seconds.
     */
    void Simulate(const lambda::core::Real dt);

    /**
     * @brief Adds a rigid body to the physics world.
     * @param body Pointer to the rigid body to add.
     * @note This function assumes the body is valid and DOES NOT perform any checks.
     */
    void AddRigidBody(void* body);

    /**
     * @brief Removes a rigid body from the physics world.
     * @param body Pointer to the rigid body to remove.
     * @note This function assumes the body is valid and DOES NOT perform any checks.
     */
    void RemoveRigidBody(void* body);

    /**
     * @brief Fetches the results of the physics simulation.
     * @param p If true, blocks until the results are available. p = patience.
     * @note This function updates the state of all rigid bodies in the world based on the simulation results.
     * WARNING: Using p = false may lead to undefined behavior if the simulation results are not ready.
     */
    void FetchResults(bool p = true);

    // EXPERIMENTAL FEATURES
    /**
     * @brief Attempts to add a rigid body to the physics world.
     * @param body Pointer to the rigid body to add.
     * @return True if the body was successfully added, false otherwise.
     * @note This is an experimental feature and may not work as intended.
     * It's intention, is to function as a catch-try block without... a catch-try block.
     */
    [[nodiscard]] bool TryAddRigidBody(void* body);

    /**
     * @brief Attempts to remove a rigid body from the physics world.
     * @param body Pointer to the rigid body to remove.
     * @return True if the body was successfully removed, false otherwise.
     * @note This is an experimental feature and may not work as intended. see TryAddRigidBody.
     */
    [[nodiscard]] bool TryRemoveRigidBody(void* body);
private:
    // helpers
    void ApplyGlobalForces();
    void IntegrateBodies(const lambda::core::Real dt);
    void DetectCollisions();
    void ResolveCollisions();
    void ClearAccumulators();


    double _simulationTime = 0.0;
};
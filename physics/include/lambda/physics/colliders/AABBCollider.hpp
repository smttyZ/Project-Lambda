// AABBCollider.hpp
// Project Lambda - Physics axis-aligned bounding-box collider definition
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
#include <core/Real.hpp>
#include <lambda/physics/colliders/ICollider.hpp>

#include <array>

namespace lambda::physics::colliders {

/**
 * @brief Collider defined by minimum and maximum extents aligned to the world axes.
 */
class AABBCollider final : public ICollider {
public:
    /**
     * @brief Constructs an AABB from minimum and maximum extents.
     * @param minPoint Minimum corner (world space).
     * @param maxPoint Maximum corner (world space).
     */
    AABBCollider(std::array<lambda::core::Real, 3> minPoint,
                 std::array<lambda::core::Real, 3> maxPoint) noexcept;

    /**
     * @brief Tests overlap with another collider instance.
     * @param other Collider to test against.
     * @return true when the two shapes overlap.
     */
    [[nodiscard]] bool Intersects(const ICollider& other) const noexcept override;

    /**
     * @brief Returns the collider center.
     * @return Center coordinates.
     */
    [[nodiscard]] std::array<lambda::core::Real, 3> GetCenter() const noexcept override;

    /**
     * @brief Returns the minimum world-space corner.
     * @return Minimum corner coordinates.
     */
    [[nodiscard]] std::array<lambda::core::Real, 3> GetMinPoint() const noexcept;

    /**
     * @brief Returns the maximum world-space corner.
     * @return Maximum corner coordinates.
     */
    [[nodiscard]] std::array<lambda::core::Real, 3> GetMaxPoint() const noexcept;

private:
    std::array<lambda::core::Real, 3> _minPoint{};
    std::array<lambda::core::Real, 3> _maxPoint{};
};

} // namespace lambda::physics::colliders

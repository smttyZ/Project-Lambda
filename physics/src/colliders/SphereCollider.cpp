// SphereCollider.cpp
// Project Lambda - Physics sphere collider implementation
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

#include <lambda/physics/colliders/SphereCollider.hpp>

#include <lambda/physics/colliders/AABBCollider.hpp>

#include <utility>

namespace lambda::physics::colliders {

namespace {

[[nodiscard]] bool IntersectsSphereSphere(const SphereCollider& lhs,
                                          const SphereCollider& rhs) noexcept {
    const auto lhsCenter = lhs.GetCenter();
    const auto rhsCenter = rhs.GetCenter();

    const auto dx = lhsCenter[0] - rhsCenter[0];
    const auto dy = lhsCenter[1] - rhsCenter[1];
    const auto dz = lhsCenter[2] - rhsCenter[2];

    const auto radiusSum = lhs.GetRadius() + rhs.GetRadius();
    const auto distanceSquared = (dx * dx) + (dy * dy) + (dz * dz);
    const auto radiusSumSquared = radiusSum * radiusSum;
    return distanceSquared <= radiusSumSquared;
}

[[nodiscard]] bool IntersectsSphereAABB(const SphereCollider& sphere,
                                        const AABBCollider& box) noexcept {
    const auto center = sphere.GetCenter();
    const auto minPoint = box.GetMinPoint();
    const auto maxPoint = box.GetMaxPoint();

    auto closest = center;
    for (int axis = 0; axis < 3; ++axis) {
        if (closest[axis] < minPoint[axis]) {
            closest[axis] = minPoint[axis];
        } else if (closest[axis] > maxPoint[axis]) {
            closest[axis] = maxPoint[axis];
        }
    }

    const auto dx = center[0] - closest[0];
    const auto dy = center[1] - closest[1];
    const auto dz = center[2] - closest[2];
    const auto distanceSquared = (dx * dx) + (dy * dy) + (dz * dz);
    const auto radiusSquared = sphere.GetRadius() * sphere.GetRadius();

    return distanceSquared <= radiusSquared;
}

} // namespace

SphereCollider::SphereCollider(std::array<lambda::core::Real, 3> center,
                               lambda::core::Real radius) noexcept
    : _center(std::move(center)),
      _radius(radius < lambda::core::Real{0.0} ? lambda::core::Real{0.0} : radius) {}

bool SphereCollider::Intersects(const ICollider& other) const noexcept {
    if (const auto* sphere = dynamic_cast<const SphereCollider*>(&other)) {
        return IntersectsSphereSphere(*this, *sphere);
    }

    if (const auto* box = dynamic_cast<const AABBCollider*>(&other)) {
        return IntersectsSphereAABB(*this, *box);
    }

    return false;
}

std::array<lambda::core::Real, 3> SphereCollider::GetCenter() const noexcept {
    return _center;
}

lambda::core::Real SphereCollider::GetRadius() const noexcept {
    return _radius;
}

} // namespace lambda::physics::colliders

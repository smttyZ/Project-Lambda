// AABBCollider.cpp
// Project Lambda - Physics axis-aligned bounding-box collider implementation
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

#include <lambda/physics/colliders/AABBCollider.hpp>

#include <lambda/physics/colliders/SphereCollider.hpp>

namespace lambda::physics::colliders {

AABBCollider::AABBCollider(std::array<lambda::core::Real, 3> minPoint,
                           std::array<lambda::core::Real, 3> maxPoint) noexcept {
    for (int axis = 0; axis < 3; ++axis) {
        if (minPoint[axis] <= maxPoint[axis]) {
            _minPoint[axis] = minPoint[axis];
            _maxPoint[axis] = maxPoint[axis];
        } else {
            _minPoint[axis] = maxPoint[axis];
            _maxPoint[axis] = minPoint[axis];
        }
    }
}

bool AABBCollider::Intersects(const ICollider& other) const noexcept {
    if (const auto* box = dynamic_cast<const AABBCollider*>(&other)) {
        const auto otherMin = box->GetMinPoint();
        const auto otherMax = box->GetMaxPoint();

        for (int axis = 0; axis < 3; ++axis) {
            if (_maxPoint[axis] < otherMin[axis] || _minPoint[axis] > otherMax[axis]) {
                return false;
            }
        }

        return true;
    }

    if (const auto* sphere = dynamic_cast<const SphereCollider*>(&other)) {
        return sphere->Intersects(*this);
    }

    return false;
}

std::array<lambda::core::Real, 3> AABBCollider::GetCenter() const noexcept {
    const auto half = lambda::core::Real{0.5};
    return {
        (_minPoint[0] + _maxPoint[0]) * half,
        (_minPoint[1] + _maxPoint[1]) * half,
        (_minPoint[2] + _maxPoint[2]) * half,
    };
}

std::array<lambda::core::Real, 3> AABBCollider::GetMinPoint() const noexcept {
    return _minPoint;
}

std::array<lambda::core::Real, 3> AABBCollider::GetMaxPoint() const noexcept {
    return _maxPoint;
}

} // namespace lambda::physics::colliders

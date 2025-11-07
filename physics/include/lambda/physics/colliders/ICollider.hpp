// ICollider.hpp
// Project Lambda - Physics collider interface
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
#include <array>

namespace lambda::physics::colliders {

/**
 * @brief Base collider interface shared by all narrow-phase shapes.
 */
class ICollider {
public:
    virtual ~ICollider() = default;

    /**
     * @brief Tests whether this collider overlaps another instance.
     */
    [[nodiscard]] virtual bool Intersects(const ICollider& other) const noexcept = 0;

    /**
     * @brief Returns the world-space center of this collider.
     */
    [[nodiscard]] virtual std::array<lambda::core::Real, 3> GetCenter() const noexcept = 0;
};

} // namespace lambda::physics::colliders

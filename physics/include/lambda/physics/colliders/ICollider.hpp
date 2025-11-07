#pragma once
#include <array>
#include <core/Real.hpp>

namespace lambda::physics::colliders {

    /**
 * @brief Base collider shape interface.
 */
    class ICollider {
    public:
        virtual ~ICollider() = default;

        /** @brief Returns true if this collider overlaps with another. */
        virtual bool Intersects(const ICollider& other) const noexcept = 0;

        /** @brief Returns the center position of the collider. */
        virtual std::array<lambda::core::Real, 3> GetCenter() const noexcept = 0;
    };

} // namespace lambda::physics::colliders
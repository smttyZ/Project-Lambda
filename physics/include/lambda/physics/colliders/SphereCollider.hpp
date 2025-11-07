#pragma once
#include <core/Real.hpp>

namespace lambda::physics::colliders {
    /**
 * @brief Sphere collider shape.
 */
    class SphereCollider {
    public:
        SphereCollider(std::array<lambda::core::Real, 3> center, lambda::core::Real radius);

        [[nodiscard]] bool Intersects(const ICollider& other) const noexcept override;
        [[nodiscard]] std::array<lambda::core::Real, 3> GetCenter() const noexcept override;

        [[nodiscard]] lambda::core::Real GetRadius() const noexcept;

    private:
        std::array<lambda::core::Real, 3> _center;
        lambda::core::Real _radius;
    };

} // namespace lambda::physics::colliders
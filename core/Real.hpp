#pragma once
#include <array>
#include <stdexcept>
#include <lambda/core/Real.hpp>

namespace lambda::physics {

    // Checks if the mass is a valid positive finite Real.
    inline bool IsValidMass(double mass) {
        try {
            lambda::core::Real r(mass);
            return r.Value() > 0.0;
        } catch (const std::invalid_argument&) {
            return false;
        }
    }

    // Checks if all components of the vector are valid finite Real values.
    inline bool IsValidVector3(const std::array<double, 3>& vec) {
        for (const auto& component : vec) {
            try {
                lambda::core::Real r(component);
            } catch (const std::invalid_argument&) {
                return false;
            }
        }
        return true;
    }

} // namespace lambda::physics

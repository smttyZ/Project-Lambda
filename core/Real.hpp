// Real.hpp
// Project Lambda - Legacy validation helpers bridging physics and core Real type
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

#include <array>
#include <stdexcept>

namespace lambda::physics {

/**
 * @brief Strongly-typed real number enforcing finite, valid values only.
 * @details The Real type forbids NaN and infinity by construction.
 * Any invalid input triggers a compile-time or runtime exception depending on context.
 */
class Real final {
public:

    constexpr Real() noexcept = default;

    constexpr explicit Real(double value)
        : _value(value) {
            if (!std::isfinite(value)) {
            throw std::invalid_argument("Real numbers must be finite (no NaN or infinity)");
        }
    }

    



}
}

} // namespace lambda::physics

// Clock.hpp
// Project Lambda - Global high-resolution timing utility
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

#include <atomic>
#include <chrono>
#include <cstdint>

namespace lambda::core {

/**
 * @brief Global monotonic timer for simulation coordination.
 */
class Clock final {
public:
    using ClockType = std::chrono::high_resolution_clock;
    using TimePoint = ClockType::time_point;
    using Duration = std::chrono::duration<double, std::milli>;

    /**
     * @brief Initializes the static clock using the provided tick rate.
     * @param tickRate Ticks per second to assume.
     */
    static void Initialize(double tickRate = 60.0) noexcept {
        _tickRate.store(tickRate, std::memory_order_relaxed);
        _tickInterval.store(1.0 / tickRate, std::memory_order_relaxed);
        _start = ClockType::now();
        _tickCount.store(0, std::memory_order_relaxed);
    }

    /**
     * @brief Advances the clock by one tick.
     */
    static void Advance() noexcept {
        _tickCount.fetch_add(1, std::memory_order_relaxed);
    }

    /**
     * @brief Returns ticks per second.
     * @return Configured tick rate.
     */
    [[nodiscard]] static double GetTickRate() noexcept {
        return _tickRate.load(std::memory_order_relaxed);
    }

    /**
     * @brief Returns seconds per tick.
     * @return Duration represented by a single tick.
     */
    [[nodiscard]] static double GetTickInterval() noexcept {
        return _tickInterval.load(std::memory_order_relaxed);
    }

    /**
     * @brief Returns the total number of ticks advanced.
     * @return Tick counter.
     */
    [[nodiscard]] static std::uint64_t GetTickCount() noexcept {
        return _tickCount.load(std::memory_order_relaxed);
    }

    /**
     * @brief Returns elapsed wall-clock seconds since initialization.
     * @return Seconds since Initialize was called.
     */
    [[nodiscard]] static double GetElapsedSeconds() noexcept {
        return std::chrono::duration<double>(ClockType::now() - _start).count();
    }

private:
    inline static std::atomic<double> _tickRate{60.0};
    inline static std::atomic<double> _tickInterval{1.0 / 60.0};
    inline static std::atomic<std::uint64_t> _tickCount{0};
    inline static TimePoint _start = ClockType::now();
};

} // namespace lambda::core

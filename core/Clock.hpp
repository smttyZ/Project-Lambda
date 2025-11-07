// Clock.hpp
// Project Lambda - Global high-resolution timing utility
// Copyright (C) 2025
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy at http://www.apache.org/licenses/LICENSE-2.0
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
        _lastFrameTime = ClockType::now();
        _tickCount.store(0, std::memory_order_relaxed);
        _accumulatedTime.store(0.0, std::memory_order_relaxed);
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

    /**
     * @brief Begins a new frame, updating the frame time accumulator.
     * @details Call this at the start of each frame to measure elapsed time
     * since the last frame. This accumulates time for fixed-step physics simulation.
     */
    static void BeginFrame() noexcept {
        const auto now = ClockType::now();
        const auto frameDelta = std::chrono::duration<double>(now - _lastFrameTime).count();
        _accumulatedTime.fetch_add(frameDelta, std::memory_order_relaxed);
        _lastFrameTime = now;
    }

    /**
     * @brief Consumes a fixed time step from the accumulator if available.
     * @param fixedStep Fixed time step in seconds (e.g., 1/60 for 60Hz physics).
     * @return true if a fixed step was consumed, false if insufficient time accumulated.
     * @details This method enables deterministic physics stepping regardless of frame rate.
     * If enough time has accumulated, it subtracts @p fixedStep from the accumulator
     * and returns true, allowing the physics simulation to advance by one step.
     * 
     * @example
     * ```cpp
     * Clock::BeginFrame();
     * while (Clock::ConsumeFixedStep(1.0 / 60.0)) {
     *     physicsWorld.Simulate(Real{1.0 / 60.0});
     * }
     * ```
     */
    [[nodiscard]] static bool ConsumeFixedStep(double fixedStep) noexcept {
        if (fixedStep <= 0.0) {
            return false;
        }
        
        double current = _accumulatedTime.load(std::memory_order_relaxed);
        if (current >= fixedStep) {
            double expected = current;
            while (!_accumulatedTime.compare_exchange_weak(
                expected, expected - fixedStep,
                std::memory_order_relaxed,
                std::memory_order_relaxed)) {
                if (expected < fixedStep) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    /**
     * @brief Gets the current accumulated time for fixed-step simulation.
     * @return Accumulated time in seconds.
     * @details Returns the amount of time accumulated since the last fixed step
     * was consumed. Useful for interpolation or debugging.
     */
    [[nodiscard]] static double GetAccumulatedTime() noexcept {
        return _accumulatedTime.load(std::memory_order_relaxed);
    }

    /**
     * @brief Resets the accumulated time accumulator.
     * @details Clears any accumulated time. Useful for pausing/resuming simulation
     * or resetting the fixed-step system.
     */
    static void ResetAccumulator() noexcept {
        _accumulatedTime.store(0.0, std::memory_order_relaxed);
    }

private:
    inline static std::atomic<double> _tickRate{60.0};
    inline static std::atomic<double> _tickInterval{1.0 / 60.0};
    inline static std::atomic<std::uint64_t> _tickCount{0};
    inline static TimePoint _start = ClockType::now();
    inline static TimePoint _lastFrameTime = ClockType::now();
    inline static std::atomic<double> _accumulatedTime{0.0};
};

} // namespace lambda::core


#pragma once
#include <chrono>

namespace lambda::core {
    /**
     * @brief Global high-res clock.
     * @note Thread-safe for reads and tick increment
     * @note If a clock subclass is needed in the future, consider making this an interface.
     */
    class Clock final {
    public:
        using ClockType = std::chrono::high_resolution_clock;
        using TimePoint = ClockType::time_point;
        using Duration = std::chrono::duration<double, std::milli>;

        /// @brief Initializes the global clock.
        /// @param tickRate 
        static void Initialize(double tickRate = 60.0) noexcept {
            _tickRate.store(tickRate);
            _tickInterval.store(1.0 / tickRate);
            _start = ClockType::now();
            _tickCount.store(0);
        }

        /// Advances one tick
        static void Advance() noexcept {
        _tickCount.fetch_add(1, std::memory_order_relaxed);
        }

        /// Returns ticks per second
        static double GetTickRate() noexcept { return _tickRate.load(); }

        /// Returns seconds per tick
        static double GetTickInterval() noexcept { return _tickInterval.load(); }

        /// Returns total ticks advanced
        static uint64_t GetTickCount() noexcept { return _tickCount.load(); }

        /// Returns elapsed real time since initialization
        static double GetElapsedSeconds() noexcept {
            return std::chrono::duration<double>(ClockType::now() - _start).count();
        }


    private:
            inline static std::atomic<double> _tickRate{60.0};
            inline static std::atomic<double> _tickInterval{1.0 / 60.0};
            inline static std::atomic<uint64_t> _tickCount{0};
            inline static TimePoint _start = ClockType::now();
    };
}
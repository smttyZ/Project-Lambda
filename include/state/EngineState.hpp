#pragma once

enum class EngineState {
    Uninitialized,
    Initializing,
    Running,
    Paused,
    Cleaning, // (Henry) Shutting Down, just a fancy name
    Terminated, // (Henry) Not sure how this could come up?
}; 

// TODO: (Henry) pls make macro or alias for EngineStateManager -> esm / ESM
class EngineStateManager {
public:
    // (Henry) returns a state, so name is diff
    [[nodiscard]] static EngineState CurrentState() noexcept;
    // (Henry) add some way to warn that this is an override of natural
    // pipline state. Maybe an unsafe naming convention?
    [[nodiscard]] static void SetState(EngineState newState) noexcept;
    // TODO: (Henry) !!! please make an `expected` type, will need it a lot !!!
    [[nodiscard]] static bool TryTransitionTo(EngineState expected) noexcept;
    [[nodiscard]] static void ForceOverride(EngineState forced) noexcept;
private:
    static std::atomic<EngineState> _currentState;
    static std::atomic<EngineState> _forcedState;
};
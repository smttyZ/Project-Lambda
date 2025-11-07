# Newton's Cradle Simulation Roadmap

Research checkpoint: build a reusable physics engine with pluggable scenes, and ship a Newton's Cradle preset (demo mode) that proves the runtime can simulate \(N\) identical spheres with accurate momentum transfer, reproducible instrumentation, and investor-friendly visualization (terminal/ASCII or lightweight UI overlays).

## Current State Audit
- `core/Real.hpp:18` includes `<lambda/core/Real.hpp>`, but no such header exists; every physics header depending on `lambda::core::Real` therefore fails to compile.
- `physics/include/lambda/physics/RigidBody.hpp:30` through `:119` expose mutators/accessors that currently throw `std::runtime_error`, so no rigid body can hold state or accept forces.
- `physics/include/lambda/physics/PhysicsWorld.hpp:19` declares orchestration methods (`Bang`, `Simulate`, collision passes) without implementations; `physics/src/` is empty, so the world cannot tick.
- `engine/CMakeLists.txt:17` and `prome/CMakeLists.txt:17` reference sources under `engine/src` and `prome/src` that do not exist, preventing the linker from producing the `lambda` executable declared in `apps/CMakeLists.txt:16`.
- No tests or scenario assets exist under `physics/tests/` or the repository root, so there is no automation to verify momentum conservation, constraint satisfaction, or determinism.

## Work Plan (Engine-First, Scene-Agnostic)

### 1. Mathematical & Core Infrastructure
- Implement `lambda::core::Real` plus SIMD-friendly vector/matrix/quat utilities under `include/core` so every module (physics, rendering, AI) shares numerics. `Real` should be a strongly typed wrapper that enforces the “strict rules instead of predefined constants” philosophy: construction is only allowed from finite scalars, arithmetic operators validate their outputs, and invalid literals trigger compile-time failures when used in `constexpr` contexts.
- Define SI-unit constants (`g`, `PI`) and generalized body/constraint configuration structs that any scene can consume (sphere, box, pendulum presets, etc.), with Newton's Cradle parameters treated as one preset among many.
- Extend `static/Clock.hpp` usage by adding a fixed-step accumulator API (`BeginFrame`, `ConsumeFixedStep`) so physics ticks stay deterministic regardless of which scene or visualization mode is active.

### 2. Rigid-Body Module & Semi-Implicit Integrator
- Flesh out `lambda::physics::RigidBody` with mass/inertia storage, pose state, and accumulators; keep APIs scene-agnostic so the same component can represent cradle bobs or any future rigid bodies.
- Author semi-implicit Euler integration inside `PhysicsWorld::Simulate` per

\[
\label{eq:semi_implicit_euler_v}
\mathbf{v}_{t+\Delta t} = \mathbf{v}_{t} + \Delta t \, \frac{\mathbf{F}_{t}}{m}
\]

\[
\label{eq:semi_implicit_euler_x}
\mathbf{x}_{t+\Delta t} = \mathbf{x}_{t} + \Delta t \, \mathbf{v}_{t+\Delta t}
\]

- Mirror the approach for angular velocity/orientation using inertia tensors, and keep the constraint interface generic so pendulums, rods, or future joints plug in cleanly.

### 3. Collision Detection, Constraints & Diagnostics
- Implement a pluggable broad-phase (start with axis sweep / spatial hash) and narrow-phase sphere/AABB overlaps using the collider interfaces so multiple scenes reuse the same pipeline.
- Solve impulses with tunable restitution \(e\) using

\[
\label{eq:impulse_response}
\mathbf{J} = -(1 + e)\,\frac{\mathbf{v}_{\text{rel}}\cdot \hat{n}}{\frac{1}{m_a} + \frac{1}{m_b}} \,\hat{n}
\]

- Verify momentum and kinetic energy transfer for equal-mass collisions per

\[
\label{eq:momentum_energy}
m v_{\text{in}} = m v_{\text{out}}, \qquad \tfrac{1}{2} m v_{\text{in}}^{2} = \tfrac{1}{2} m v_{\text{out}}^{2}
\]

- Surface contact manifolds, per-contact diagnostics, and logging hooks so research scripts and investor demos can inspect solver iterations regardless of scene.
- Provide a constraint layer (holonomic strings, distance joints, damped springs) that can connect arbitrary rigid bodies; cradle suspensions become a preset of this general system.

### 4. Scene System & Cradle Preset
- Introduce a lightweight scene registry (JSON, Lua, or CLI descriptors) describing rigid bodies, constraints, colliders, and instrumentation outputs; Newton's Cradle ships as `NewtonsCradle.scene` next to other demos.
- Use the suspension constraint to model each ball as a pendulum bob of length \(\ell\); match the period

\[
\label{eq:pendulum_period}
T = 2\pi \sqrt{\frac{\ell}{g}}
\]

- Convert release angle \(\theta\) into initial drop velocity via energy conservation

\[
\label{eq:potential_to_velocity}
v = \sqrt{2 g \ell \left(1 - \cos \theta\right)}
\]

- Provide configuration presets (number of spheres, pullback angles, damping curves) stored alongside other scenes; ensure the loader can cycle through presets for benchmarking or live demos.

### 5. User-Facing Runtime, Logging & Accessible Visualization
- Stand up a reusable runtime service that can run any scene headless (CSV logs: time, positions, velocities, total momentum) or with visualization backends (future GPU renderer, current terminal/ASCII mode).
- For investors or non-technical viewers, implement an optional ASCII/terminal dashboard by mapping sphere positions to columns via

\[
\label{eq:ascii_projection}
c_i = \left\lfloor \frac{x_i - x_{\min}}{\Delta x} \right\rfloor
\]

- Pair the ASCII view with tabular readouts (momentum, kinetic energy, constraint error) plus narrative text (“Ball #1 transferred \(0.98\,\text{J}\) to Ball #5”) so the output is understandable without domain expertise.
- Provide pause/step/reset commands, a scene selector, and preset descriptions through the CLI so an older-aged investor can launch the cradle demo without editing config files, while agents retain full scripting control.

### 6. Testing & Research Outputs
- Add GTest suites: `RigidBodyTests` (mass/validation), `PhysicsWorldIntegrationTests` (Eqs. \ref{eq:semi_implicit_euler_v}-\ref{eq:semi_implicit_euler_x}), `CollisionImpulseTests` (Eq. \ref{eq:impulse_response}), and `ConstraintDriftTests`.
- Wire the tests into CTest via `physics/tests/CMakeLists.txt` and ensure they run headless.
- Record canonical experiment logs (CSV + Markdown narrative) under `paper/` describing setup, parameters, and observed conservation metrics for repeatability, and highlight how the cradle preset demonstrates both scientific rigor and clear investor-facing output.

## Deliverables & Sequence
1. Math/core module with a strict `Real` wrapper (validated construction/operators), vector types, configuration structs, and deterministic clock wrappers usable by every subsystem.
2. Scene-agnostic `RigidBody` + `PhysicsWorld` implementation with semi-implicit integration, force application pipeline, and constraint interfaces.
3. Collision and constraint systems that support both Newton's Cradle and future demos, with shared diagnostics/logging.
4. Scene loader plus preset catalog (`NewtonsCradle`, future demos) with CLI selection and reproducible configuration.
5. User-facing runtime (headless + ASCII dashboard) that communicates results clearly to investors while remaining scriptable for agents.
6. Automated tests and research notes covering conservation, constraint stability, and deterministic replay across scenes.

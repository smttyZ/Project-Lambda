# Newton's Cradle Checkpoint Plan

## Goal
- Deliver a real-time, research-grade Newton's Cradle demo: \(N\) identical spheres, equal string lengths, accurate momentum transfer, camera + instrumentation, and reproducible logs.
- Run inside the Project Lambda toolchain (CMake targets + tests) so downstream agents can extend it without patching build scripts.

## Current Reality
- `physics/include/lambda/physics/RigidBody.hpp:34` exposes mass, pose, force, and impulse APIs but every method still throws, so no rigid body can exist at runtime.
- `physics/include/lambda/physics/PhysicsWorld.hpp:34` declares orchestration hooks without any backing implementation, and `physics/CMakeLists.txt:16` references `src/PhysicsWorld.cpp` / `src/CollisionSystem.cpp` that are absent.
- `core/Real.hpp:16` includes `<lambda/core/Real.hpp>`, yet that header/content does not exist anywhere in the tree, blocking all math/physics code from compiling.
- Rendering, scene traversal, and AI modules referenced in `engine/CMakeLists.txt:15`, `prome/CMakeLists.txt:15`, and `apps/CMakeLists.txt:15` have no sources, so there is currently no executable host for a simulation or tests.
- Test suites such as `tests/math/MathFunctionsTests.cpp:18` and `tests/window/LDWindowAPITests.cpp:18` include headers that are missing, leaving the repo unable to build, run, or validate any physics behavior today.

## Workstreams

### 1. Numerical Foundations
- Implement `lambda::core::Real`, vector/matrix types, and math constants so every include in `tests/math/*.cpp` resolves and `lambda_math` can be defined once.
- Provide serialization + unit conversion helpers (SI base units) to keep cradle parameters (mass, radius, string length) explicit; surface them via configuration structs consumable by agents.
- Add deterministic random utilities (initial perturbations, jitter) to support later experiments on chaotic transfers.

### 2. Rigid-Body State & Integration
- Finish `lambda::physics::RigidBody` to store mass, inertia, pose, and accumulators; expose validation through `RigidBodyStatus`.
- Author physics update equations (semi-implicit Euler is sufficient initially) and wire them into `PhysicsWorld::Simulate` per Eqs. \ref{eq:semi_implicit_euler_v}-\ref{eq:semi_implicit_euler_x}.

\[
\begin{aligned}
\label{eq:semi_implicit_euler_v}
\mathbf{v}_{t+\Delta t} &= \mathbf{v}_t + \Delta t \frac{\mathbf{F}_t}{m} \\
\label{eq:semi_implicit_euler_x}
\mathbf{x}_{t+\Delta t} &= \mathbf{x}_t + \Delta t \, \mathbf{v}_{t+\Delta t}
\end{aligned}
\]

- Integrate angular state using matching formulas with inertia tensors and clamp drift to keep the balls aligned on strings.
- Respect deterministic stepping by sourcing `dt` from `lambda::core::Clock` and exposing a fixed-step accumulator plus sub-stepping hooks for later refinement.

### 3. Collision Detection & Resolution
- Implement broad-phase (1D sweep along cradle axis) and narrow-phase sphere-sphere checks leveraging existing collider interfaces.
- Solve for impulses assuming perfectly elastic collisions between equal masses initially, then expose restitution \(e\) as a tunable parameter via Eq. \ref{eq:impulse_response}.

\[
\label{eq:impulse_response}
\mathbf{J} = - (1 + e)\,\frac{\mathbf{v}_{\text{rel}}\cdot \hat{n}}{\frac{1}{m_a} + \frac{1}{m_b}} \, \hat{n}
\]

- Enforce equal-mass momentum + energy transfer for validation according to Eq. \ref{eq:momentum_energy}:

\[
\label{eq:momentum_energy}
m \, v_{\text{in}} = m \, v_{\text{out}}, \qquad \tfrac{1}{2} m v_{\text{in}}^2 = \tfrac{1}{2} m v_{\text{out}}^2
\]

- Track contact manifolds for simultaneous multi-sphere interactions (e.g., launching two balls) and log solver iterations for research notebooks.

### 4. Suspension Constraints & Scenario Setup
- Model each ball as a pendulum bob with fixed string length \(\ell\); enforce holonomic constraints or approximate them with strong spring-damper forces projected along the hanger lines while observing the period in Eq. \ref{eq:pendulum_period}.

\[
\label{eq:pendulum_period}
T = 2\pi \sqrt{\frac{\ell}{g}}
\]

- Convert release angle \(\theta\) into drop height and initial speed via energy conservation (Eq. \ref{eq:potential_to_velocity}):

\[
\label{eq:potential_to_velocity}
v = \sqrt{2 g \Delta h} = \sqrt{2 g \ell (1 - \cos \theta)}
\]

- Author configuration presets (number of spheres, spacing, damping, gravitational field) and expose them through data files or CLI flags consumed by the future `lambda` executable.

### 5. Runtime Driver, Rendering, and Tooling
- Flesh out `LambdaEngine` MVP: GPU buffer setup, simple PBR or unlit spheres, shadowless lighting, and camera controls (orbit + dolly) referencing the math camera utilities once implemented.
- Implement an application entry (`apps/src/Main.cpp`) that wires physics ticks to rendering frames, with pause/step/reset controls and live charts (energy drift, contact impulses) for researchers.
- Provide scripting hooks (JSON or Lua) so experiments can sweep pullback angles or restitution automatically.

### 6. Verification & Research Outputs
- Add targeted GTests: rigid-body setters, collision impulse correctness (compare against Eq. \ref{eq:impulse_response}), constraint satisfaction, and regression tests for energy drift budgets.
- Build a headless benchmark mode that runs the cradle for fixed simulated seconds and emits CSV logs (positions, velocities, total momentum) for inclusion in `paper/`.
- Document methodology + expected results in the research notebook, linking logged data and describing how to reproduce runs via CMake/CLI commands.

## Deliverables Checklist
- [ ] `lambda_math` module with Real/vectors/matrices + passing math/window tests.
- [ ] `LambdaPhysics` implementation: rigid bodies, integration, collision solver, configuration-driven cradle scene.
- [ ] `LambdaEngine`/`lambda` executable capable of rendering the cradle and streaming metrics.
- [ ] Automated tests + headless scenario validating momentum transfer, constraint maintenance, and determinism.
- [ ] Research notes + datasets demonstrating the Newton's Cradle checkpoint, ready for the next set of AI-driven experiments.

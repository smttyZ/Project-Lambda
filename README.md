<!--
README.md
Project Lambda - Repository overview
Copyright (C) 2025
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
-->

<h1 align="center">Project Lambda: Can Artificial Agents Rediscover the Laws of Physics?</h1>

**Author:** Henry H. Hicks (Tallahassee State College)  
**Started:** 2025  

---

## Overview
Project Lambda is a personal research project built around one question: if an artificial agent can only observe and interact with a simulated world, can it work out the physical laws that govern that world?

Answering that needs two things: a physics simulation that is deterministic and trustworthy enough to experiment in, and agents that run experiments inside it. This repository is where both started. So far the work has gone into the physics side.

---

## Objectives
- Build a deterministic rigid-body simulation where the same inputs always produce the same results.
- Design agents that can run their own experiments in it: push objects, drop them, and record what happens.
- Study whether, and how, those agents arrive at relationships like constant gravitational acceleration or conservation of momentum, and where that breaks down.

---

## Status
| Area | State |
|---|---|
| `core/`: strict `Real` type, `Vector3`, `Matrix3`, constants | Working |
| `core/`: `Vector2`, `Vector4`, `Matrix4`, `Clock` | Interfaces declared, not yet implemented |
| `physics/`: rigid bodies, sphere/AABB colliders, velocity Verlet integration | Builds; all 5 tests pass (integration, rotation, determinism). Collisions are not yet covered by tests |

Linear motion uses **velocity Verlet**, which reproduces free fall exactly and keeps energy bounded in oscillating systems such as pendulums. That matters here because the integrator effectively defines the "laws" an agent can observe in the simulation.

The math layer has since been extracted into its own library, [kalon](https://github.com/smttyZ/kalon), and a new engine built on it is in progress at [Lambda-Physics-Engine](https://github.com/smttyZ/Lambda-Physics-Engine).

---

## Repository Structure
- `core/`: header-only foundations: `Real`, `Vector2/3/4`, `Matrix3/4`, constants, clock. This is the prototype's own copy; the maintained version of this math is [kalon](https://github.com/smttyZ/kalon).
- `physics/`: rigid bodies, colliders, and `PhysicsWorld` (headers in `physics/include/lambda/physics/`).
- `tests/`: GoogleTest suite for the physics world.
- `paper/`: research notes and the Newton's cradle roadmap.
- `scripts/`: formatting and lint helpers.
- `STYLEGUIDE.md`: C++ style conventions for the project.

---

## Getting Started

### Prerequisites
- CMake ≥ 3.20
- A C++23 compiler (clang++ 17 / g++ 13 or newer)
- Network access on first configure (GoogleTest is fetched automatically)
- `clang-format` and `clang-tidy` for the format and lint targets

### Configure & Build
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

### Tests
```bash
ctest --output-on-failure --test-dir build
```

---

## Development Workflow
- `cmake --build build --target format`: apply the project's clang-format profile.
- `cmake --build build --target lint`: run clang-tidy using `.clang-tidy`.
- `scripts/format.sh` / `scripts/lint.sh`: the same tools, runnable from any shell.
- Follow `STYLEGUIDE.md` for naming, documentation, and structure.

---

## License
Licensed under the **Apache License 2.0**. See [LICENSE](LICENSE) and [NOTICE.md](NOTICE.md).

---

## Citation
If you reference this project, please link to this repository:

> Hicks, H. H. (2025). *Project Lambda: Can Artificial Agents Rediscover the Laws of Physics?*  
> [https://github.com/smttyZ/Project-Lambda](https://github.com/smttyZ/Project-Lambda)

---

## Contact
**Henry H. Hicks**  
**Email:** smttyz4@gmail.com

---

> *"There comes a point where the mind takes a higher plane of knowledge, but can never prove how it got there."*  
> — attributed to Albert Einstein, as quoted in R. W. Clark, *Einstein: The Life and Times*

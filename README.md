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

**Author:** Henry H. Hicks  
**Institution:** Tallahassee State College  
**Year:** 2025  

---

## Overview
*Project Lambda* is an open research initiative exploring whether artificial agents can independently rediscover fundamental physical principles through observation, interaction, and adaptive reasoning.  

The project seeks to unify concepts from computational neuroscience, physics, and artificial intelligence to examine how machine systems may arrive at empirical laws similar to those discovered by human scientists.

---

## Objectives
- Design artificial agents capable of self-guided experimentation and observation.  
- Analyze the emergence of symbolic representations and laws from raw environmental data.  
- Investigate the limits of synthetic intelligence in rediscovering established physical principles.

---

## Repository Structure
- `include/` — Public headers exposed per domain (`math/`, `core/`, …).  
- `src/` — Engine and experiment implementations (entry point in `src/main.cpp`).  
- `scripts/` — Tooling helpers for formatting and static analysis.  
- `paper/` — Research notes, references, and experiment reports.  
- `STYLEGUIDE.md` — Canonical Project Lambda C++ style manifest.

---

## Getting Started

### Prerequisites
- CMake ≥ 3.20
- A C++23 compiler (clang++ 17 / g++ 13 or newer)
- GLFW 3.x and GoogleTest discoverable by CMake
- `clang-format` and `clang-tidy` for style enforcement

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
- `cmake --build build --target format` — Apply the project clang-format profile.
- `cmake --build build --target lint` — Execute clang-tidy using `.clang-tidy`.
- `scripts/format.sh` / `scripts/lint.sh` — Direct access to the tooling from any shell.
- Follow `STYLEGUIDE.md` for naming, documentation, and architectural rules. Extend the guide when introducing new patterns.

---

## License and Attribution
This project is licensed under the **Apache License 2.0**.  
All modifications, extensions, or derivative works must be properly documented to preserve the scientific integrity and intent of the original research.  

---

## Citation
If you reference or build upon this work, please cite as:

> Hicks, H. H. (2025). *Project Lambda: Can Artificial Agents Rediscover the Laws of Physics?*  
> Tallahassee State College.  
> [https://github.com/henryhicks/project-lambda](https://github.com/henryhicks/project-lambda)

---

## Contact
For correspondence, inquiries, or collaboration requests, please contact:  
**Henry H. Hicks** — *Tallahassee State College*  
**Email:** Hicks886@mymail.tsc.fl.edu  



> *"There comes a time when the mind takes a higher plane of knowledge but can never prove how it got there."*  
> — Albert Einstein

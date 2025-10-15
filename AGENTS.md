# Repository Guidelines

## Project Structure & Module Organization
Source resides in `src/` with the main entry point in `src/main.cpp`. Public headers live under `include/`, split into `include/core` for foundational utilities (e.g., type traits) and `include/math` for numerical helpers. Shared research materials and references sit in `paper/`. Place new libraries in `include/<domain>` with matching implementation in `src/`, and prefer lightweight headers so agents can experiment without cross-module rebuilds.

## Build, Test, and Development Commands
- `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug` generates the build tree with compiler commands for tooling.
- `cmake --build build` compiles the `ProjectLambda` binary against GLFW and GTest.
- `ctest --test-dir build` runs the GTest suite (currently exercised through the `ProjectLambda` target).
- `cmake --build build --target ProjectLambda --config Release` produces an optimized artifact for performance studies.

## Coding Style & Naming Conventions
Target C++23 with warnings enabled via your chosen toolchain. Use four-space indentation, brace-on-new-line for namespaces and types, and trailing return types only when clarity improves. Follow the existing pattern of PascalCase for public functions (`SinDegrees`, `CircleArea`) and ALL_CAPS for constants (`TRIG_TABLE_SIZE`, `PI`). Prefer `constexpr` or `const` where possible. Keep headers self-contained; include the narrowest dependency and rely on forward declarations for types declared elsewhere.

## Testing Guidelines
Extend coverage with GTest; co-locate test translation units under `tests/` (create the directory if missing) and link them through CMake. Name test cases with the pattern `DomainScenario_Result`, mirroring the APIs under test. Ensure new math or physics utilities ship with edge-case tests (negative angles, extreme magnitudes). After adding tests, run `ctest --output-on-failure --test-dir build` and confirm green status before submitting.

## Commit & Pull Request Guidelines
Commits should be focused and written in imperative mood, mirroring history entries such as `Add trigonometric lookup tables and fast Sin/Cos functions`. Reference related issues with `Refs #ID` or `Fixes #ID` when applicable. Pull requests must summarize intent, enumerate major changes, and call out follow-up work. Attach build and test results, include reproduction steps for behavioral changes, and provide screenshots or plots when updating research outputs in `paper/`.

## Dependencies & Environment
GLFW 3.x and GTest are required; ensure they are discoverable by CMake (system packages or vcpkg). Keep local compiler settings compatible with C++23; clang++-17 and g++-13 are known-good. Document any external datasets or configuration files added to support experiments, and commit sanitized defaults under version control.

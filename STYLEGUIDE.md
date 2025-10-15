# Project Lambda C++ Style Guide

## General Principles
- Target C++23; prefer `constexpr`, `inline`, and aggregate initialization for zero-cost abstractions.
- Keep headers self-contained and include only what they need. Place public symbols in the `lambda::` root namespace, then a domain namespace (e.g., `lambda::math`).
- Use four spaces for indentation and brace-on-new-line for namespaces, structs, and functions.

## Naming & Types
- Types and free functions use PascalCase (`Vector3`, `Matrix4`, `CircleArea`); member variables follow lowerCamelCase (`position`, `rotation`).
- Constants use ALL_CAPS with underscores (`TRIG_TABLE_SIZE`, `PI`). For user-defined numeric types (`Real`, `Integer`, etc.), default-construct to zero and expose arithmetic operators to mimic native types.
- Prefer `struct` over `class` for POD-like math types; make data members public when they represent the mathematical state directly.

## Documentation
- Annotate public structs and functions with Doxygen comments (`/** */` or `///`). Document constructor intent, parameter meaning, and units when applicable.
- Group related helpers with brief comment banners only when it aids navigation; avoid noisy prose.

## Math Modules
- Vectors live in `Vectors.hpp` and expose component-wise arithmetic, dot/cross, and normalization helpers. Provide symmetric scalar multiplication helpers (`scalar * vector`).
- Matrices live in `Matrices.hpp`, store data row-major, and supply factory functions (`Translation`, `Scale`, `RotationX`...). Compose model transforms in scale → rotate → translate order.
- Numeric primitives (`Real`, `Integer`, `Rational`, `Complex`) reside in `Numbers.hpp`. Implement full arithmetic and comparison operators plus conversions to `Real` or native types as needed.

## Coding Patterns
- Provide non-throwing helpers whenever possible; only throw for invalid states (e.g., zero denominator). Guard division operations against zero.
- When exposing global tables or singletons (e.g., trig lookup), keep them `inline` in headers to avoid ODR issues.
- Favor free functions or static factory methods instead of constructors with flags; readability beats micro-optimizations at this stage.

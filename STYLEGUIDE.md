<!--
STYLEGUIDE.md
Project Lambda - C++ style manifesto
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

# Project Lambda C++ Style Manifest


## 1. Encoding, Formatting, and Layout
- Files use UTF-8 without BOM and use LF line endings. Automated tooling should reject other encodings.
- Limit source lines to **120 characters**; wrap earlier if readability suffers.
- Indent with **four spaces**; tabs are forbidden.
- Trim trailing whitespace automatically. Keep files without extra blank lines at EOF.
- Apply K&R (1TBS) braces for all constructs, with the opening brace on the same line as the declaration.
- Add exactly one space around binary operators, after keywords, and after commas; skip spaces for unary operators and inside parentheses.
- Keep a blank line after the include block and between free functions. Separate major sections (includes, declarations, tests) with two blank lines when that clarifies structure.

```cpp
namespace lambda::math {
Real ComputeMagnitude(Vector3 value) {
    if (value.LengthSquared() == Real{}) {
        return Real{0};
    }
    return value.Length();
}
} // namespace lambda::math
```

Break long parameter lists or initializer lists so each logical element sits on its own line. Use brace
initialization (`{}`) for aggregates by default.

## 2. Include, Header, and Module Rules
- Order includes strictly:
  1. Matching header for the translation unit.
  2. Other project headers.
  3. External dependencies.
  4. C and C++ standard library headers.
- Within each group, sort lexicographically. Leave one blank line between groups only if it improves readability.
- Use `#pragma once` at the top of every header; no traditional include guards.
- Prefer forward declarations to shrink dependencies, but never expose incomplete types in public APIs that require knowledge of their size.
- Templates that need definitions live in `.ipp` files included from the `.hpp`. Keep compiled source in `.cpp`. Reserve `.ixx` for C++ modules when introduced.
- When designating initializers, allow the pattern for internal helpers; public APIs expose positional initialization unless a builder is clearer.

## 3. Files, Directories, and Namespaces
- File names use `CamelCase` (`MatrixOps.cpp`), while directory names stay `lowercase_with_underscores`.
- Place public headers in `include/<domain>` and implementations in `src/`.
- Namespace names are lowercase (`lambda::math::detail`). Limit nesting depth to three and prefer `detail` for internal implementation namespaces.
- No `using namespace` directives in headers. In `.cpp` files, a `using` directive may appear inside a function or anonymous namespace when it improves clarity.
- Anonymous namespaces are acceptable in `.cpp` files for internal linkage. Inline namespaces are reserved for versioning.

## 4. Naming Conventions
- **Types**: PascalCase (`Vector3`, `Transform`). Interfaces receive an `I` prefix, utilities may use `U` (`UStringBuilder`). Implementation details adopt an `Impl` suffix or leading underscore (`_QuaternionImpl`).
- **Enums**: PascalCase type name with ALL_CAPS enumerators (`enum class ColorSpace { LINEAR, SRGB };`).
- **Aliases**: Public aliases in PascalCase; internal aliases gain a leading underscore (`using _Index = std::size_t;`).
- **Concepts**: PascalCase or prefixed with `C` (`CArithmetic`).
- **Functions**: Public functions/methods use PascalCase (`ComputeNormals`). Private helpers use `camelCase` or leading underscore (`buildIndex`). Asynchronous APIs receive an `Async` prefix.
- **Predicates**: Begin with `Is`, `Has`, `Can`, or `Should`.
- **Factories**: `MakeX` or `FromX`.
- **Members**: Public data members are PascalCase; private members carry a leading underscore (`_position`).
- **Variables**: Locals and parameters use `camelCase`. Constants are ALL_CAPS. Global variables start with `Global` and are rare.
- **Macros**: ALL_CAPS with a `LAMBDA_` prefix to avoid collision.
- **Tests**: Follow `DomainScenario_Result` with underscores (`VectorNormalization_ZeroVector_NoChange`).

```cpp
class IRenderBackend {
public:
    virtual ~IRenderBackend() = default;
    virtual void SubmitFrame(FramePayload payload) = 0;
};

class VulkanRenderBackend final : public IRenderBackend {
public:
    void SubmitFrame(FramePayload payload) override;

private:
    QueueHandle _graphicsQueue;
};
```

## 5. Comments and Documentation
- Document every public struct, class, function, concept, and constant with a Doxygen block containing `@brief` and any relevant `@param`, `@return`, `@tparam`, or `@note`.
- Place Doxygen comments immediately before the declaration. Inline comments go above the statement they clarify.
- Use comments to explain reasoning, constraints, or side effects—never to restate the code.
- TODOs and FIXMEs follow `TODO(Name):` or `FIXME(Name):`.
- Include a file banner detailing the component name, brief summary, and Apache-2.0 license notice.
- Examples use the `@example` tag only when the usage is non-obvious.

```cpp
/**
 * @brief Samples a color ramp at the requested position.
 * @param ramp Normalized color ramp definition.
 * @param t Sample position in [0, 1].
 * @return Interpolated color at t.
 */
[[nodiscard]] Color SampleRamp(const ColorRamp& ramp, Real t);
```

## 6. Language Features and Idioms
- Prefer explicit types; use `auto` only when the type appears on the RHS or is evident (`auto* device = AcquireDevice();`).
- Default to `const`, `constexpr`, and `noexcept` whenever guarantees hold. Treat `constexpr` as the default for compile-time constants.
- Use `std::unique_ptr` for ownership transfer and `std::shared_ptr` only when shared ownership is essential. Raw pointers denote non-owning references; prefer references for required, non-null values.
- Reserve exceptions for unrecoverable errors. Routine error handling uses `Expected<T, Error>` or status codes.
- Document thread-safety. Use atomics or higher-level concurrency primitives; avoid bespoke threading ad hoc.
- Prefer concepts over SFINAE. Keep lambdas short and local; capture explicitly.
- Avoid long range-adaptor chains; materialize intermediate intent when readability suffers.
- Structured bindings are allowed, but ensure the tuple shape is obvious.
- Modules define clean architectural boundaries—only promote stable APIs.

## 7. Source File Organization
- Organize `.cpp` files as: includes, anonymous namespace helpers, class/member definitions, free functions, tests (when colocated).
- Group related helper functions together. Keep internal constants in anonymous namespaces or as `constexpr` variables with internal linkage.
- Place logging and assertions near the code they validate. Use project logging macros consistently once introduced.

## 8. Testing and Verification
- Tests live in `tests/<domain>/` with filenames mirroring the unit under test (`Matrix4Tests.cpp`).
- Structure GTest suites using `TEST_F` or `TEST_P` when shared fixtures make behavior clearer.
- Every new API ships with edge-case coverage—consider negative inputs, boundary values, and degenerate geometry.
- Run `ctest --output-on-failure --test-dir build` before submission and capture the result in merge requests.

## 9. Tooling and Workflow
- `clang-format` and `clang-tidy` configurations will align with this guide; run formatting before committing.
- CMake targets must follow consistent naming (PascalCase), with headers listed in `PUBLIC` or `PRIVATE` sections appropriately.
- Commit messages use imperative mood; include `Fixes #ID` or `Refs #ID` when applicable.
- Pull requests summarize intent, list major changes, and attach build/test logs. Highlight follow-up work explicitly.

## 10. Performance, Memory, and Safety
- Adopt RAII for all resources. Centralize allocation policies, especially for GPU or aligned memory, in dedicated helpers.
- Profile before optimizing. Document any micro-optimization with the benchmark that justified it.
- Validate inputs on boundaries exposed to external data. Integrate sanitizers (`address`, `undefined`, `thread`) into CI.
- Handle untrusted data defensively; refuse to parse unknown schema versions without explicit migration paths.

## 11. API Design and Stability
- Public APIs promise backward compatibility across tagged releases. Use deprecation macros and documentation before breaking changes.
- Prefer explicit parameter objects or structs when a function grows beyond four parameters or mixes units.
- Expose fluent interfaces sparingly; clarity beats chaining.
- Separate UI-layer types from math/physics domains to maintain modular boundaries.

## 12. Extending the Guide
When you encounter a pattern not covered here, draft the expectation, circulate the change during code review,
and update this document in the same pull request. Consistency is more valuable than individual preference.

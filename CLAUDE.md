# Project Lambda workspace

Henry is building Project Lambda, a deterministic physics simulation and research
platform, to learn. Four repos live side by side here:

- `kalon/`: header-only C++23 math library. Strongly typed: dimensions (L, M, T)
  are checked at compile time. You use it; you don't run it.
- `lambda-physics-engine/`: black-box solver. Takes inputs, steps, returns outputs.
  Pulls kalon in as a git submodule.
- `taxis/`: the orchestrator, the layer above the engine: sets up a simulation,
  runs it, and collects the results. Its design is not started, so what goes
  inside it (scenes or something else) is undecided. Empty until then.
- `project-lambda/`: the umbrella for the whole research project: this file, the
  style guide, the paper, results, and the showcase README. Its `core/` and
  `physics/` folders are an obsolete prototype.

prome (the agents) joins later as another module.

On Windows the folders are named `Lambda-Physics-Engine/` and `Project-Lambda/`.

First milestone: a two-body Kepler orbit, printed as text.

## Status
kalon is the only active repo. The engine and the prototype in `project-lambda/`
are intentionally out of date: their current structure (scenes, the Newton's cradle,
the CLI) was built before kalon existed and may not survive. Don't clean them up,
refactor them, or build on that structure unless Henry asks. When kalon changes,
only keep the engine building against it. Don't add code to taxis until Henry
starts orchestrator work.

## Who decides what
- Design decisions are Henry's: type design, which equations the engine uses,
  numerical methods, API shape. Explain options and trade-offs, review his code,
  point out errors. Don't write design code unless he asks.
- Busywork is fine to write: boilerplate, standard known math, test scaffolding,
  CMake, formatting.
- If unsure which side something falls on, ask.

## Conventions
- C++23. SI units inside the simulation; convert only at the boundaries.
- Numbers are `double` via `kalon::Real`. No `long double`.
- Determinism: same inputs give the same results on every machine.
- Style: `STYLEGUIDE.md`, `.clang-format` and `.clang-tidy` in `project-lambda/`
  are the source of truth. kalon carries copies; change both together.

## Workflow
- Never commit to `main`. Branch, open a PR; Henry merges.
- `spike/*` branches are throwaway experiments; `feat/*` branches are real work.
- One change per PR.
- Claude's commits end with `Co-authored-by: Claude <noreply@anthropic.com>`.
  Henry's don't, so the history shows which work is whose.
- Before each git command, say in one line what it does. Henry is learning git.
- Before each step of multi-step work, post a one-line "now doing X".

## Machines
- MacBook: `~/CLionProjects/lambda/`. Apple clang; CLion's bundled CMake and Ninja.
- Windows desktop "snowwhite": `C:\Users\Admin\Documents\GitHub\lambda\`. CLion's
  bundled MinGW GCC, CMake, Ninja and clang-tidy (under CLion's `bin\`). GitHub CLI
  is signed in, and git uses it for github.com. Shell tools default to PowerShell.
- GoogleTest comes in through CMake FetchContent, so there is nothing to install.

## Where this file lives
The real file is `CLAUDE.md` in the `project-lambda/` repo, so git keeps every machine
in sync. Each machine's workspace folder (`lambda/`) has a one-line `CLAUDE.md`
that imports it: `@project-lambda/CLAUDE.md` (Windows: `@Project-Lambda/CLAUDE.md`).
Edit this file, not the stub.

## Open TODOs
- MacBook: clone taxis into `~/CLionProjects/lambda/`, pull `project-lambda/`, and
  check the workspace stub is the one line `@project-lambda/CLAUDE.md`.

## Design doc
The design lives in a Google Doc, "Project Lambda: Design" (Part I system,
II kalon, III engine, IV taxis). Sections marked [Draft for review]
aren't approved yet. Nothing merges until its decision is written there.
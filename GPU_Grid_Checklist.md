# Project Lambda — GPU Grid Implementation Checklist

## MVP: First Pixels on Screen

1. **Window + Swapchain (or GL Context)**
   - Create window, initialize backend (`IGPUBackend::Initialize`), ensure valid backbuffer.
   - ✅ *Done when:* A cleared color shows and `BeginFrame/EndFrame` present without crashing.

2. **Camera & View/Projection Math**
   - Minimal `Camera` struct (position, forward, up, fov, aspect, near/far) + `ComputeViewProj()`.
   - ✅ *Done when:* You can print/log a stable VP matrix each frame.

3. **Grid Geometry (CPU-Generated)**
   - Build a routine to generate XY-plane lines centered at origin with N major/minor steps.
   - ✅ *Done when:* Buffers are built once at startup and sizes look correct in logs.

4. **Shader Pair (VS/FS) for Lines**
   - VS: transform positions by VP; FS: uniform color or per-vertex color.
   - ✅ *Done when:* Shaders compile and link; pipeline created.

5. **Command Path**
   - Add `RenderCommand` for “DrawLines { vb, ib, count, world }”.
   - ✅ *Done when:* Submit reaches the driver and draws (even off-screen).

6. **Draw Call**
   - Bind pipeline, set VP uniform, issue draw.
   - ✅ *Done when:* You see any lines.

---

## Core: Robustness and Usability

7. **Camera Controls (Orbit/Pan/Zoom)**
   - Mouse drag = orbit; Shift+drag = pan; wheel = zoom.
   - ✅ *Done when:* You can orbit around origin smoothly.

8. **Major/Minor Grid + Axis Highlights**
   - Parameters: `cellSize`, `majorEvery`, colors; X/Y axes tinted.
   - ✅ *Done when:* You can toggle majors and clearly see axes.

9. **DPI/Contrast Accessibility**
   - Uniforms for line thickness (pixel-space) and color theme.
   - ✅ *Done when:* Line thickness is legible and contrast-correct at 1440p.

10. **Frustum Culling / Range Clamp**
    - Only emit lines inside radius; optional shader discard.
    - ✅ *Done when:* Density constant when zooming; no slideshow.

11. **Constant/Uniform Buffer Layout**
    - Define `FrameUBO` and optional `DrawUBO`.
    - ✅ *Done when:* Uniforms are via buffer updates, not ad-hoc calls.

12. **Resource Lifetime & RAII**
    - Wrappers for `GpuBuffer`, `GpuProgram/Pipeline`, RAII cleanup.
    - ✅ *Done when:* ASan/UBSan clean on create/destroy.

13. **CMake & Directory Wiring**
    - Targets: `LambdaGPU`, `LambdaDemoGrid`; proper headers.
    - ✅ *Done when:* Demo builds and runs.

---

## Polish & Diagnostics

14. **Origin Indicator and Axis Gizmo**
    - Thicker origin lines; axis triad overlay.
    - ✅ *Done when:* Orientation always clear.

15. **Snap & Rulers (Optional)**
    - Tick marks or labels for distances.
    - ✅ *Done when:* Distances are easy to judge visually.

16. **Perf HUD**
    - Draw call count, frame times, camera distance.
    - ✅ *Done when:* F1 toggles overlay with stable readings.

17. **Config Hot-Reload**
    - Read `grid.toml/json`; hot reload on change.
    - ✅ *Done when:* File edit updates visuals instantly.

18. **Tests**
    - Validate math, counts, culling.
    - ✅ *Done when:* `ctest` passes locally and in CI.

19. **Logging & Errors**
    - Shader compile logs, pipeline errors visible.
    - ✅ *Done when:* Bad shader fails fast with readable message.

20. **Safety & CI**
    - Sanitizers, warnings-as-errors, formatting checks.
    - ✅ *Done when:* Clean CI signal on PR.

---

## Minimal File Map (Suggested)

```
include/gpu/GPUBackend.hpp      # Interface
include/gpu/GPURenderQueue.hpp  # Command queue
src/gpu/GPURenderQueue.cpp      # Implementation
src/gpu/backends/opengl/GLBackend.{hpp,cpp}
src/gpu/graphics/GridRenderer.{hpp,cpp}
include/gfx/Camera.hpp
src/gfx/Camera.cpp
shaders/grid.vert
shaders/grid.frag
apps/demo_grid/main.cpp
```

---

## Definition of Done (Grid)
- Runs at >120 FPS with 100×100 minor + 10×10 major lines on RTX 3050 @ 1440p.
- Smooth camera orbit/pan/zoom (no gimbal flips).
- Crisp lines at any zoom; thickness in pixels, not world units.
- High-contrast theme toggle works with accessibility settings.
- CI passes, no leaks, HUD stable.

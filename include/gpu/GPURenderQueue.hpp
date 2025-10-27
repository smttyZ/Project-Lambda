#pragma once

namespace lambda::gpu { 
/**
 * @brief Represents a submission queue for render commands targeting the GPU.
 *
 * @note This is a pure interface; concrete backends (OpenGL, Vulkan, Metal)
 *       will implement how commands are encoded and dispatched.
 */
struct RenderCommand {
    // Placeholder for mesh, material, transform, etc.
};

class GPURenderQueue {
public:
    virtual ~GPURenderQueue() = default;

    /// Submits a render command for execution on the GPU.
    virtual void Submit(const RenderCommand& cmd) noexcept = 0;
};
} // namespace lambda::gpu

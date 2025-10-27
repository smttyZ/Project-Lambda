#pragma once

#include <vector>

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

class GPURenderQueue final {
public:
    void EnqueueCommand(const RenderCommand& command);
    void Clear() noexcept;
    [[nodiscard]] const std::vector<RenderCommand>& Commands() const noexcept;

private:
    std::vector<RenderCommand> _commands;
};
} // namespace lambda::gpu

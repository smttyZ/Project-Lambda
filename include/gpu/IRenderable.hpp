#pragma once

#include <gpu/GPURenderQueue.hpp>

namespace lambda::render {

class IRenderable {
public:
    virtual ~IRenderable() = default;

    /**
     * @brief Render the object by submitting commands to the GPU render queue.
     *
     * @param renderQueue The GPU render queue to submit render commands to.
     */
    virtual void Render(gpu::GPURenderQueue& renderQueue) = 0;}
} // namespace lambda::render

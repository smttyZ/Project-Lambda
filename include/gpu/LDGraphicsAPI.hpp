#pragma once
/**
 * @file LDGraphicsAPI.hpp
 * @brief Defines the abstract interface for the Lambda Graphics API, which bridges rendering backends
 *        and provides high-level GPU control functions such as clearing, frame management, and viewport setup.
 * @copyright
 *   Project Lambda — Apache-2.0
 */

#include "core/ColorConversions.hpp"
#include "core/LDColor.hpp"
#include <GLFW/glfw3.h>

namespace lambda::gpu {

/**
 * @class LDGraphicsAPI
 * @brief Abstract graphics interface responsible for high-level rendering commands.
 *
 * The LDGraphicsAPI provides an abstraction layer over the GPU backend, offering functions
 * for frame management, clearing the screen, viewport configuration, and basic rendering options.
 * Implementations such as GLBackend or MetalBackend define backend-specific behavior.
 */
class LDGraphicsAPI {
public:
    virtual ~LDGraphicsAPI() = default;

    /**
     * @brief Initialize the graphics subsystem and connect to the underlying backend.
     * @return True if initialization succeeded; false otherwise.
     */
    virtual bool Initialize() noexcept = 0;

    /**
     * @brief Release all resources held by the graphics API.
     */
    virtual void Shutdown() noexcept = 0;

    /**
     * @brief Clears the framebuffer with a color that can be any convertible color type.
     * @tparam ColorType Any type that has a ToRGB() overload defined.
     * @param color The color to clear the screen with.
     *
     * @note This uses compile-time type enforcement; passing an unsupported type
     *       will trigger a compile-time error.
     */
    template<typename ColorType>
    inline void ClearScreen(const ColorType& color) noexcept {
        auto rgba = lambda::core::ToRGB(color);
        glClearColor(rgba.r, rgba.g, rgba.b, rgba.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    /**
     * @brief Begin a new frame for rendering operations.
     * 
     * Typically clears color/depth buffers and prepares the swapchain for drawing.
     */
    virtual void BeginFrame() noexcept = 0;

    /**
     * @brief Finalize and present the current frame.
     * 
     * Should swap the buffers and flush GPU commands.
     */
    virtual void EndFrame() noexcept = 0;

    /**
     * @brief Set the active viewport region for rendering.
     * @param x Left coordinate of the viewport origin.
     * @param y Bottom coordinate of the viewport origin.
     * @param width Width of the viewport in pixels.
     * @param height Height of the viewport in pixels.
     */
    virtual void SetViewport(int x, int y, int width, int height) noexcept = 0;

    /**
     * @brief Enable or disable depth testing for subsequent draw calls.
     * @param enable True to enable, false to disable.
     */
    virtual void EnableDepthTest(bool enable) noexcept = 0;

    /**
     * @brief Submit a queued list of GPU rendering commands for execution.
     * @param queue The render queue containing recorded commands.
     */
    virtual void SubmitRenderQueue(const GPURenderQueue& queue) noexcept = 0;
};

} // namespace lambda::gpu
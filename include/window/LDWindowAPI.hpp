// LDWindowAPI.hpp
// Project Lambda - LDWindow API
// Copyright (C) 2025
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

struct GLFWwindow;

namespace lambda::window {
/**
 * @brief Reports whether the LDWindow subsystem is ready for use.
 *
 * The initial implementation always returns true, providing a minimal
 * integration point for unit tests exercising the LDWindow DLL wiring.
 *
 * @return True when LDWindow is available.
 */
[[nodiscard]] bool IsAvailable() noexcept;

/**
 * @brief Creates a blank GLFW window and returns its handle.
 *
 * The window is configured with an OpenGL 3.3 core profile context, V-Sync enabled,
 * and the provided dimensions and title. A null pointer is returned when initialization
 * fails or invalid parameters are supplied.
 */
[[nodiscard]] GLFWwindow* CreateBlankWindow(int width, int height, const char* title) noexcept;

/**
 * @brief Releases a GLFW window previously created by @ref CreateBlankWindow.
 */
void DestroyWindow(GLFWwindow* window) noexcept;
} // namespace lambda::window
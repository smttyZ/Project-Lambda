// LDWindowAPI.cpp
// Project Lambda - LDWindow API implementation
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

#include <GLFW/glfw3.h>

#include <mutex>

#include "window/LDWindowAPI.hpp"

namespace lambda::window {
bool IsAvailable() noexcept {
    return true;
}

namespace {
std::once_flag g_glfwInitFlag;
bool g_glfwInitialized = false;

void InitializeGlfw() noexcept {
    g_glfwInitialized = glfwInit() == GLFW_TRUE;
}

[[nodiscard]] bool EnsureGlfwInitialized() noexcept {
    std::call_once(g_glfwInitFlag, InitializeGlfw);
    return g_glfwInitialized;
}
} // namespace

GLFWwindow* CreateBlankWindow(int width, int height, const char* title) noexcept {
    if (width <= 0 || height <= 0) {
        return nullptr;
    }

    if (!EnsureGlfwInitialized()) {
        return nullptr;
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    const char* windowTitle = (title != nullptr) ? title : "Project Lambda";
    GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);
    if (window == nullptr) {
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    return window;
}

void DestroyWindow(GLFWwindow* window) noexcept {
    if (window == nullptr) {
        return;
    }

    if (glfwGetCurrentContext() == window) {
        glfwMakeContextCurrent(nullptr);
    }

    glfwDestroyWindow(window);
}
} // namespace lambda::window

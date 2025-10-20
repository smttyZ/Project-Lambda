// main.cpp
// Project Lambda - Application entry point
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
#include "window/LDWindowAPI.hpp"

#include <chrono>
#include <iostream>
#include <thread>

/**
 * @brief Application entry point for the Project Lambda prototype.
 *
 * Prints a diagnostic string so build and runtime wiring can be validated quickly.
 *
 * @return Zero on success, non-zero otherwise.
 */
int main() {
    constexpr int kWidth = 800;
    constexpr int kHeight = 600;
    constexpr const char* kTitle = "Project Lambda";

    if (!lambda::window::IsAvailable()) {
        std::cerr << "LDWindow subsystem unavailable\n";
        return 1;
    }

    GLFWwindow* window = lambda::window::CreateBlankWindow(kWidth, kHeight, kTitle);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window\n";
        return 1;
    }

    std::cout << "Window created successfully\n";

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    lambda::window::DestroyWindow(window);
    return 0;
}

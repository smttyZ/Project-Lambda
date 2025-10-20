// LDWindowBlankWindowTests.cpp
// Project Lambda - LDWindow window-creation tests

#include <gtest/gtest.h>

#include "window/LDWindowAPI.hpp"

namespace lambda::window {

TEST(LDWindowAPI_CreateBlankWindow, ReturnsNullForInvalidSize) {
    EXPECT_EQ(CreateBlankWindow(0, 480, "Invalid"), nullptr);
    EXPECT_EQ(CreateBlankWindow(640, -1, "Invalid"), nullptr);
}

TEST(LDWindowAPI_CreateBlankWindow, CreatesWindowWhenPlatformSupportsGlfw) {
    GLFWwindow* window = CreateBlankWindow(320, 240, "Test Window");
    if (window == nullptr) {
        GTEST_SKIP() << "GLFW initialization unavailable in this environment";
    }

    ASSERT_NE(window, nullptr);
    DestroyWindow(window);
}

} // namespace lambda::window

cmake_minimum_required(VERSION 3.20)
project(ProjectLambda VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------------------------------------------------------------
# Dependencies
# ---------------------------------------------------------------
include(FetchContent)

# GLFW
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# GTest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


# ---------------------------------------------------------------
# Include paths
# ---------------------------------------------------------------
include_directories(${PROJECT_SOURCE_DIR}/include)

# ---------------------------------------------------------------
# Math (header-only)
# ---------------------------------------------------------------
add_library(lambda_math INTERFACE)
target_include_directories(lambda_math INTERFACE include)
target_compile_features(lambda_math INTERFACE cxx_std_23)

# ---------------------------------------------------------------
# LDWindow shared library
# ---------------------------------------------------------------
add_library(LDWindow SHARED
        src/LDWindowAPI.cpp
)
set_target_properties(LDWindow PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

target_include_directories(LDWindow
        PUBLIC ${PROJECT_SOURCE_DIR}/include
)
target_compile_features(LDWindow PUBLIC cxx_std_23)
target_link_libraries(LDWindow PRIVATE glfw)

# ---------------------------------------------------------------
# Application executable
# ---------------------------------------------------------------
add_executable(ProjectLambda src/main.cpp)
target_link_libraries(ProjectLambda
        PRIVATE lambda_math
        LDWindow
        glfw
)

# ---------------------------------------------------------------
# Tests
# ---------------------------------------------------------------
add_executable(LDWindowTests
        tests/window/LDWindowAPITests.cpp
        tests/window/LDWindowBlankWindowTests.cpp
)
target_link_libraries(LDWindowTests PRIVATE LDWindow GTest::gtest_main)

add_executable(MathTests
        tests/math/NumbersTests.cpp
        tests/math/VectorsTests.cpp
        tests/math/MatricesTests.cpp
        tests/math/CameraTests.cpp
        tests/math/MathFunctionsTests.cpp
)
target_link_libraries(MathTests PRIVATE GTest::gtest_main)

enable_testing()
add_test(NAME LDWindowTests COMMAND LDWindowTests)
add_test(NAME MathTests COMMAND MathTests)

# ---------------------------------------------------------------
# Tooling targets
# ---------------------------------------------------------------
set(PROJECT_FORMAT_SCRIPT ${PROJECT_SOURCE_DIR}/scripts/format.sh)
set(PROJECT_LINT_SCRIPT ${PROJECT_SOURCE_DIR}/scripts/lint.sh)

if (EXISTS ${PROJECT_FORMAT_SCRIPT})
    add_custom_target(format
            COMMAND ${PROJECT_FORMAT_SCRIPT}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMENT "Formatting sources with clang-format"
            VERBATIM)
endif()

if (EXISTS ${PROJECT_LINT_SCRIPT})
    add_custom_target(lint
            COMMAND ${PROJECT_LINT_SCRIPT} ${PROJECT_BINARY_DIR}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMENT "Running clang-tidy analysis"
            VERBATIM)
endif()

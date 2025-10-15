cmake_minimum_required(VERSION 3.20)
project(ProjectLambda VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
find_package(glfw3 REQUIRED)
find_package(GTest REQUIRED)

# Include paths
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(ProjectLambda ${SRC_FILES}
        include/math/Numbers.hpp
        include/math/Vectors.hpp
        include/math/Matrices.hpp)

# Link libs
target_link_libraries(ProjectLambda PRIVATE glfw GTest::gtest_main)

enable_testing()
add_test(NAME LambdaTests COMMAND ProjectLambda)

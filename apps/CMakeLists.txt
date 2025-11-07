# Applications
add_executable(lambda
    src/Main.cpp
)

target_link_libraries(lambda
    PRIVATE
        LambdaEngine
        LambdaPhysics
        LambdaProme
)

# Unit Tests
enable_testing()

add_executable(PhysicsTests
    ${PROJECT_SOURCE_DIR}/tests/physics/PhysicsWorldTests.cpp
)
target_link_libraries(PhysicsTests PRIVATE LambdaPhysics GTest::gtest_main)
add_test(NAME PhysicsTests COMMAND PhysicsTests)
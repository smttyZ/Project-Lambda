# tests/CMakeLists.txt
# Project Lambda - Test harness configuration

add_executable(PhysicsWorldTests
    PhysicsWorldTests.cpp
)

target_link_libraries(PhysicsWorldTests
    PRIVATE
        LambdaPhysics
        GTest::gtest_main
)

add_test(NAME PhysicsWorldTests COMMAND PhysicsWorldTests)

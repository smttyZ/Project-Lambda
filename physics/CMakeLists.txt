# Physics Engine Module
add_library(LambdaPhysics STATIC
    src/PhysicsWorld.cpp
    src/CollisionSystem.cpp
)

target_include_directories(LambdaPhysics
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(LambdaPhysics PUBLIC cxx_std_23)
target_link_libraries(LambdaPhysics PUBLIC lambda_math)

# Optional CLI for physics subsystem
add_executable(lambda-cli
    cli/Main.cpp
)
target_link_libraries(lambda-cli PRIVATE LambdaPhysics)
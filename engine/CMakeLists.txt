# Simulation Renderer
add_library(LambdaEngine STATIC
    src/RenderPipeline.cpp
    src/SceneGraph.cpp
)

target_include_directories(LambdaEngine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(LambdaEngine PUBLIC cxx_std_23)
target_link_libraries(LambdaEngine PUBLIC glfw lambda_math)
# Artificial Agents (Prometheus Engine)
add_library(LambdaProme STATIC
    src/AgentSystem.cpp
    src/BehaviorGraph.cpp
)

target_include_directories(LambdaProme
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(LambdaProme PUBLIC cxx_std_23)
target_link_libraries(LambdaProme PUBLIC lambda_math)
# physics/CMakeLists.txt
# Project Lambda - Physics module build rules
# Copyright (C) 2025
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Physics Engine Module
add_library(LambdaPhysics STATIC
    src/RigidBody.cpp
    src/PhysicsWorld.cpp
    src/CollisionSystem.cpp
)

target_include_directories(LambdaPhysics
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(LambdaPhysics PUBLIC cxx_std_23)
target_link_libraries(LambdaPhysics PUBLIC LambdaCore lambda_math)

# Optional CLI for physics subsystem
add_executable(lambda-cli
    cli/Main.cpp
)
target_link_libraries(lambda-cli PRIVATE LambdaPhysics)

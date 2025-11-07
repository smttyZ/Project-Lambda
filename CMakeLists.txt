# CMakeLists.txt
# Project Lambda - Root build configuration
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

cmake_minimum_required(VERSION 3.20)
project(ProjectLambda VERSION 0.2 LANGUAGES CXX)

# ---------------------------------------------------------------
# Global configuration
# ---------------------------------------------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# ---------------------------------------------------------------
# Dependencies
# ---------------------------------------------------------------

# GTest (for all test targets)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ---------------------------------------------------------------
# Subprojects
# ---------------------------------------------------------------
add_subdirectory(physics)
add_subdirectory(engine)
add_subdirectory(prome)
add_subdirectory(apps)

# ---------------------------------------------------------------
# Tooling targets (format & lint)
# ---------------------------------------------------------------
set(PROJECT_FORMAT_SCRIPT ${PROJECT_SOURCE_DIR}/scripts/format.sh)
set(PROJECT_LINT_SCRIPT ${PROJECT_SOURCE_DIR}/scripts/lint.sh)

if(EXISTS ${PROJECT_FORMAT_SCRIPT})
    add_custom_target(format
        COMMAND ${PROJECT_FORMAT_SCRIPT}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Formatting sources with clang-format"
        VERBATIM
    )
endif()

if(EXISTS ${PROJECT_LINT_SCRIPT})
    add_custom_target(lint
        COMMAND ${PROJECT_LINT_SCRIPT} ${PROJECT_BINARY_DIR}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Running clang-tidy analysis"
        VERBATIM
    )
endif()

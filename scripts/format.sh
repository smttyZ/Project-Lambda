#!/usr/bin/env bash
# Project Lambda - Formatting helper script
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

set -euo pipefail

if ! command -v clang-format >/dev/null 2>&1; then
    echo "clang-format not found on PATH." >&2
    exit 1
fi

repo_root="$(git rev-parse --show-toplevel)"
extensions=(
    "*.cpp"
    "*.hpp"
    "*.h"
    "*.ipp"
    "*.ixx"
)

mapfile -t files < <(git -C "${repo_root}" ls-files "${extensions[@]}")

if [[ ${#files[@]} -eq 0 ]]; then
    echo "No source files to format."
    exit 0
fi

clang-format -i "${files[@]}"

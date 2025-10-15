#!/usr/bin/env bash

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

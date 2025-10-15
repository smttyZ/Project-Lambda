#!/usr/bin/env bash

set -euo pipefail

repo_root="$(git rev-parse --show-toplevel)"
build_dir="${1:-${repo_root}/build}"

if [[ ! -f "${build_dir}/compile_commands.json" ]]; then
    echo "compile_commands.json not found in ${build_dir}." >&2
    echo "Generate the build with: cmake -S ${repo_root} -B ${build_dir}" >&2
    exit 1
fi

filter_noise() {
    sed '/[0-9]\+ warnings generated\./d;/Suppressed [0-9]\+ warnings/d'
}

status=0

if command -v run-clang-tidy >/dev/null 2>&1; then
    output="$(run-clang-tidy -quiet -p "${build_dir}" 2>&1)" || status=$?
    printf '%s\n' "${output}" | filter_noise
    exit ${status}
fi

if ! command -v clang-tidy >/dev/null 2>&1; then
    echo "Neither run-clang-tidy nor clang-tidy found on PATH." >&2
    exit 1
fi

mapfile -t files < <(git -C "${repo_root}" ls-files -- '*.cpp' '*.ixx')

if [[ ${#files[@]} -eq 0 ]]; then
    echo "No translation units available for clang-tidy."
    exit 0
fi

for file in "${files[@]}"; do
    output="$(clang-tidy "${repo_root}/${file}" -p "${build_dir}" --quiet 2>&1)" || status=$?
    printf '%s\n' "${output}" | filter_noise
done

exit ${status}

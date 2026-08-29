#!/usr/bin/env bash

set -euo pipefail

if (( $# != 1 )); then
    echo "Usage: $0 '<expression>'" >&2
    echo "Example: $0 '*.2948.*'" >&2
    exit 2
fi

build_dir="${BUILD_DIR:-./build}"
expression=$1

# Accept the convenient *.text.* spelling as well as a regular expression.
# For example, *.2948.* becomes .*2948.*.
regex=${expression//\*./.*}

if [[ ! -f "$build_dir/CMakeCache.txt" ]]; then
    echo "Configuring CMake build directory: $build_dir"
    cmake \
        -G Ninja \
        -S . \
        -B "$build_dir" \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_C_COMPILER_LAUNCHER=ccache \
        -DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
fi

mapfile -t targets < <(
    cmake --build "$build_dir" --target help \
        | awk -F': ' 'NF == 2 { print $1 }' \
        | rg '_tests$' \
        | rg "$regex" \
        | sort -u
)

if (( ${#targets[@]} == 0 )); then
    echo "No test build targets matched: $expression" >&2
    exit 1
fi

printf 'Building:'
printf ' %s' "${targets[@]}"
printf '\n'

cmake --build "$build_dir" --target "${targets[@]}"
ctest --test-dir "$build_dir" --output-on-failure -R "$regex"

# Compilations

[![CI](https://github.com/ronnie-adato/cpp_examples/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/ronnie-adato/cpp_examples/actions/workflows/ci.yml)

If you don't have `bazel` download and install it  [Bazel Introduction](https://bazel.build/about/intro)

## Linting

Run: `bazel run @hedron_compile_commands//:refresh_all`

## Compile & tests

Run: `bazel build --config=clang-tidy //...`

or for debugging
`bazel build -c dbg --config=clang-tidy //...`

## Running Tests

Run: `./bazel-bin/tests/tests-cpp-examples`

## Local CI (same steps as GitHub Actions)

Run: `./tools/ci.sh`

Notes:
- Requires `node` + `npx` for the Markdown lint step.
- Requires `clang-format` for the C++ format check (Ubuntu example: `sudo apt-get install -y clang-format`).
- Uses Bazel if installed; otherwise downloads Bazelisk v1.20.0 into `.tools/`.

## Inspecting logs

Open the file `/tmp/tests-cpp-examples.INFO`

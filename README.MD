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

## Inspecting logs

Open the file `/tmp/tests-cpp-examples.INFO`

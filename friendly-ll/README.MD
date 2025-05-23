# Problem Description

A linked list with friends is defined by the following node structure:

```c++

struct Node {
  int value;
  Node *next = nullptr;
  Node *afriend = nullptr;
};

```

`afriend` may point to any other node in the list or be null. Friendship doesn’t have to be mutual (i.e. a node pointed to by a friend pointer of another node, doesn’t have to point back).
Implement a clone function for such a list.

## Compile

If you don't have `bazel` download and install it  [Bazel Introduction](https://bazel.build/about/intro)

### Linting

Run: `bazel run @hedron_compile_commands//:refresh_all`

### Compilations

#### library

Run: `bazel build --config=clang-tidy //...`

#### tests

Run: `bazel build --config=clang-tidy //friendly-ll/tests:tests-friendly-ll`

## Running Tests

Run: `./bazel-bin/tests/tests-cpp-examples`

## Inspecting logs

Open the file `/tmp/tests-cpp-examples.INFO`

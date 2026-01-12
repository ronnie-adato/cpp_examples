# Largest Square

## Task

Given a 2D matrix of integers, compute the side-length of the largest axis-aligned square
sub-matrix whose cells are all non-zero.

## API

```cpp
unsigned largest_square(const std::vector<std::vector<int>>& matrix);
```

The input matrix is treated as binary (any non-zero value counts as `1`).

## Notes

- Returns `0` for an empty matrix or when no non-zero square exists.

## Build / Test (Bazel)

- Build: `bazel build //largest_square/...`
- Run all tests: `bazel test //tests:all`
- Run only this module’s tests: `bazel test //largest_square/tests:tests-largest_square`

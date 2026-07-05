# All Nodes Distance K in Binary Tree (LeetCode 863, Medium)

LeetCode: <https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/>

## Problem Description

Given the root of a binary tree, a target node, and an integer `k`, return the values of all nodes
whose distance from the target is exactly `k`.

The answer may be returned in any order.

## Examples

```text
Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
Output: [7,4,1]
```

```text
Input: root = [1], target = 1, k = 3
Output: []
```

## Illustration

```mermaid
flowchart TB
    N3((3)) --- N5((5))
    N3 --- N1((1))
    N5 --- N6((6))
    N5 --- N2((2))
    N2 --- N7((7))
    N2 --- N4((4))
    N1 --- N0((0))
    N1 --- N8((8))

    N5:::target
    N7:::answer
    N4:::answer
    N1:::answer

    classDef target fill:#ffe8a3,stroke:#8a6d00,stroke-width:2px
    classDef answer fill:#d9f7be,stroke:#237804,stroke-width:2px
```

**Topics**: Tree, Graph BFS

## Build / Test (Bazel)

- Build: `bazel build //all-nodes-distance-k/...`
- Test: `bazel test //all-nodes-distance-k/tests:tests-all-nodes-distance-k`

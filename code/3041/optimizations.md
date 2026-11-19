# 3041: approach and optimisations

Process values in descending order. Track the longest consecutive chain starting
at the current value when it is kept or incremented. Transitions depend only on
the gap to the previous value, so two DP states replace the arrays.

At most two copies of a value matter: they can become `x` and `x + 1`.
Two bitsets encode presence and duplication, allowing each distinct value to be
processed once. Equal-valued inputs return `min(n, 2)`.

Choose how to obtain descending order:

- **Small inputs (`n <= 128`):** comparison sort avoids setup costs.
- **Medium, sparse inputs:** two 10-bit radix passes cover the 20-bit value
  range. Sort values directly, alternating input and scratch buffers.
- **Large or dense inputs:** enumerate the bitsets in descending order, avoiding
  sorting. Clear and scan only the observed value range.

The bitset route costs $O(n + R/64 + D)$, where $R$ is the observed range and
$D$ the number of distinct values. Radix sorting costs $O(n + 1024)$ per pass.

## Traversal variants

The default remains the adaptive implementation in `3041.hpp`. Three separate
headers use the same distinct-value DP transition:

- `3041_flat_bitset.hpp`: scan presence words, then their set bits, descending.
- `3041_pyramid_bitset.hpp`: find the maximum and repeatedly query its strict
  predecessor, skipping empty regions through summary layers.
- `3041_radix.hpp`: sort with two 10-bit passes, then walk equal-value groups
  backwards, recording whether each group has at least two elements.

All four run the same cases in `3041_tests.cpp`. These are alternative
implementations; their relative performance has not been measured in this change.
The [variant convention](../solution_variants.md) keeps each header independently
submittable.

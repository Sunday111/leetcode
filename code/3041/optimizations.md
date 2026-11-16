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

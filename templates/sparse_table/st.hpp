#pragma once

#include <concepts>

// Op must be associative and idempotent (min, max, unsigned gcd)
template <typename T, std::unsigned_integral Index, typename Op>
struct SparseTable
{
    T* x;
    Index size;
};

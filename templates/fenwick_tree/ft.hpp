#pragma once

#include <concepts>

// Traits::Op must be associative and commutative; Traits::Inv must undo it.
// Traits::identity must be neutral: addition/subtraction (0), XOR/XOR (0),
// multiplication/division (1; nonzero factors and exact, representable
// products).
template <typename T, std::unsigned_integral Index, typename Traits>
struct FenwickTree
{
    T* x;
    Index size;
};

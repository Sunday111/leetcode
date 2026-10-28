#pragma once

#include <concepts>

template <typename T, std::unsigned_integral Index, typename Traits>
struct FenwickTree
{
    T* x;
    Index size;
};

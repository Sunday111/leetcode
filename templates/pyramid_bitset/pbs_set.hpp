#pragma once

#include "pyramid_bitset/pbs_add.hpp"
#include "pyramid_bitset/pbs_remove.hpp"

template <bool v, size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_set(
    PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType idx) noexcept
{
    if constexpr (v)
    {
        pbs_add(bits, idx);
    }
    else
    {
        pbs_remove(bits, idx);
    }
}

template <size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_set(
    PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType idx,
    bool v) noexcept
{
    if (v)
    {
        pbs_add(bits, idx);
    }
    else
    {
        pbs_remove(bits, idx);
    }
}

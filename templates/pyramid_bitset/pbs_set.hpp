#pragma once

#include "pyramid_bitset/pbs_add.hpp"
#include "pyramid_bitset/pbs_remove.hpp"

template <bool v, u32 capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_set(
    const PyramidBitset<capacity, Word>& bits,
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

template <u32 capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_set(
    const PyramidBitset<capacity, Word>& bits,
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

#pragma once

#include "bitsets/bitset_view/bsv_get.hpp"
#include "pyramid_bitset/pbs_layer_view.hpp"

template <u32 capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr bool pbs_get(
    const PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    return bsv_get(pbs_layer_view<0>(bits), v);
}

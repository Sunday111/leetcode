#pragma once

#include "bitsets/bitset_view/bsv_set.hpp"
#include "pyramid_bitset/pbs_layer_view.hpp"
#include "pyramid_bitset/pbs_layers.hpp"

template <u32 capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_add(
    const PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    pbs_for_each_layer<B>(
        [&]<size_t layer> [[gnu::always_inline]] (
            std::integral_constant<size_t, layer>) noexcept
        {
            bsv_set<true>(pbs_layer_view<layer>(bits), v);
            v >>= B::kShift;
        });
}

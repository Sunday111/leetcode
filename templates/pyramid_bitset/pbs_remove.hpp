#pragma once

#include "bitsets/bitset_view/bsv_set_if.hpp"
#include "pyramid_bitset/pbs_layer_view.hpp"
#include "pyramid_bitset/pbs_layers.hpp"

template <u32 capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_remove(
    const PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    bool prev_empty = true;
    pbs_for_each_layer<B>(
        [&]<size_t layer> [[gnu::always_inline]] (
            std::integral_constant<size_t, layer>) noexcept
        {
            const auto view = pbs_layer_view<layer>(bits);
            prev_empty = bsv_set_if<false>(view, v, prev_empty) == 0;
            v >>= B::kShift;
        });
}

#pragma once

#include "bitsets/bitset_view/bsv_get.hpp"
#include "bitsets/bitset_view/bsv_set_if.hpp"
#include "pyramid_bitset/pbs_layer_view.hpp"
#include "pyramid_bitset/pbs_layers.hpp"

template <u32 capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr bool pbs_remove_ex(
    const PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    bool prev_empty = true, removed = false;
    pbs_for_each_layer<B>(
        [&]<size_t layer> [[gnu::always_inline]] (
            std::integral_constant<size_t, layer>) noexcept
        {
            const auto view = pbs_layer_view<layer>(bits);
            if constexpr (layer == 0)
            {
                removed = bsv_get(view, v);
            }
            prev_empty = bsv_set_if<false>(view, v, prev_empty) == 0;
            v >>= B::kShift;
        });

    return removed;
}

#pragma once

#include "bitsets/bitset_view/bsv_get.hpp"
#include "bitsets/bitset_view/bsv_set.hpp"
#include "pyramid_bitset/pbs_layer_view.hpp"
#include "pyramid_bitset/pbs_layers.hpp"

template <u32 capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr bool pbs_add_ex(
    const PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    bool added = false;
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            const auto view = pbs_layer_view<layer>(bits);
            if constexpr (layer == 0)
            {
                added = !bsv_get(view, v);
            }
            bsv_set<true>(view, v);
            v >>= B::kShift;
        });
    return added;
}

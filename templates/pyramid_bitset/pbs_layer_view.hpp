#pragma once

#include "bitsets/bitset_view/bitset_view.hpp"
#include "pyramid_bitset/pyramid_bitset.hpp"  // IWYU pragma: export

template <std::size_t layer, u32 capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr auto pbs_layer_view(
    const PyramidBitset<capacity, Word>& bits) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    static_assert(layer < B::kNumLayers);
    constexpr auto extent = layer == 0 ? capacity : B::kLayersSizes[layer - 1];
    return BitsetView<Word, extent>{bits.words + B::offsets[layer]};
}

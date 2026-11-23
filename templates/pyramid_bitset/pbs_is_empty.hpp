#pragma once

#include "pyramid_bitset/pbs_layer_view.hpp"

template <u32 capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr bool pbs_is_empty(
    const PyramidBitset<capacity, Word>& bits) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    return pbs_layer_view<B::kNumLayers - 1>(bits).words[0] == 0;
}

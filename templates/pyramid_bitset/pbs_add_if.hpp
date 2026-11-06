#pragma once

#include "pyramid_bitset/pbs_layers.hpp"
#include "pyramid_bitset/pyramid_bitset.hpp"  // IWYU pragma: export

template <u32 capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_add_if(
    const PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v,
    bool c) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    pbs_for_each_layer<B>(
        [&]<size_t layer> [[gnu::always_inline]] (
            std::integral_constant<size_t, layer>) noexcept
        {
            typename B::ValueType wi = v >> B::kShift;
            bits.words[B::offsets[layer] + wi] |= Word{c} << (v & B::kMask);
            v = wi;
        });
}

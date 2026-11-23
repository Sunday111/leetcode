#pragma once

#include <cassert>

#include "bitsets/bitset_view/bsv_fill.hpp"
#include "empty.hpp"
#include "full.hpp"
#include "pyramid_bitset/pbs_layer_view.hpp"
#include "pyramid_bitset/pbs_layers.hpp"

template <bool value, u32 capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    const PyramidBitset<capacity, Word>& bits,
    size_t end = capacity) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    assert(end <= capacity);
    if (end == 0)
    {
        pbs_layer_view<B::kNumLayers - 1>(bits).words[0] = 0;
        return;
    }
    pbs_for_each_layer<B>(
        [&]<size_t layer> [[gnu::always_inline]] (
            std::integral_constant<size_t, layer>) noexcept
        {
            const auto count = end;
            end = ceil_div<size_t>(end, B::kWordSize);
            BitsetView<Word> prefix{
                pbs_layer_view<layer>(bits).words,
                end * B::kWordSize};
            bsv_fill<value>(prefix);
            if constexpr (value)
            {
                constexpr Word max_word = static_cast<Word>(~Word{});
                prefix.words[end - 1] &=
                    max_word >> ((size_t{0} - count) & B::kMask);
            }
        });
}

template <u32 capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    const PyramidBitset<capacity, Word>& bits,
    FullType,
    size_t end = capacity) noexcept
{
    pbs_initialize<true>(bits, end);
}

template <u32 capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    const PyramidBitset<capacity, Word>& bits,
    EmptyType,
    size_t end = capacity) noexcept
{
    pbs_initialize<false>(bits, end);
}

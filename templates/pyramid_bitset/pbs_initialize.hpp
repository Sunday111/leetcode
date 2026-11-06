#pragma once

#include <algorithm>
#include <cassert>
#include <limits>

#include "empty.hpp"
#include "full.hpp"
#include "pyramid_bitset/pbs_layers.hpp"
#include "pyramid_bitset/pyramid_bitset.hpp"  // IWYU pragma: export

template <bool value, u32 capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    const PyramidBitset<capacity, Word>& bits,
    size_t end = capacity) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    assert(end <= capacity);
    if (end == 0)
    {
        bits.words[B::offsets[B::kNumLayers - 1]] = 0;
        return;
    }
    constexpr auto m = value ? ~Word{} : Word{};
    pbs_for_each_layer<B>(
        [&]<size_t layer> [[gnu::always_inline]] (
            std::integral_constant<size_t, layer>) noexcept
        {
            const auto count = end;
            end = ceil_div<size_t>(end, B::kWordSize);
            std::fill_n(bits.words + B::offsets[layer], end, m);
            if constexpr (value)
            {
                bits.words[B::offsets[layer] + end - 1] &=
                    std::numeric_limits<Word>::max() >>
                    ((size_t{0} - count) & B::kMask);
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

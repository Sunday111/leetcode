#pragma once

#include <algorithm>
#include <iterator>

#include "empty.hpp"
#include "full.hpp"
#include "pyramid_bitset/pbs_layers.hpp"
#include "pyramid_bitset/pyramid_bitset.hpp"  // IWYU pragma: export

template <bool value, size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    PyramidBitset<capacity, Word>& bits,
    size_t end = capacity) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    constexpr auto m = value ? ~Word{} : Word{};
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            end = ceil_div<size_t>(end, B::kWordSize);
            std::fill_n(
                std::next(bits.words.begin(), B::offsets[layer]),
                end,
                m);
        });
}

template <size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    PyramidBitset<capacity, Word>& bits,
    FullType,
    size_t end = capacity) noexcept
{
    pbs_initialize<true>(bits, end);
}

template <size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    PyramidBitset<capacity, Word>& bits,
    EmptyType,
    size_t end = capacity) noexcept
{
    pbs_initialize<false>(bits, end);
}

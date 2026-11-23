#pragma once

#include <cstddef>
#include <limits>

#include "bitsets/bitset_view/bitset_view.hpp"  // IWYU pragma: export

template <BitsetWord Word, std::size_t extent>
[[nodiscard, gnu::always_inline]] constexpr bool bsv_get(
    BitsetView<Word, extent> bits,
    std::size_t index) noexcept
{
    constexpr auto width = std::numeric_limits<Word>::digits;
    return (bits.words[index / width] >> (index % width)) & 1;
}

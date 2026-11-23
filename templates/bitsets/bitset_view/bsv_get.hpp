#pragma once

#include <cstddef>

#include "bitsets/bitset_view/bitset_view.hpp"  // IWYU pragma: export

template <BitsetWord Word, std::size_t extent>
[[nodiscard, gnu::always_inline]] constexpr bool bsv_get(
    BitsetView<Word, extent> bits,
    std::size_t index) noexcept
{
    constexpr auto width = sizeof(Word) * 8;
    return (bits.words[index / width] >> (index % width)) & 1;
}

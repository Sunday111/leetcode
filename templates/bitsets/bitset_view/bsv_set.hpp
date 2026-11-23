#pragma once

#include <cstddef>
#include <limits>
#include <type_traits>

#include "bitsets/assign_bits.hpp"
#include "bitsets/bitset_view/bitset_view.hpp"  // IWYU pragma: export

template <bool value, BitsetWord Word, std::size_t extent>
    requires(!std::is_const_v<Word>)
[[gnu::always_inline]] constexpr void bsv_set(
    BitsetView<Word, extent> bits,
    std::size_t index) noexcept
{
    constexpr auto width = std::numeric_limits<Word>::digits;
    auto& word = bits.words[index / width];
    const Word mask = static_cast<Word>(Word{1} << (index % width));
    word = assign_bits<value>(word, mask);
}

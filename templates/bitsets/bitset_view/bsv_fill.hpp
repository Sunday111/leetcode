#pragma once

#include <cstddef>
#include <limits>
#include <type_traits>

#include "bitsets/assign_bits.hpp"
#include "bitsets/bitset_view/bitset_view.hpp"  // IWYU pragma: export

template <bool value, BitsetWord Word, std::size_t extent>
    requires(!std::is_const_v<Word>)
[[gnu::always_inline]] constexpr void bsv_fill(
    BitsetView<Word, extent> bits) noexcept
{
    constexpr auto width = std::numeric_limits<Word>::digits;
    constexpr auto max_word = std::numeric_limits<Word>::max();
    const auto full_words = bits.capacity / width;
    const auto tail = bits.capacity % width;
    for (std::size_t i = 0; i != full_words; ++i)
    {
        bits.words[i] = value ? max_word : Word{};
    }
    if (tail)
    {
        const Word mask = static_cast<Word>(max_word >> (width - tail));
        auto& word = bits.words[full_words];
        word = assign_bits<value>(word, mask);
    }
}

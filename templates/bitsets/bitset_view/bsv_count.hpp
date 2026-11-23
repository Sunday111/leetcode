#pragma once

#include <cstddef>

#include "bitsets/bitset_view/bitset_view.hpp"  // IWYU pragma: export
#include "bitsets/popcount.hpp"

template <BitsetWord Word, std::size_t extent>
[[nodiscard, gnu::always_inline]] constexpr std::size_t bsv_count(
    BitsetView<Word, extent> bits) noexcept
{
    constexpr auto width = sizeof(Word) * 8;
    constexpr auto max_word = static_cast<Word>(~Word{});
    const auto full_words = bits.capacity / width;

    std::size_t count = 0;
    for (std::size_t i = 0; i != full_words; ++i)
    {
        count += static_cast<std::size_t>(::popcount(bits.words[i]));
    }
    if (const auto tail = bits.capacity % width; tail)
    {
        const Word mask = static_cast<Word>(max_word >> (width - tail));
        count += static_cast<std::size_t>(
            ::popcount(static_cast<Word>(bits.words[full_words] & mask)));
    }
    return count;
}

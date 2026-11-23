#pragma once

#include <cstddef>
#include <type_traits>

#include "bitsets/assign_bits.hpp"
#include "bitsets/bitset_view/bitset_view.hpp"  // IWYU pragma: export

template <bool value, BitsetWord Word, std::size_t extent>
    requires(!std::is_const_v<Word>)
[[gnu::always_inline]] constexpr Word bsv_set_if(
    BitsetView<Word, extent> bits,
    std::size_t index,
    bool condition) noexcept
{
    constexpr auto width = sizeof(Word) * 8;
    auto& word = bits.words[index / width];
    const Word mask = static_cast<Word>(Word{condition} << (index % width));
    word = assign_bits<value>(word, mask);
    return word;
}

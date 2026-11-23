#pragma once

#include "bitsets/bitset_word.hpp"

template <BitsetWord Word>
[[nodiscard, gnu::always_inline]] constexpr int popcount(Word word) noexcept
{
    return __builtin_popcountg(word);  // NOLINT
}

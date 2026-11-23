#pragma once

#include "bitsets/bitset_word.hpp"

template <BitsetWord Word>
[[nodiscard, gnu::always_inline]] constexpr int ctl_zero(Word word) noexcept
{
    constexpr int width = sizeof(Word) * 8;
    return __builtin_clzg(word, width);  // NOLINT
}

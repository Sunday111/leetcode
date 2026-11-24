#pragma once

#include "bitsets/bitset_word.hpp"
#include "integral_aliases.hpp"

template <BitsetWord Word>
[[nodiscard, gnu::always_inline]] constexpr u32 ctl_zero(Word word) noexcept
{
    constexpr int width = sizeof(Word) * 8;
    return static_cast<u32>(__builtin_clzg(word, width));  // NOLINT
}

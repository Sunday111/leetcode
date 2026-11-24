#pragma once

#include "bitsets/bitset_word.hpp"
#include "integral_aliases.hpp"

template <BitsetWord Word>
    requires(sizeof(Word) == 1)
[[nodiscard, gnu::always_inline]] constexpr Word bswap(Word word) noexcept
{
    return word;
}

template <BitsetWord Word>
    requires(sizeof(Word) == 2)
[[nodiscard, gnu::always_inline]] constexpr Word bswap(Word word) noexcept
{
    return __builtin_bswap16(word);
}

template <BitsetWord Word>
    requires(sizeof(Word) == 4)
[[nodiscard, gnu::always_inline]] constexpr Word bswap(Word word) noexcept
{
    return __builtin_bswap32(word);
}

template <BitsetWord Word>
    requires(sizeof(Word) == 8)
[[nodiscard, gnu::always_inline]] constexpr Word bswap(Word word) noexcept
{
    return __builtin_bswap64(word);
}

template <BitsetWord Word>
    requires(sizeof(Word) == 16)
[[nodiscard, gnu::always_inline]] constexpr Word bswap(Word word) noexcept
{
    const auto low = static_cast<u64>(word);
    const auto high = static_cast<u64>(word >> 64);
    return (Word{bswap(low)} << 64) | bswap(high);
}

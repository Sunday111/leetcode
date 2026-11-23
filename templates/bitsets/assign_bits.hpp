#pragma once

template <bool value, typename Word>
[[nodiscard, gnu::always_inline]] constexpr Word assign_bits(
    Word word,
    Word mask) noexcept
{
    if constexpr (value)
    {
        return static_cast<Word>(word | mask);
    }
    else
    {
        return static_cast<Word>(word & ~mask);
    }
}

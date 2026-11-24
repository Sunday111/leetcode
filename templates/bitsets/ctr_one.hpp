#pragma once

#include "bitsets/ctr_zero.hpp"
#include "integral_aliases.hpp"

template <BitsetWord Word>
[[nodiscard, gnu::always_inline]] constexpr u32 ctr_one(Word word) noexcept
{
    return ::ctr_zero(static_cast<Word>(~word));
}

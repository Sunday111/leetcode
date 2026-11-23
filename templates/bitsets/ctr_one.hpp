#pragma once

#include "bitsets/ctr_zero.hpp"

template <BitsetWord Word>
[[nodiscard, gnu::always_inline]] constexpr int ctr_one(Word word) noexcept
{
    return ::ctr_zero(static_cast<Word>(~word));
}

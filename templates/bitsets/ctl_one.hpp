#pragma once

#include "bitsets/ctl_zero.hpp"

template <BitsetWord Word>
[[nodiscard, gnu::always_inline]] constexpr int ctl_one(Word word) noexcept
{
    return ::ctl_zero(static_cast<Word>(~word));
}

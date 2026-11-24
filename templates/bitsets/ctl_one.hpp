#pragma once

#include "bitsets/ctl_zero.hpp"
#include "integral_aliases.hpp"

template <BitsetWord Word>
[[nodiscard, gnu::always_inline]] constexpr u32 ctl_one(Word word) noexcept
{
    return ::ctl_zero(static_cast<Word>(~word));
}

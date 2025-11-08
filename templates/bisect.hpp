#pragma once

#include <algorithm>

#include "force_inline.hpp"

// Find an iterator to the first
template <typename Range, typename Proj>
[[nodiscard]] FORCE_INLINE constexpr auto bisectFirstFalse(
    Range&& range,
    Proj&& proj) noexcept
{
    return std::ranges::lower_bound(
        std::forward<Range>(range),
        false,
        std::greater{},
        std::forward<Proj>(proj));
}

template <typename Range, typename Proj>
[[nodiscard]] FORCE_INLINE constexpr auto bisectLastTrue(
    Range&& range,
    Proj&& proj) noexcept
{
    return bisectFirstFalse(
               std::forward<Range>(range),
               std::forward<Proj>(proj)) -
           1;
}

#pragma once

#include <algorithm>

// Find an iterator to the first
template <typename Range, typename Proj>
[[nodiscard, gnu::always_inline]] inline constexpr auto bisectFirstFalse(
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
[[nodiscard, gnu::always_inline]] inline constexpr auto bisectLastTrue(
    Range&& range,
    Proj&& proj) noexcept
{
    return bisectFirstFalse(
               std::forward<Range>(range),
               std::forward<Proj>(proj)) -
           1;
}

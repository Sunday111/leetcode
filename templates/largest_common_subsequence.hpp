#pragma once

#include <algorithm>
#include <cassert>
#include <span>

#include "uint_for_value.hpp"

template <
    typename Value,
    u32 max_length,
    typename Index = UintForValue<max_length>>
    requires(std::numeric_limits<Index>::max() >= max_length)
[[nodiscard]] inline constexpr Index lcs_length(
    std::span<Index, max_length * 2> dp,
    std::span<const Value> a,
    std::span<const Value> b) noexcept
{
    // This doesn't change algorithmic complexity
    // but reduces the amount of memory we touch
    if (b.size() > a.size()) std::swap(a, b);

    const Index la = static_cast<Index>(a.size());
    const Index lb = static_cast<Index>(b.size());

    assert(std::min(la, lb) > 0);

    std::fill_n(dp.data(), lb * 2, Index{0});
    auto curr = dp.first(lb);
    auto prev = dp.subspan(lb, lb);

    for (u16 ia = 0; ia != la; ++ia)
    {
        std::swap(curr, prev);

        const Value& ca = a[ia];

        curr[0] = ca == b[0] || prev[0];

        for (u16 ib = 1; ib != lb; ++ib)
        {
            if (ca == b[ib])
            {
                curr[ib] = prev[ib - 1] + 1;
            }
            else
            {
                curr[ib] = std::max(curr[ib - 1], prev[ib]);
            }
        }
    }

    return curr[lb - 1];
}

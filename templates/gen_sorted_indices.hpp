#pragma once

#include <algorithm>
#include <concepts>
#include <ranges>

template <
    std::random_access_iterator It,
    std::unsigned_integral I,
    typename Comp = std::ranges::less,
    typename Proj = std::identity>
    requires std::sortable<It, Comp, Proj>
[[gnu::always_inline]]
void gen_sorted_indices(
    It begin,
    It end,
    I* out,
    Comp comp = {},
    Proj proj = {}) noexcept
{
    I n = static_cast<I>(std::distance(begin, end));
    std::ranges::copy(std::views::iota(I{}, n), out);
    std::ranges::sort(
        out,
        out + n,
        comp,
        [&] [[gnu::always_inline]] (I i)
        { return std::invoke(proj, begin[i]); });
}

template <
    std::ranges::random_access_range Range,
    std::unsigned_integral I,
    typename Comp = std::ranges::less,
    typename Proj = std::identity>
    requires std::sortable<std::ranges::iterator_t<Range>, Comp, Proj>
[[gnu::always_inline]]
void gen_sorted_indices(
    Range&& range,
    I* out,
    Comp comp = {},
    Proj proj = {}) noexcept
{
    gen_sorted_indices(std::begin(range), std::end(range), out, comp, proj);
}

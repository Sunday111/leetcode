#pragma once

#include <algorithm>
#include <utility>

#include "force_inline.hpp"

// Returns new end
template <typename ForwardIt, typename UnaryPredicate>
[[nodiscard]] FORCE_INLINE static constexpr ForwardIt
unstable_remove_if(ForwardIt begin, ForwardIt end, UnaryPredicate p) noexcept
{
    while (begin != end)
    {
        if (p(*begin))
        {
            do
            {
                if (--end == begin) return begin;
            } while (p(*end));
            std::iter_swap(begin, end);
        }
        ++begin;
    }
    return end;
}

// Returns new end. Range overload
template <typename Range, typename UnaryPredicate>
[[nodiscard]] FORCE_INLINE static constexpr auto unstable_remove_if(
    Range& range,
    UnaryPredicate&& p) noexcept
{
    return unstable_remove_if(
        std::begin(range),
        std::end(range),
        std::forward<UnaryPredicate>(p));
}

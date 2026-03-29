#pragma once

#include <algorithm>

inline static constexpr auto all_equal_to =
    [] [[nodiscard, gnu::always_inline]] (
        std::ranges::input_range auto&& rng,
        auto&& value) noexcept
{
    return std::ranges::all_of(
        rng,
        [&] [[gnu::always_inline]] (const auto& x) { return x == value; });
};

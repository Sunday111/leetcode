#pragma once

#include <concepts>
#include <utility>
#include <vector>

#include "max2.hpp"

template <std::integral T>
[[nodiscard, gnu::always_inline, gnu::hot]] inline constexpr T
iif(bool c, T a, T b) noexcept
{
    return (a & static_cast<T>(-c)) + (b & static_cast<T>(~static_cast<T>(-c)));
}

class Solution
{
public:
    [[nodiscard]] static constexpr int longestSubarray(
        const std::vector<int>& nums) noexcept
    {
        int l0 = 0, l1 = 0, r = 0;
        for (int v : nums)
        {
            l0 = iif(v, l0, l1);
            l1 = iif(v, l1 + 1, 0);
            r = max2(r, l0 + l1);
        }

        return r - std::cmp_equal(l1, nums.size());
    }
};

#pragma once

#include <concepts>
#include <utility>
#include <vector>

#define HOT_PATH __attribute__((hot))
#define FORCE_INLINE inline __attribute__((always_inline))

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & static_cast<T>(-c)) + (b & static_cast<T>(~static_cast<T>(-c)));
}

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T int_max(T a, T b) noexcept
{
    return iif(a > b, a, b);
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
            r = int_max(r, l0 + l1);
        }

        return r - std::cmp_equal(l1, nums.size());
    }
};

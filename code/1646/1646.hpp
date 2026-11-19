#pragma once

#include <algorithm>
#include <array>
#include <span>

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] static constexpr u8 getMaximumGenerated(u8 n) noexcept
    {
        if (n < 2) return n;

        const u8 t = n + 1;
        std::array<u8, 101> num_vals;  // NOLINT
        std::span<u8> nums = std::span{num_vals}.subspan(0, t);
        nums[0] = 0, nums[1] = 1;

        const u8 last = (t / 2) + 1;
        for (u8 i = 1; i != last; ++i)
        {
            const u8 a = 2 * i, b = a + 1;
            if (a < t) nums[a] = nums[i];
            if (b < t) nums[b] = nums[i] + nums[i + 1];
        }

        return *std::ranges::max_element(nums);
    }
};

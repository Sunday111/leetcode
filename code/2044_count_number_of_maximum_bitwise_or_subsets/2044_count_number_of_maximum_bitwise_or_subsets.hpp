#pragma once

#include <span>
#include <vector>

class Solution
{
public:
    int target = 0;
    uint8_t n = 0;
    std::span<int> nums;

    uint16_t dfs(uint8_t i, int acc)
    {
        if (acc == target) return (1 << (n - i)) & 0xFFFF;
        if (i == n) return 0;
        return dfs(i + 1, acc) + dfs(i + 1, acc | nums[i]);
    }

    [[nodiscard]] constexpr int countMaxOrSubsets(
        std::vector<int>& nums_) noexcept
    {
        nums = nums_;
        n = nums.size() & 0xFF;
        for (int v : nums) target |= v;

        return dfs(0, 0);
    }
};

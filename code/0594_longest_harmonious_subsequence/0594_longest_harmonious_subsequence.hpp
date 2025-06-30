#pragma once

#include <algorithm>
#include <unordered_map>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int findLHS(std::vector<int>& nums) noexcept
    {
        static std::unordered_map<int, int> freq;
        freq.clear();
        freq.reserve(10'000);
        for (int v : nums) freq[v] += 1;

        int max = 0;
        for (auto& [v, cnt] : freq)
        {
            if (auto it = freq.find(v + 1); it != freq.end())
            {
                max = std::max(max, cnt + it->second);
            }
        }

        return max;
    }
};

class Solution2
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr u32 findLHS(std::vector<int>& nums) noexcept
    {
        std::ranges::sort(nums);
        u32 l = 0, r = 0, ans = 0, n = static_cast<u32>(nums.size());
        while (r < n)
        {
            int d = nums[r] - nums[l];
            ans = std::max(ans, (d == 1) * (r - l + 1));
            ++*(d > 1 ? &l : &r);
        }
        return ans;
    }
};

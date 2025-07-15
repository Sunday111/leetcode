#pragma once

#include <unordered_set>

#include "integral_aliases.hpp"
#include "radix_sorter.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr int longestConsecutive(
        std::vector<int>& nums) noexcept
    {
        radix_sort<int, SortOrder::Ascending, 8>(nums);

        if (nums.empty()) return 0;

        int max_len = 1;
        int len = 1;
        int prev = nums.front();

        const u32 n = static_cast<u32>(nums.size());
        for (u32 i = 1; i != n; ++i)
        {
            auto v = nums[i];
            if (v == prev) continue;
            if (v == prev + 1)
            {
                ++len;
            }
            else
            {
                len = 1;
            }
            prev = v;
            max_len = std::max(max_len, len);
        }

        return max_len;
    }
};

class Solution2
{
public:
    static int longestConsecutive(std::vector<int>& nums) noexcept
    {
        if (nums.empty()) return 0;

        std::unordered_set<int> s{nums.begin(), nums.end()};

        int n = static_cast<int>(nums.size()), longest = 1, handled = 0;

        for (int v : s)
        {
            if (s.find(v - 1) == s.end())
            {
                int l = 1;

                while (s.find(++v) != s.end()) ++l;

                handled += l;
                if (l > longest)
                {
                    longest = l;
                }

                // Impossible to find longer sequence
                if (n <= longest + handled)
                {
                    break;
                }
            }
        }

        return longest;
    }
};

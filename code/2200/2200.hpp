#pragma once

#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr std::vector<int>
    findKDistantIndices(const std::vector<int>& nums, int key, u32 k) noexcept
    {
        std::vector<int> r;

        u32 n = static_cast<u32>(nums.size());
        r.reserve(n);

        u32 i = 0, j = 0;
        while ((i = j) != n)
        {
            while (i != n && nums[i] != key) ++i;
            if (i == n) break;
            if (j + k < i) j = i - k;

            u32 end = std::min(i + k + 1, n);
            while (j != end)
            {
                if (nums[j] == key)
                {
                    end = std::min(j + k + 1, n);
                }
                r.push_back(std::bit_cast<int>(j));
                ++j;
            }
        }

        return r;
    }
};

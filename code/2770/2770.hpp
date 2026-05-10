#include <vector>

#include "cast.hpp"
#include "int_if.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    int maximumJumps(std::vector<int>& nums, int target)
    {
        auto n = cast<u32>(nums.size());
        int dp[1000];
        std::fill_n(dp + 1, n - 1, -1);

        for (u32 i = 0; i != n; ++i)
        {
            int t = dp[i] + 1;
            if (!t) continue;

            for (u32 j = i + 1; j < n; ++j)
            {
                bool b = std::abs(nums[j] - nums[i]) <= target;
                dp[j] = iif(b, std::max(dp[j], t), dp[j]);
            }
        }

        return dp[n - 1];
    }
};

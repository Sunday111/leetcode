#include <array>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    int longestArithSeqLength(std::vector<int>& nums)
    {
        int longest = 2;
        static std::array<std::array<int, 1001>, 1001> dp;

        for (u32 i = 0; i != nums.size(); ++i)
        {
            dp[i].fill(1);
            for (u32 j = 0; j != i; ++j)
            {
                u32 diff = static_cast<u32>(500 + nums[i] - nums[j]);
                dp[i][diff] = dp[j][diff] + 1;
                longest = std::max(longest, dp[i][diff]);
            }
        }

        return longest;
    }
};

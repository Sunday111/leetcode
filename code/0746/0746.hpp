#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int minCostClimbingStairs(
        std::vector<int>& cost) noexcept
    {
        auto n = static_cast<unsigned>(cost.size());
        int dp[1003];
        dp[n + 1] = dp[n] = 0;

        for (unsigned i = n; i--;)
        {
            dp[i] = std::min(dp[i + 1], dp[i + 2]) + cost[i];
        }

        return std::min(dp[0], dp[1]);
    }
};

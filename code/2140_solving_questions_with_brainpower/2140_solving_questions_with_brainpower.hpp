#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    using u64 = uint64_t;

    [[nodiscard]] static u64 mostPoints(
        std::vector<std::vector<int>>& questions) noexcept
    {
        auto& q = reinterpret_cast<std::vector<std::vector<u32>>&>(questions);
        const u32 n = static_cast<u32>(questions.size());
        u64 dp[100'001];
        dp[n] = 0;

        for (u32 i = n; --i != 0xFFFFFFFF;)
        {
            dp[i] =
                std::max(dp[i + 1], dp[std::min(i + q[i][1] + 1, n)] + q[i][0]);
        }

        return dp[0];
    }
};

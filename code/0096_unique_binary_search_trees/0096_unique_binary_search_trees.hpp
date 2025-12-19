#include <algorithm>
#include <array>
#include <cstdint>

class Solution
{
public:
    using u32 = uint32_t;
    static constexpr auto kResult = []
    {
        std::array<std::array<u32, 21>, 21> dp{};
        for (auto& x : dp) std::ranges::fill(x, 1u);

        for (u32 n = 2; n != 20; ++n)
        {
            for (u32 s = n; s >= 1; --s)
            {
                dp[n][s] = 0;
                for (u32 i = n; i >= s; --i)
                {
                    dp[n][s] += dp[i - 1][s] * dp[n][i + 1];
                }
            }
        }

        std::array<u32, 20> ans;  // NOLINT
        for (u32 x = 0; x != 20; ++x) ans[x] = dp[x][1];
        return ans;
    }();

    static constexpr u32 numTrees(u32 n) noexcept { return kResult[n]; }
};

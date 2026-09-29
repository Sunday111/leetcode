#include <bitset>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    bool hasValidPath(const std::vector<std::vector<char>>& g) const noexcept
    {
        const u32 w = static_cast<u32>(g[0].size());
        std::bitset<128> dp[101]{};
        dp[1] = 1u;
        for (auto& row : g)
        {
            for (u32 x = 0; x != w; ++x)
            {
                auto p = dp[x] | dp[x + 1];
                dp[x + 1] = std::array{p << 1, p >> 1}[row[x] & 1];
            }
        }
        return dp[w][0];
    }
};

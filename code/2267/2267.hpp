#include <bitset>
#include <vector>

class Solution
{
public:
    bool hasValidPath(const std::vector<std::vector<char>>& g) const noexcept
    {
        const size_t w = g[0].size();
        // impossible paths
        if ((g[0][0] == ')') || (g.back().back() == '(')) return false;

        // paths with odd lengths
        if ((g.size() + w - 1) & 1) return false;

        std::bitset<128> dp[101]{};
        dp[1] = 1u;
        for (auto& row : g)
        {
            for (size_t x = 0; x != w; ++x)
            {
                auto p = dp[x] | dp[x + 1];
                dp[x + 1] = std::array{p << 1, p >> 1}[row[x] & 1];
            }
        }
        return dp[w][0];
    }
};

#include <algorithm>
#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    static u16 findMaxForm(
        const std::vector<std::string>& strs,
        u8 max_zeroes,
        u8 max_ones) noexcept
    {
        static u16 dp[101][101];
        for (u8 z = 0; z <= max_zeroes; ++z)
        {
            std::fill_n(dp[z], max_ones + 1, 0);
        }

        for (auto& s : strs)
        {
            u8 ones = std::ranges::count(s, '1') & 0xFF;
            u8 zeroes = (s.size() - ones) & 0xFF;
            for (u8 z = max_zeroes; z >= zeroes && z != 0xFF; --z)
            {
                for (u8 o = max_ones; o >= ones && o != 0xFF; --o)
                {
                    u16 v = 1 + dp[z - zeroes][o - ones];
                    if (v > dp[z][o]) dp[z][o] = v;
                }
            }
        }

        return dp[max_zeroes][max_ones];
    }
};

#include "sync_stdio.hpp"

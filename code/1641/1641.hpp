// https://leetcode.com/problems/count-sorted-vowel-strings/

#include <array>

#include "integral_aliases.hpp"

class Solution
{
public:
    inline static constexpr auto Ans = []
    {
        std::array<std::array<u32, 6>, 51> dp{};
        dp[0].fill(1);

        for (u8 i = 1; i != dp.size(); ++i)
        {
            for (u8 j = 1; j != 6; ++j)
            {
                for (u8 k = 0; k != j; ++k)
                {
                    dp[i][j] += dp[i - 1][j - k];
                }
            }
        }

        return dp;
    }();

    [[nodiscard]] constexpr u32 countVowelStrings(u8 n) const noexcept
    {
        return Ans[n][5];
    }
};

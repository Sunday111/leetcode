
#include <algorithm>
#include <string_view>

#include "cast.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    inline static u16 dp[1000][1000];
    std::string_view a, b;
    u16 la, lb;

    [[nodiscard]] u16 dfs(u16 start_a, u16 start_b) noexcept
    {
        if (start_a == la || start_b == lb) return 0;

        auto& r = dp[start_a][start_b];

        if (r == 0xFFFF)
        {
            r = 0;

            if (auto next_b = b.find(a[start_a], start_b); next_b != b.npos)
            {
                r = 1 + dfs(start_a + 1, cast<u16>(next_b + 1));
            }

            r = std::max(r, dfs(start_a + 1, start_b));
        }

        return r;
    }

    [[nodiscard]] u16 longestCommonSubsequence(
        std::string_view a_,
        std::string_view b_) noexcept
    {
        a = a_, b = b_;
        la = cast<u16>(a.size()), lb = cast<u16>(b.size());
        for (u16 ia = 0; ia != la; ++ia) std::fill_n(dp[ia], lb, 0xFFFF);
        return dfs(0, 0);
    }
};

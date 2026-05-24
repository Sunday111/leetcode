#include <algorithm>
#include <numeric>
#include <ranges>
#include <vector>

#include "integral_aliases.hpp"
#include "upd_max.hpp"

class Solution
{
public:
    [[nodiscard]] u16 maxJumps(std::vector<int>& a, u16 d) noexcept
    {
        constexpr u16 max_n = 1000;
        const u16 n = a.size() & 0xFFFF;
        [[assume(n <= max_n)]];

        static u16 srt[max_n], dp[max_n];
        std::iota(srt, srt + n, 0);
        std::ranges::sort(
            srt,
            srt + n,
            std::greater{},
            [&](u16 i) { return a[i]; });
        std::fill_n(dp, n, 1);

        for (u16 i : srt | std::views::take(n))
        {
            [[assume(i < n)]];

            u16 jumps = dp[i] + 1;
            int v = a[i];

            u16 l = i - std::min(i, d);
            for (u16 j = i; j-- != l && a[j] < v;)
            {
                upd_max(dp[j], jumps);
            }

            u16 r = std::min<u16>(i + d + 1, n);
            for (u16 j = i + 1; j != r && a[j] < v; ++j)
            {
                upd_max(dp[j], jumps);
            }
        }

        return std::ranges::max(dp | std::views::take(n));
    }
};

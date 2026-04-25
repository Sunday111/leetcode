#include <algorithm>
#include <integral_aliases.hpp>
#include <ranges>
#include <vector>

#include "cast.hpp"
#include "int_if.hpp"

class Solution
{
public:
    u32 maxDistance(
        const u32 s,
        const std::vector<std::vector<int>>& points,
        const u32 k) noexcept
    {
        static u32 flat[15'001];
        u32 n = 0, p = s * 4;
        for (auto& pt : points)
        {
            u32 x = cast<u32>(pt[0]), y = cast<u32>(pt[1]);
            u32 t = x + y;
            flat[n++] = iif(x == 0 || y == s, p - t, t);
        }

        std::sort(flat, flat + n);
        *(flat + n) = *(flat + n - 1);

        static std::pair<u32, u32> dp[15'001];
        dp[n] = {0, 0};

        return *std::ranges::lower_bound(
            std::views::iota(1u, s + 1) | std::views::reverse,
            true,
            std::less{},
            [&] [[gnu::always_inline]] (u32 d) noexcept -> bool
            {
                u32 i = n - 1, j = n;
                while (true)
                {
                    u32 v = flat[i];

                    if (j != i && flat[j - 1] - v >= d)
                    {
                        --j;
                        continue;
                    }

                    auto& [cnt, last] = dp[i] = dp[j];
                    last = std::max(last, v);
                    ++cnt;

                    if (cnt == k && p + v - last >= d)
                    {
                        return true;
                    }

                    if (!i--) break;
                }

                return false;
            });
    }
};

#include "sync_stdio.hpp"

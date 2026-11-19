#include <algorithm>
#include <numeric>
#include <ranges>
#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    static i64 maxPower(const std::vector<i32>& stations, u32 r, u32 k) noexcept
    {
        const u32 n = static_cast<u32>(stations.size()), d = r * 2 + 1;

        static i64 power[100'001];
        std::fill_n(power, n + 1, 0);

        for (u32 i = 0; i != n; ++i)
        {
            power[(i - r) & ((i < r) - 1)] += stations[i];
            power[std::min(n, i + r + 1)] -= stations[i];
        }

        std::inclusive_scan(power, power + n, power);

        static i64 deltas[100'001];
        auto possible = [&](i64 x)
        {
            std::fill_n(deltas, n + 1, 0);

            u32 can_build = k;
            i64 curr_delta = 0;
            for (u32 i = 0; i != n; ++i)
            {
                curr_delta -= deltas[i];
                if (i64 p = power[i] + curr_delta; p < x)
                {
                    i64 to_build = x - p;
                    if (to_build > can_build) return false;

                    can_build -= to_build;
                    curr_delta += to_build;
                    deltas[std::min(n, i + d)] = to_build;
                }
            }

            return true;
        };

        const i64 min_power = *std::min_element(power, power + n);
        return *std::ranges::lower_bound(
                   std::views::iota(min_power, min_power + k + 1),
                   false,
                   std::greater{},
                   possible) -
               1;
    }
};

#include "sync_stdio.hpp"

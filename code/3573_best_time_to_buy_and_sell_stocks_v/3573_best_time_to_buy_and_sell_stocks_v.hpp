#include <cassert>
#include <vector>

using u8 = uint8_t;
using u32 = uint32_t;
using i64 = int64_t;

class Solution
{
public:
    static constexpr i64 maximumProfit(
        std::vector<int>& prices,
        u32 max_transactions) noexcept
    {
        u32 n = static_cast<u32>(prices.size());
        u32 last_idx = n - 1;

        static i64 dp[3][1000][501];
        constexpr auto kBad = -1'000'000'000'000;
        for (u8 j = 0; j != 3; ++j)
        {
            for (u32 i = 0; i != n; ++i)
            {
                std::fill_n(dp[j][i], max_transactions + 1, kBad);
            }
        }

        constexpr int kFlat = 0, kLong = 1, kShrt = 2;

        auto dfs = [&](auto& f, u8 s, u32 i, u32 k) -> i64
        {
            if (k == 0) assert(s == kFlat);
            if (i == n || k == 0) return 0;
            if (i == last_idx)
            {
                switch (s)
                {
                case kLong:
                    return prices[i];
                case kShrt:
                    return -prices[i];
                default:
                    return 0;
                }
            }

            auto& r = dp[s][i][k];
            if (r == kBad)
            {
                r = f(f, s, i + 1, k);

                if (s == kFlat)
                {
                    r = std::max(r, f(f, kLong, i + 1, k) - i64{prices[i]});
                    r = std::max(r, f(f, kShrt, i + 1, k) + i64{prices[i]});
                }
                else
                {
                    auto fut = f(f, kFlat, i + 1, k - 1);
                    fut += s == kLong ? i64{prices[i]} : -i64{prices[i]};
                    r = std::max(r, fut);
                }
            }

            return r;
        };

        return dfs(dfs, kFlat, 0, max_transactions);
    }
};

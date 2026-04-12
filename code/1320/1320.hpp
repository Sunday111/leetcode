#include <algorithm>
#include <ranges>
#include <string>

#include "integral_aliases.hpp"
#include "upd_min.hpp"

class Solution
{
public:
    inline static u32 dist[26][26];

    inline static auto _init_ = []
    {
        for (u8 i = 0; i != 26; ++i)
        {
            u8 ix = i % 6, iy = i / 6;
            for (u8 j = 0; j != 26; ++j)
            {
                u8 jx = j % 6, jy = j / 6;
                dist[i][j] = (std::max(ix, jx) - std::min(ix, jx)) +
                             (std::max(iy, jy) - std::min(iy, jy));
            }
        }
        return 'a';
    }();

    u32 minimumDistance(std::string& word) const noexcept
    {
        u32 dp[2][26][26]{};

        bool f = false;

        u8 j = (word[0] - 'A') & 0xFF;

        for (char c : word | std::views::drop(1))
        {
            const u8 k = (c - 'A') & 0xFF;
            u32 dj = dist[j][k];

            f = !f;

            for (u8 i = 0; i != 26; ++i)
            {
                for (u8 jj = 0; jj != 26; ++jj)
                {
                    dp[f][i][jj] = 100'000;
                }
            }

            for (u8 i = 0; i != 26; ++i)
            {
                u32 di = dist[k][i];

                upd_min(dp[f][k][j], dp[!f][i][j] + di);
                upd_min(dp[f][k][i], dp[!f][j][i] + dj);
                upd_min(dp[f][i][k], dp[!f][i][j] + dj);
                upd_min(dp[f][j][k], dp[!f][j][i] + di);
            }
            j = k;
        }

        u32 r = 100'000;

        u8 k = (*(word.rbegin()) - 'A') & 0xFF;
        j = (*(word.rbegin() + 1) - 'A') & 0xFF;

        for (u8 i = 0; i != 26; ++i)
        {
            upd_min(r, dp[f][k][j]);
            upd_min(r, dp[f][k][i]);
            upd_min(r, dp[f][i][k]);
            upd_min(r, dp[f][j][k]);
        }

        return r;
    }
};

#include "sync_stdio.hpp"

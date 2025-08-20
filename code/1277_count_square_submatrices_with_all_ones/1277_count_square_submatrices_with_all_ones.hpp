#pragma once

#include <numeric>
#include <vector>

class Solution
{
public:
    using u16 = uint16_t;
    [[nodiscard]] constexpr static int countSquares(
        std::vector<std::vector<int>>& m) noexcept
    {
        const u16 h = m.size() & 0xFFFF, w = m[0].size() & 0xFFFF;
        int r = std::accumulate(m[0].begin(), m[0].end(), 0);
        for (u16 y = 1; y != h; ++y)
        {
            auto& prev_row = m[y - 1];
            auto& row = m[y];
            r += row[0];
            for (u16 x = 1; x != w; ++x)
            {
                int& v = row[x];
                int a = row[x - 1], b = prev_row[x], c = prev_row[x - 1];
                v += v * std::min({a, b, c});
                r += v;
            }
        }

        return r;
    }
};

#pragma once

#include <numeric>
#include <vector>

#include "integral_aliases.hpp"
#include "to.hpp"

class Solution
{
public:
    static std::vector<std::vector<int>> rangeAddQueries(
        u32 n,
        std::vector<std::vector<int>>& queries)
    {
        std::vector<std::vector<int>> t(n + 1);
        for (auto& r : t)
        {
            r.resize(n + 1, 0);
        }

        for (auto& q : queries)
        {
            u32 y0 = to<u32>(q[0]);
            u32 x0 = to<u32>(q[1]);
            u32 y1 = to<u32>(q[2] + 1);
            u32 x1 = to<u32>(q[3] + 1);
            ++t[y0][x0];
            --t[y0][x1];
            --t[y1][x0];
            ++t[y1][x1];
        }

        for (u32 y = 0; y != n; ++y)
        {
            auto& r = t[y];
            r.resize(n);
            std::inclusive_scan(r.begin(), r.end(), r.begin());
        }

        for (u32 y = 1; y != n; ++y)
        {
            auto &r = t[y], &pr = t[y - 1];
            for (u32 x = 0; x != n; ++x) r[x] += pr[x];
        }

        t.resize(n);
        return t;
    }
};

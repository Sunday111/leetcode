#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] inline static constexpr auto xy(
        const std::vector<int>& v) noexcept
    {
        return std::make_tuple(v[0], v[1]);
    }

    using u32 = uint32_t;
    [[nodiscard]] static constexpr double largestTriangleArea(
        const std::vector<std::vector<int>>& p) noexcept
    {
        int r = 0;
        auto n = static_cast<u32>(p.size());
        for (u32 i = 0; i != n; ++i)
        {
            auto [xi, yi] = xy(p[i]);
            for (u32 j = i + 1; j != n; ++j)
            {
                auto [xj, yj] = xy(p[j]);
                for (u32 k = j + 1; k != n; ++k)
                {
                    auto [xk, yk] = xy(p[k]);
                    r = std::max(
                        r,
                        std::abs(
                            xi * (yj - yk) + xj * (yk - yi) + xk * (yi - yj)));
                }
            }
        }
        return static_cast<double>(r) / 2;
    }
};

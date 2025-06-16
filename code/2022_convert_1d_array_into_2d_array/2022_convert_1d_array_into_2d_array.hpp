#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr auto
    construct2DArray(std::vector<int>& original, size_t m, size_t n) noexcept
    {
        std::vector<std::vector<int>> r;

        if (m * n == original.size())
        {
            auto next = original.begin();
            r.resize(m, std::vector<int>(n));
            for (size_t y = 0; y != m; ++y)
            {
                std::copy_n(next, n, r[y].begin());
                std::advance(next, n);
            }
        }

        return r;
    }
};

#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int minNumberOperations(
        std::vector<int>& t) noexcept
    {
        int p = 0, r = 0;

        for (int v : t)
        {
            r += std::max(v - std::exchange(p, v), 0);
        }

        return r;
    }
};

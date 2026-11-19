#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> mostVisited(
        int n,
        const std::vector<int>& rounds)
    {
        std::vector<int> r;
        r.reserve(static_cast<size_t>(n));

        const int s = rounds.front(), f = rounds.back();

        if (s > f)
        {
            for (int i = 1; i <= f; ++i) r.push_back(i);
            for (int i = s; i <= n; ++i) r.push_back(i);
        }
        else if (s < f)
        {
            for (int i = s; i <= f; ++i) r.push_back(i);
        }
        else
        {
            r.push_back(s);
        }

        return r;
    }
};

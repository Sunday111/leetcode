#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr auto sumZero(int n) noexcept
    {
        std::vector<int> r;
        r.reserve(static_cast<size_t>(n));
        for (int i = 1; i != n; ++i) r.emplace_back(i);
        r.emplace_back(-((n - 1) * n) / 2);
        return r;
    }
};

#pragma once

#include <numeric>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int>
    missingRolls(std::vector<int> rolls, int mean, int n) noexcept
    {
        const int m = static_cast<int>(rolls.size());
        const int sum_n =
            mean * (m + n) - std::accumulate(rolls.begin(), rolls.end(), 0);

        if (sum_n < n || sum_n > n * 6) return {};

        const int p = sum_n / n;
        rolls.clear();
        rolls.reserve(static_cast<unsigned>(n));
        rolls.resize(static_cast<unsigned>(sum_n % n), p + 1);
        rolls.resize(static_cast<unsigned>(n), p);
        return rolls;
    }
};

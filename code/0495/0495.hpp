#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int findPoisonedDuration(
        std::vector<int>& timeSeries,
        int duration)
    {
        int total = 0;
        int prev = timeSeries.front();

        for (size_t i = 1; i != timeSeries.size(); ++i)
        {
            int next = timeSeries[i];
            int prev_end = prev + duration;
            total += std::min(next, prev_end) - prev;
            prev = next;
        }

        return total + duration;
    }
};

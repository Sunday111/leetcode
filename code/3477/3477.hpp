#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int numOfUnplacedFruits(
        std::vector<int>& fruits,
        std::vector<int>& baskets) noexcept
    {
        int r = static_cast<int>(fruits.size());
        for (int f : fruits)
        {
            for (int& b : baskets)
            {
                if (b >= f)
                {
                    b = 0;
                    --r;
                    break;
                }
            }
        }

        return r;
    }
};

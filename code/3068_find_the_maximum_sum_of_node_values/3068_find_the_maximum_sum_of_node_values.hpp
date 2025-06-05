#pragma once

#include <optional>
#include <vector>

class Solution
{
public:
    int64_t maximumValueSum(
        std::vector<int>& nums,
        int k,
        [[maybe_unused]] std::vector<std::vector<int>>& edges)
    {
        int64_t sum = 0;
        size_t num_xored = 0;
        std::optional<std::pair<int, int>> worst_positive, best_non_positive;

        for (auto v : nums)
        {
            const int xored = v ^ k;
            const int diff = xored - v;
            if (diff > 0)
            {
                sum += xored;
                ++num_xored;

                if (!worst_positive || worst_positive->second > diff)
                {
                    worst_positive = std::make_pair(v, diff);
                }
            }
            else
            {
                sum += v;

                if (!best_non_positive || best_non_positive->second < diff)
                {
                    best_non_positive = std::make_pair(v, diff);
                }
            }
        }

        if ((num_xored % 2) == 1)
        {
            const int a = worst_positive->first;
            const int xa = a ^ k;
            if (best_non_positive)
            {
                const int b = best_non_positive->first;
                const int xb = b ^ k;

                if ((xa + xb) > (a + b))
                {
                    sum -= b;
                    sum += xb;
                }
                else
                {
                    sum -= xa;
                    sum += a;
                }
            }
            else
            {
                sum -= xa;
                sum += a;
            }
        }

        return sum;
    }
};

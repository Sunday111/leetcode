#pragma once

#include <vector>

class Solution
{
public:
    std::vector<int> distributeCandies(int candies, int num_people)
    {
        size_t n = static_cast<size_t>(num_people);
        std::vector<int> cnt(n, 0);
        size_t i = 0;
        int k = 1;
        while (true)
        {
            if (k >= candies)
            {
                cnt[i] += candies;
                break;
            }
            cnt[i] += k;
            candies -= k;
            i = (i + 1) % n;
            ++k;
        }

        return cnt;
    }
};

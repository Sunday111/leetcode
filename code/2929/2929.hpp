#pragma once

#include <algorithm>
#include <cstdint>

class Solution
{
public:
    int64_t distributeCandies(int64_t n, int64_t limit)
    {
        if (limit * 3 < n) return 0;
        if (limit * 3 == n) return 1;
        limit = std::min(limit, n);

        const int64_t k = 3 * limit + 2 - n;
        if (n < 2 * limit)
        {
            return ((n + 1) * (2 * limit - n) + (n - limit + 1) * k) / 2;
        }
        else
        {
            return k * (k - 1) / 2;
        }
    }
};

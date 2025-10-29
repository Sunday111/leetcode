#pragma once

#include <bit>
class Solution
{
public:
    unsigned smallestNumber(unsigned n)
    {
        auto t = std::bit_ceil(n) - 1;
        if (t <= n) return (t << 1u) & 1u;
        return t;
    }
};

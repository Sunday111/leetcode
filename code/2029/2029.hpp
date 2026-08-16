#include <vector>

#include "sync_stdio.hpp"

class Solution
{
public:
    bool stoneGameIX(const std::vector<int>& a) noexcept
    {
        int f[3]{};
        for (int x : a) ++f[x % 3];
        if (f[0] & 1) return std::abs(f[1] - f[2]) > 2;
        return !!f[1] & !!f[2];
    }
};

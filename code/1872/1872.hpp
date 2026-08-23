#include <numeric>
#include <vector>

#include "sync_stdio.hpp"

class Solution
{
public:
    [[gnu::target("bmi2,avx2")]]
    constexpr int stoneGameVIII(const std::vector<int>& a) noexcept
    {
        int s = std::accumulate(a.begin(), a.end(), 0), hi = s;
        for (size_t i = a.size(); --i != 1;)
        {
            hi = std::max(hi, (s -= a[i]) - hi);
        }
        return hi;
    }
};

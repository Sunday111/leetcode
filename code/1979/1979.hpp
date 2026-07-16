#include <algorithm>
#include <numeric>
#include <vector>

class Solution
{
public:
    int findGCD(const std::vector<int>& a)
    {
        auto [lo, hi] = std::ranges::minmax(a);
        return std::gcd(lo, hi);
    }
};

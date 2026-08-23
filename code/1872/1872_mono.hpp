#include <numeric>
#include <vector>


#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

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

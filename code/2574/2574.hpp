#include <algorithm>
#include <vector>

class Solution
{
public:
    std::vector<int> leftRightDifference(std::vector<int>& a) noexcept
    {
        int l = 0, r = std::ranges::fold_left(a, 0, std::plus{});
        for (int& x : a) x = std::abs(std::exchange(l, l + x) - (r -= x));
        return std::move(a);
    }
};

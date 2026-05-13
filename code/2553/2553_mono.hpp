#include <algorithm>
#include <ranges>
#include <vector>


class Solution
{
public:
    std::vector<int> separateDigits(std::vector<int>& a) noexcept
    {
        std::vector<int> r;
        r.reserve(a.size() * 6);
        for (int x : a | std::views::reverse)
        {
            while (x)
            {
                r.push_back(x % 10);
                x /= 10;
            }
        }
        std::ranges::reverse(r);
        return r;
    }
};

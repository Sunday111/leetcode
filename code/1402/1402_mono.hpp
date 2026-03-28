#include <algorithm>
#include <vector>

// https://leetcode.com/problems/reducing-dishes/


class Solution
{
public:
    [[nodiscard]] constexpr int maxSatisfaction(
        std::vector<int>& satisfaction) const noexcept
    {
        std::ranges::sort(satisfaction, std::ranges::greater{});

        int s = 0, r = 0;

        for (int v : satisfaction)
        {
            s += v;
            if (s < 0) break;
            r += s;
        }

        return r;
    }
};

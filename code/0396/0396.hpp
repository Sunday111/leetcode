#include <ranges>
#include <vector>

class Solution
{
public:
    int maxRotateFunction(const std::vector<int>& nums)
    {
        auto d = nums.data();
        int s = 0, x = 0, n = static_cast<int>(nums.size());
        for (int i = 0; i != n; ++i)
        {
            s += d[i];
            x += i * d[i];
        }

        int r = x;
        for (int v : nums | std::views::take(n - 1))
        {
            x += v * n - s;
            r = std::max(r, x);
        }

        return r;
    }
};

#include <array>
#include <vector>

#include "swap_if_greater.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr int maxSumDivThree(
        const std::vector<int>& nums) noexcept
    {
        int s = 0;

        constexpr auto mi = std::numeric_limits<int>::max();
        std::array<int, 2> m[3]{};
        int n[3]{0, 0, 0};
        m[1].fill(mi), m[2].fill(mi);

        for (int v : nums)
        {
            s += v;
            int mod = v % 3;
            ++n[mod];
            swap_if_greater(v, m[mod][0]);
            swap_if_greater(v, m[mod][1]);
        }

        int mod = s % 3, k = s & -!!mod;
        if (n[1] > 0 && mod == 1) k = std::min(k, m[1][0]);
        if (n[2] > 1 && mod == 1) k = std::min(k, m[2][0] + m[2][1]);
        if (n[1] > 1 && mod == 2) k = std::min(k, m[1][0] + m[1][1]);
        if (n[2] > 0 && mod == 2) k = std::min(k, m[2][0]);
        return s - k;
    }
};

#include "sync_stdio.hpp"

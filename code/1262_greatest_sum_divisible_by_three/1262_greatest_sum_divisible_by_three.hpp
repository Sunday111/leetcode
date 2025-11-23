#include <array>
#include <vector>

#include "int_if.hpp"
#include "update_minima.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr int maxSumDivThree(
        const std::vector<int>& nums) noexcept
    {
        int s = 0;

        int n1{}, n2{};
        constexpr auto mi = std::numeric_limits<int>::max();
        std::array<int, 2> m1{}, m2{};
        m1.fill(mi), m2.fill(mi);

        for (int v : nums)
        {
            s += v;
            int m = v % 3;
            bool b1 = m == 1, b2 = m == 2;
            n1 += v & -b1, n2 += v & -b2;
            update_minima(iif(b1, v, mi), m1);
            update_minima(iif(b2, v, mi), m2);
        }

        int m = s % 3, k = s & -!!m;
        if (n1 > 0 && m == 1) k = std::min(k, m1[0]);
        if (n2 > 1 && m == 1) k = std::min(k, m2[0] + m2[1]);
        if (n1 > 1 && m == 2) k = std::min(k, m1[0] + m1[1]);
        if (n2 > 0 && m == 2) k = std::min(k, m2[0]);
        return s - k;
    }
};

#include "sync_stdio.hpp"

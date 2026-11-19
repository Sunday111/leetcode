#pragma once

#include <vector>

#include "branchless_max.hpp"
#include "int_if.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr int totalFruit(
        const std::vector<int>& fruits) noexcept
    {
        int r = 0;
        int f1 = -1, f2 = -1;
        int l = 0;
        int n1 = 0, n2 = 0;
        for (int f : fruits)
        {
            int p = n1;
            bool c1 = f == f1, c2 = f == f2, c12 = c1 || c2;
            n1 = iif(c1, n2, n1);
            n2 = iif(c1, p, n2);
            f1 = iif(c2, f1, f2);
            f2 = iif(c2, f2, f);
            n1 = iif(c12, n1, l);
            n2 = iif(c12, n2, 0) + 1;
            l = iif(c2, l, 0) + 1;
            r = branchless_max(r, n1 + n2);
        }
        return r;
    }
};

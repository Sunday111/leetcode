#include <vector>

#include "integral_aliases.hpp"
#include "upd_max.hpp"
#include "upd_min.hpp"

class Solution
{
public:
    [[nodiscard]] int findMaxVal(
        u32 n,
        std::vector<std::vector<int>>& rstr,
        const std::vector<int>& diff) noexcept
    {
        static int hi[100001];
        std::fill_n(hi, n, 10'000'000);
        hi[0] = 0;
        for (auto& x : rstr) hi[x[0]] = x[1];

        for (u32 i = 1; i != n; ++i)
        {
            auto& curr_hi = hi[i];
            upd_min(curr_hi, hi[i - 1] + diff[i - 1]);
        }

        int next_hi = hi[n - 1], mv = next_hi;
        for (u32 i = n - 2; i; --i)
        {
            upd_min(next_hi += diff[i], hi[i]);
            upd_max(mv, next_hi);
        }
        return mv;
    }
};

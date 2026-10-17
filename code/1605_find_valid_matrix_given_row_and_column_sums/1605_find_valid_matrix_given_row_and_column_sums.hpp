#include <vector>

#include "integral_aliases.hpp"
#include "pyramid_bitset/pbs_is_empty.hpp"
#include "pyramid_bitset/pbs_min.hpp"
#include "pyramid_bitset/pbs_set.hpp"

class Solution
{
public:
    [[nodiscard]] constexpr auto restoreMatrix(
        const std::vector<int>& row_sum,
        const std::vector<int>& col_sum) const noexcept
    {
        u16 h = row_sum.size() & 0xFFFF, w = col_sum.size() & 0xFFFF;
        PyramidBitset<512> a, b;
        auto src = &a, dst = &b;

        std::vector<std::vector<int>> r;
        r.resize(h);

        auto& last_row = r.back();
        last_row = col_sum;

        for (u16 x = 0; x != w; ++x) pbs_set(*src, x, last_row[x]);

        for (u16 y = 0; y != h - 1; ++y)
        {
            auto& row = r[y];
            row.resize(w, 0);
            auto rs = row_sum[y];

            dst = src;
            while (rs && !pbs_is_empty(*src))
            {
                auto x = pbs_min(*src);
                int& cs = last_row[x];
                int t = row[x] = std::min(rs, cs);
                rs -= t, cs -= t;
                pbs_set(*dst, x, cs);
            }

            std::swap(src, dst);
        }

        return r;
    }
};

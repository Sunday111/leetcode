#include <numeric>
#include <vector>

#include "integral_aliases.hpp"
#include "max4.hpp"
#include "min4.hpp"
#include "namespaces.hpp"  // IWYU pragma: keep
#include "signed_integral_aliases.hpp"
// https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/

class Solution
{
public:
    [[nodiscard]] constexpr i32 maxProductPath(
        const std::vector<std::vector<i32>>& grid) const noexcept
    {
        const u8 h = grid.size() & 0xFF, w = grid[0].size() & 0xFF;
        i64 dp_lo[16], dp_hi[16];

        // first row
        std::inclusive_scan(
            grid[0].begin(),
            grid[0].end(),
            dp_hi,
            std::multiplies{},
            i64{1});
        std::copy_n(dp_hi, w, dp_lo);

        for (u8 y = 1; y != h; ++y)
        {
            auto& row = grid[y];
            dp_hi[0] *= row[0];
            dp_lo[0] *= row[0];

            for (u8 x = 1; x != w; ++x)
            {
                i64 v = row[x];
                i64 a = dp_lo[x - 1] * v;
                i64 b = dp_lo[x] * v;
                i64 c = dp_hi[x - 1] * v;
                i64 d = dp_hi[x] * v;
                dp_hi[x] = max4(a, b, c, d);
                dp_lo[x] = min4(a, b, c, d);
            }
        }

        return static_cast<i32>(max2(dp_hi[w - 1], -1L) % 1'000'000'007);
    }
};

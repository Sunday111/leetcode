#include <algorithm>
#include <vector>

#include "integral_aliases.hpp"
#include "namespaces.hpp"  // IWYU pragma: keep
// https://leetcode.com/problems/equal-sum-grid-partition-i/

class Solution
{
public:
    template <typename T>
    [[nodiscard, gnu::always_inline]] constexpr bool check(
        const std::vector<std::vector<u32>>& g,
        const u32 w,
        const u32 h,
        T* sum_buf) noexcept
    {
        stdr::fill_n(sum_buf, w + h, 0);
        auto rs = sum_buf, cs = rs + h;

        T total{};
        for (u32 y = 0; y != h; ++y)
        {
            auto& row = g[y];
            auto& rsy = rs[y];
            for (u32 x = 0; x != w; ++x)
            {
                auto v = row[x];
                rsy += v;
                cs[x] += v;
            }
            total += rsy;
        }

        if (total & 1) return false;
        T target = total / 2;

        T s = 0;
        for (u32 y = 0; s < target; ++y) s += rs[y];
        if (s == target) return true;

        s = 0;
        for (u32 x = 0; s < target; ++x) s += cs[x];
        return s == target;
    }

    [[nodiscard]] bool canPartitionGrid(
        const std::vector<std::vector<int>>& orig) noexcept
    {
        u32 h = static_cast<u32>(orig.size());
        u32 w = static_cast<u32>(orig[0].size());
        static u64 sum_buf[100'001];
        auto& g = reinterpret_cast<const std::vector<std::vector<u32>>&>(orig);

        if (w * h < 42000)
        {
            return check(g, w, h, reinterpret_cast<u32*>(sum_buf));
        }

        return check(g, w, h, sum_buf);
    }
};

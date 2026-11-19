#include <span>
#include <vector>

#include "radix_sorter.hpp"

class Solution
{
public:
    static constexpr u32 kMOD = 1'000'000'007;
    u32 countTrapezoids(std::vector<std::vector<int>>& points)
    {
        // Sort ascending by Y
        std::array<u32, 100'001> a;  // NOLINT
        for (u32 i = 0; i != points.size(); ++i)
        {
            a[i] = static_cast<u32>(points[i][1] + 100000000);
        }

        radix_sort<8, 4>(std::span{a}.first(points.size()));

        // All points are unique, so do no care about actual x positions
        // - just the number of them witin the same y
        u32 py = 0xFFFFFFFF, n = 0xFFFFFFFF;
        for (u32 i = 0; i != points.size(); ++i)
        {
            u32 y = a[i], b = y == std::exchange(py, y);
            n += !b;
            a[n] = (a[n] & (!b - 1)) + 1;
        }

        ++n;

        u64 r = 0, s = (a[0] * (a[0] - 1)) / 2;
        for (u32 i = 1; i != n; ++i)
        {
            u64 k = (u64{a[i]} * u64{a[i] - 1}) / 2;
            r += k * s, r %= kMOD;
            s += k;
        }

        return static_cast<u32>(r);
    }
};

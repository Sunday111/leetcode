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
            u32 y = a[i], b = y != std::exchange(py, y);
            n += b;
            a[n] = (a[n] & (b - 1)) + 1;
        }

        ++n;

        u64 s = 0, s2 = 0;
        for (u32 i = 0; i != n; ++i)
        {
            u64 f = a[i];
            u64 z = (f * (f - 1)) / 2;
            s += z;
            s2 += z * z;
        }

        return ((s * s - s2) / 2) % kMOD;
    }
};

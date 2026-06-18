#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    std::vector<double> sampleStats(std::vector<int>& freq) noexcept
    {
        const auto f = reinterpret_cast<const u32*>(freq.data());
        u64 s = 0;
        u32 lo = 256, hi = 0, mode = 0, n = 0;
        for (u32 i = 0; i != 256; ++i)
        {
            if (f[i])
            {
                lo = std::min(lo, i);
                hi = i;
            }
            if (f[mode] < f[i])
            {
                mode = i;
            }
            n += f[i];
            s += f[i] * i;
        }

        // find left and right value for median
        bool odd_n = n & 1;
        u32 n2 = n / 2, l = 0, ls = f[l];
        while (ls < n2) ls += f[++l];
        u32 r = l;
        while (ls <= n2) ls += f[++r];
        if (odd_n) l = r;

        return {
            static_cast<double>(lo),
            static_cast<double>(hi),
            static_cast<double>(s) / n,
            static_cast<double>(l + r) / 2,
            static_cast<double>(mode),
        };
    }
};

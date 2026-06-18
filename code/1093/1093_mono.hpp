#include <cstdint>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    std::vector<double> sampleStats(std::vector<int>& freq)
    {
        auto f = reinterpret_cast<const u32*>(freq.data());
        u64 s = 0;
        u32 lo = 256, hi = 0, mode = 0, n = 0;
        for (u32 i = 0; i != 256; ++i)
        {
            int x = freq[i];
            u32 ux = static_cast<u32>(x);
            if (x)
            {
                lo = std::min(lo, i);
                hi = i;
            }
            if (freq[mode] < x)
            {
                mode = i;
            }
            n += ux;
            s += ux * i;
        }

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

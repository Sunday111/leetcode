#include <vector>

#include "sync_stdio.hpp"

class Solution
{
public:
    using u32 = uint32_t;
    int minSumOfLengths(std::vector<int>& arr, const u32 t) noexcept
    {
        auto& a = reinterpret_cast<std::vector<u32>&>(arr);
        u32 s = 0, ps = 0;
        u32 qb = 0, qe = 0;
        u32 r = ~u32{} / 2;
        u32 pb = 0, pe = 0;
        u32 ts = 0, pl = ~u32{} / 2;

        for (u32 v : a)
        {
            ++qe;
            s += v;

            while (qb != qe && ps + t < s)
            {
                ps += a[qb++];
            }

            if (qb == qe || ps + t != s) continue;

            u32 u = qe - qb;
            ps += a[qb];

            while (pe < qb)
            {
                ts += a[pe++];
                while (ts > t) ts -= a[pb++];
                pl = std::min(pl, (pe - pb) | -u32{t != ts});
            }

            qb++;
            r = std::min(r, u + pl);
        }

        return r < 0xFFFFFF ? static_cast<int>(r) : -1;
    }
};

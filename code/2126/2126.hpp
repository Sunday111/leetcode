#include <vector>

#include "cast_view.hpp"
#include "exch.hpp"
#include "pyramid_bitset.hpp"

class Solution
{
public:
    [[nodiscard]] bool asteroidsDestroyed(u64 m, const std::vector<int>& a)
        const noexcept
    {
        static PyramidBitset<100'001> b;
        static u32 freq[100'001];

        for (u32 x : a | cast_view<u32>)
        {
            b.add(x);
            freq[x]++;
        }

        bool r = true;

        for (u32 x = b.min(); x < 100'001; x = b.min())
        {
            bool ok = x <= m;
            r &= ok;
            m += (u64{x} * exch(freq[x], 0)) & -u64{ok};
            b.remove(x);
        }

        return r;
    }
};

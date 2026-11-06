#include <vector>

#include "cast_view.hpp"
#include "exch.hpp"
#include "pyramid_bitset/pbs_add.hpp"
#include "pyramid_bitset/pbs_is_empty.hpp"
#include "pyramid_bitset/pbs_make.hpp"
#include "pyramid_bitset/pbs_min.hpp"
#include "pyramid_bitset/pbs_remove.hpp"

class Solution
{
public:
    [[nodiscard]] bool asteroidsDestroyed(u64 m, const std::vector<int>& a)
        const noexcept
    {
        static u64 b_words[PyramidBitset<100'001>::kTotalWords]{};
        static auto b = pbs_make<100'001>(b_words);
        static u32 freq[100'001];

        for (u32 x : a | cast_view<u32>)
        {
            pbs_add(b, x);
            freq[x]++;
        }

        bool r = true;

        while (!pbs_is_empty(b))
        {
            u32 x = pbs_min(b);
            bool ok = x <= m;
            r &= ok;
            m += (u64{x} * exch(freq[x], 0)) & -u64{ok};
            pbs_remove(b, x);
        }

        return r;
    }
};

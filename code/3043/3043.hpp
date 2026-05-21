#include <vector>

#include "integral_aliases.hpp"
#include "pyramid_bitset.hpp"
#include "upd_max.hpp"

class Solution
{
public:
    u8 longestCommonPrefix(const std::vector<int>& a, const std::vector<int>& b)
        const noexcept
    {
        auto pa = &a, pb = &b;
        if (a.size() > b.size()) std::swap(pa, pb);
        return impl(
            reinterpret_cast<const std::vector<u32>&>(*pa),
            reinterpret_cast<const std::vector<u32>&>(*pb));
    }
    static u8 impl(
        const std::vector<u32>& a,
        const std::vector<u32>& b) noexcept
    {
        static PyramidBitset<100'000'001> bs;
        u8 max_digits = 0;
        u32 num_unique = 0;
        for (u32 v : a)
        {
            u8 digits = 0;
            while (v)
            {
                num_unique += bs.add_ex(v);
                v /= 10;
                ++digits;
            }
            upd_max(max_digits, digits);
        }
        u8 r = 0;
        for (u32 v : b)
        {
            while (v && !bs.get(v)) v /= 10;

            u8 l = 0;
            while (v)
            {
                num_unique -= bs.remove_ex(v);
                ++l;
                v /= 10;
            }
            upd_max(r, l);
            if (r == max_digits || num_unique == 0) break;
        }

        // cleanup static bitset
        while (num_unique--) bs.remove(bs.min());

        return r;
    }
};

#include "sync_stdio.hpp"

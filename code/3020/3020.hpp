#include <cmath>
#include <vector>

#include "integral_aliases.hpp"
#include "pyramid_bitset/pbs_add.hpp"
#include "pyramid_bitset/pbs_get.hpp"
#include "pyramid_bitset/pbs_is_empty.hpp"
#include "pyramid_bitset/pbs_min.hpp"
#include "pyramid_bitset/pbs_remove.hpp"
#include "sync_stdio.hpp"
#include "upd_max.hpp"

class Solution
{
public:
    inline static PyramidBitset<1 << 17> bs{};
    inline static PyramidBitset<(1 << 16) + 1> roots{};
    static u32 impl(const std::vector<u32>& nums) noexcept
    {
        constexpr u32 tt = 31623;  // sqrt(10^9)+1
        u32 f1 = 0;

        for (u32 x : nums)
        {
            f1 += x == 1;

            if (x < tt)
            {
                u32 i = x * 2;
                bool prev = pbs_add_ex(bs, i);
                pbs_add_if(bs, i + 1, !prev);
            }
            else
            {
                u32 s = static_cast<u32>(std::sqrt(static_cast<float>(x)));
                pbs_add_if(roots, s, s * s == x);
            }
        }
        pbs_remove(bs, 2);
        pbs_remove(bs, 3);

        u32 ans = 0;

        while (!pbs_is_empty(bs))
        {
            u32 i = pbs_min(bs);
            u32 x = i / 2, f = 1u + pbs_get(bs, i + 1), t = 1;
            pbs_remove(bs, i);
            pbs_remove(bs, i + 1);

            while (x < tt && f >= 2)
            {
                u32 nx = x * x;
                t += 2;
                i = nx * 2;
                if (nx < tt)
                {
                    f = pbs_remove_ex(bs, i) + pbs_remove_ex(bs, i + 1);
                }
                else
                {
                    f = pbs_remove_ex(roots, x);
                }
                x = nx;
            }

            upd_max(ans, t - (u32{!f} << 1));
        }

        while (!pbs_is_empty(roots))
        {
            pbs_remove(roots, pbs_min(roots));
        }

        if (f1 >= 2) upd_max(ans, f1 - !(f1 & 1));

        return ans;
    }

    auto maximumLength(const std::vector<int>& nums) noexcept
    {
        return impl(reinterpret_cast<const std::vector<u32>&>(nums));
    }
};

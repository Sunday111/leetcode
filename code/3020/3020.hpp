#include <cmath>
#include <vector>

#include "empty.hpp"
#include "integral_aliases.hpp"
#include "pyramid_bitset.hpp"
#include "sync_stdio.hpp"
#include "upd_max.hpp"

class Solution
{
public:
    inline static PyramidBitset<1 << 17> bs{kEmpty};
    inline static PyramidBitset<(1 << 16) + 1> roots{kEmpty};
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
                bool prev = bs.add_ex(i);
                bs.add_if(i + 1, !prev);
            }
            else
            {
                u32 s = static_cast<u32>(std::sqrt(static_cast<float>(x)));
                roots.add_if(s, s * s == x);
            }
        }
        bs.remove(2);
        bs.remove(3);

        u32 ans = 0;

        for (u32 i = bs.min(); i < (1u << 17); i = bs.min())
        {
            u32 x = i / 2, f = 1u + bs.get(i + 1), t = 1;
            bs.remove(i);
            bs.remove(i + 1);

            while (x < tt && f >= 2)
            {
                u32 nx = x * x;
                t += 2;
                i = nx * 2;
                if (nx < tt)
                {
                    f = bs.remove_ex(i) + bs.remove_ex(i + 1);
                }
                else
                {
                    f = roots.remove_ex(x);
                }
                x = nx;
            }

            upd_max(ans, t - (u32{!f} << 1));
        }

        for (u32 x = roots.min(); x < (1 << 16); x = roots.min())
        {
            roots.remove(x);
        }

        if (f1 >= 2) upd_max(ans, f1 - !(f1 & 1));

        return ans;
    }

    auto maximumLength(const std::vector<int>& nums) noexcept
    {
        return impl(reinterpret_cast<const std::vector<u32>&>(nums));
    }
};

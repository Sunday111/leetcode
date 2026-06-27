#include <array>
#include <vector>

#include "empty.hpp"
#include "integral_aliases.hpp"
#include "pyramid_bitset.hpp"
#include "sync_stdio.hpp"

class Solution
{
public:
    static constexpr u32 m = 100'000;
    inline static u16 f[m + 1];
    inline static PyramidBitset<m + 1> bs{kEmpty};
    template <bool big>
    static u32 impl(const std::vector<int>& nums) noexcept
    {
        u32 v = 0, g = 0, n = static_cast<u32>(nums.size());
        auto* __restrict__ data = reinterpret_cast<const u32*>(nums.data());
        for (u32 i = 0; i != n; ++i)
        {
            u32 x = std::min(data[i], m);
            // can overflow 16 bit counter?
            if constexpr (big)
            {
                // will overflow now?
                [[unlikely]]
                if (f[x] == 0xFFFFu)
                {
                    // remember number with overflown frequency
                    // there can only be one.
                    g = x;
                    f[x] = 0;
                }
            }
            ++f[x];
            bs.add(x);
        }
        for (u32 x = bs.min(); x <= m; x = bs.min())
        {
            bs.remove(x);
            u32 h = std::exchange(f[x], 0u);
            if constexpr (big)
            {
                [[unlikely]]
                if (g == x)
                {
                    h += (1u << 16);
                }
            }
            v += std::min(x - v, h);
        }
        return v;
    }
    u32 maximumElementAfterDecrementingAndRearranging(
        const std::vector<int>& nums) noexcept
    {
        return std::array{&impl<0>, &impl<1>}[nums.size() >= (1ul << 16)](nums);
    }
};

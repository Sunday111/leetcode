#include "bitsets/assign_bits.hpp"
#include "bitsets/ctr_zero.hpp"
#include "exch.hpp"
#include "integral_aliases.hpp"
#include "minmax/upd_max.hpp"

class Solution
{
public:
    template <std::unsigned_integral T>
    [[nodiscard]] static constexpr u8 removeLastBit(T& x) noexcept
    {
        const u8 i = ::ctr_zero(x) & 0xFF;
        const T lowest_bit = static_cast<T>(x & -x);
        x = assign_bits<false>(x, lowest_bit);
        return i;
    }

    [[nodiscard]] static constexpr u8 binaryGap(u32 n) noexcept
    {
        u8 r = 0, prev = removeLastBit(n);
        while (n)
        {
            auto curr = removeLastBit(n);
            upd_max(r, curr - exch(prev, curr));
        }
        return r;
    }
};

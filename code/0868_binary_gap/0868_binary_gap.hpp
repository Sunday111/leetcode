#include <algorithm>

#include "bit_manipultaion/clear_bit.hpp"
#include "bit_manipultaion/rightmost_one.hpp"
#include "exch.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    template <std::unsigned_integral T>
    [[nodiscard]] static constexpr u8 removeLastBit(T& x) noexcept
    {
        auto i = rightmost_one(x);
        x = clearBit(x, i);
        return i;
    }

    [[nodiscard]] static constexpr u8 binaryGap(u32 n) noexcept
    {
        u8 r = 0, p = removeLastBit(n);
        while (n)
        {
            u8 i = removeLastBit(n);
            r = std::max<u8>(r, i - exch(p, i));
        }
        return r;
    }
};

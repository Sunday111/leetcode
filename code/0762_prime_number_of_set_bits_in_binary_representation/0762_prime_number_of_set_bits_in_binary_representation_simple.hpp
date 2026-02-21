#include <bit>
#include <initializer_list>

#include "integral_aliases.hpp"

class Solution
{
public:
    inline static constexpr auto kPrimes = []
    {
        u32 m = 0;
        for (auto i : {2, 3, 5, 7, 11, 13, 17, 19}) m |= (1u << i);
        return m;
    }();

    [[nodiscard]] static constexpr u32 countPrimeSetBits(
        u32 left,
        u32 right) noexcept
    {
        u32 r = 0;
        for (u32 x = left, end = right + 1; x != end; ++x)
        {
            r += !!(kPrimes & (1u << std::popcount(x)));
        }

        return r;
    }
};

#include <immintrin.h>
#include <xmmintrin.h>

#include <array>

#include "integral_aliases.hpp"
#include "next_with_x_popcount.hpp"

class Solution
{
public:
    inline static constexpr std::array<u8, 8>
        kPrimes{2, 3, 5, 7, 11, 13, 17, 19};

    [[nodiscard]] WITH_BMI2 static constexpr u32 countPrimeSetBits(
        u32 left,
        u32 right) noexcept
    {
        u32 r = 0;
        for (auto p : kPrimes)
        {
            auto x = next_with_x_popcount(left, p);
            while (x <= right)
            {
                ++r;
                x = next_with_same_popcount(x);
            }
        }

        return r;
    }
};

#include <array>
#include <iterator>
#include <vector>

#include "cast/cast.hpp"
#include "math/precompute_primes.hpp"

inline static constexpr auto kPrimes = precompute_primes<50'000>();

inline static const auto kResults = []() noexcept
{
    std::array<u32, 100'001> r{};
    for (u32 i = 0; i != std::size(kPrimes.data); ++i)
    {
        u32 pi = kPrimes.data[i];
        u32 x1 = pi * pi;
        if (x1 > 100'000) break;
        x1 *= pi;
        r[x1 & -u32{(x1 < 100'000)}] = (1u + pi + pi * pi + x1);

        for (u32 j = i + 1; j != std::size(kPrimes.data); ++j)
        {
            u32 pj = kPrimes.data[j];
            u32 x2 = pi * pj;
            if (x2 > 100'000) break;
            r[x2] = 1u + pi + pj + x2;
        }
    }

    return r;
}();

class Solution
{
public:
    [[nodiscard]] inline static u32 sumFourDivisors(
        std::vector<int>& nums) noexcept
    {
        u32 s = 0;
        for (int v : nums) s += kResults[cast<u32>(v)];
        return s;
    }
};

#pragma once

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <ranges>

class Solution
{
public:
    [[nodiscard]] static constexpr uint64_t
    nthUglyNumber(uint64_t n, uint64_t a, uint64_t b, uint64_t c)
    {
        auto number_of_ugly_numbers_less_than = [&](uint64_t k)
        {
            uint64_t lcm_ab = std::lcm(a, b);
            uint64_t lcm_bc = std::lcm(b, c);
            uint64_t lcm_ca = std::lcm(c, a);
            uint64_t lcm_abc = std::lcm(lcm_ab, c);
            uint64_t total = k / a + k / b + k / c;
            uint64_t overlap =
                k / lcm_ab + k / lcm_bc + k / lcm_ca - k / lcm_abc;
            return total - overlap;
        };

        return *std::ranges::lower_bound(
            std::views::iota(uint64_t{1}, std::numeric_limits<uint64_t>::max()),
            n,
            std::less<>{},
            number_of_ugly_numbers_less_than);
    }
};

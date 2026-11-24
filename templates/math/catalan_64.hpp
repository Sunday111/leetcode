#pragma once

#include <array>
#include <numeric>

#include "integral_aliases.hpp"

inline constexpr auto kCatalan64 = []
{
    std::array<u64, 37> values{};
    values.front() = 1;
    for (u32 n = 1; n < values.size(); ++n)
    {
        u32 numerator = 4 * n - 2;
        u32 denominator = n + 1;
        u32 divisor = std::gcd(numerator, denominator);
        values.at(n) = (values.at(n - 1) / (denominator / divisor)) *
                       (numerator / divisor);
    }
    return values;
}();

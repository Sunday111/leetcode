#pragma once

#include <array>

#include "integral_aliases.hpp"

inline constexpr auto kFactorial64 = []
{
    std::array<u64, 21> r;  // NOLINT
    r[0] = 1;
    for (u8 i = 1; i != r.size(); ++i) r[i] = r[i - 1] * i;

    return r;
}();

static_assert(kFactorial64[20] == 2432902008176640000);

#pragma once

#include <functional>

struct FenwickTreeXORTraits
{
    using Op = std::bit_xor<>;
    using Inv = std::bit_xor<>;
    static constexpr int identity = 0;
};

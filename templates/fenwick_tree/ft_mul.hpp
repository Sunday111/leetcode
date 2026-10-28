#pragma once

#include <functional>

struct FenwickTreeMulTraits
{
    using Op = std::multiplies<>;
    using Inv = std::divides<>;
    static constexpr int identity = 1;
};

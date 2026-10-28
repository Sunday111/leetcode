#pragma once

#include <functional>

struct FenwickTreeAddTraits
{
    using Op = std::plus<>;
    using Inv = std::minus<>;
    static constexpr int identity = 0;
};

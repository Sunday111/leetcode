#pragma once

struct FenwickTreeXORTraits
{
    using Op = decltype([] [[gnu::always_inline]] (auto a, auto b) noexcept
                        { return a ^ b; });
    using Inv = Op;
    static constexpr int identity = 0;
};

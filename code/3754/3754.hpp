#include <cstdint>

#include "int_if.hpp"

class Solution
{
    using u32 = uint32_t;
    using u64 = uint64_t;

public:
    [[nodiscard]] constexpr u64 sumAndMultiply(u32 n) noexcept
    {
        u64 m = 1, x = 0, s = 0;
        while (n)
        {
            u32 d = n % 10;
            x += m * d;
            m *= iif(d, 10u, 1u);
            s += d;
            n /= 10;
        }

        return x * s;
    }
};

#include <cstdint>
#include <vector>

#include "sync_stdio.hpp"

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard, gnu::no_sanitize_address, gnu::flatten]]
    constexpr u32 climbStairs(u32 n, const std::vector<int>& costs)
        const noexcept
    {
        auto min = [](u32 a, u32 b)
        {
            return b ^ ((a ^ b) & -u32{a < b});
        };
        u32 a = 0, b = 0, c = 0;
        for (int cost : costs)
        {
            const u32 next = min(min(a, b + 2), c + 6);
            c = b;
            b = a;
            a = next + (cost & 0xFFFF);
        }
        return a + n;
    }
};

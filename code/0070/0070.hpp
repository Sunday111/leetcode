#include <array>

#include "integral_aliases.hpp"

class Solution
{
public:
    inline static constexpr auto kAns = []()
    {
        std::array<u32, 46> r;  // NOLINT
        r[0] = r[1] = 1;
        for (u32 i = 2; i != r.size(); ++i) r[i] = r[i - 1] + r[i - 2];
        return r;
    }();

    [[nodiscard]] static constexpr u32 climbStairs(u32 n) noexcept
    {
        return kAns[n];
    }
};

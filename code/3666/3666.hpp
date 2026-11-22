#include <algorithm>
#include <string_view>

#include "integral_aliases.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr int minOperations(
        const std::string_view s,
        const u32 k) noexcept
    {
        const u32 n = static_cast<u32>(s.size());
        const u32 a = static_cast<u32>(std::ranges::count(s, '0'));
        const u32 b = n - a;
        const u32 base = n - k;

        if (!a) return 0;
        if (!base)
        {
            if (a == n) return 1;
            if (a == 0) return 0;
            return -1;
        }

        u32 m = (a + k - 1) / k;

        u32 m1 = ~u32{};
        if (~(k ^ a) & 1)
        {
            m1 = std::max(m, (b + base - 1) / base);
            m1 += ~m1 & 1;
        }

        u32 m2 = ~u32{};
        if (~a & 1)
        {
            m2 = std::max(m, (a + base - 1) / base);
            m2 += m2 & 1;
        }

        return std::bit_cast<int>(std::min(m1, m2));
    }
};

#include <vector>

// https://leetcode.com/problems/flip-square-submatrix-vertically/

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard, gnu::always_inline]] auto reverseSubmatrix(
        std::vector<std::vector<int>>& g,
        u8 y0,
        u8 x0,
        u8 k) noexcept
    {
        for (u8 y1 = y0 + k - 1; y0 < y1; ++y0, --y1)
        {
            auto a = g[y0].begin() + x0;
            std::swap_ranges(a, a + k, g[y1].begin() + x0);
        }
        return std::move(g);
    }
};

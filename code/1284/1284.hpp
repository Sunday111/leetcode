#include <algorithm>
#include <bit>
#include <cstdint>
#include <ranges>
#include <vector>

#include "namespaces.hpp"

class Solution
{
public:
    using u32 = uint32_t;
    int minFlips(const std::vector<std::vector<int>>& g) const noexcept
    {
        const u32 h = g.size() & ~0u, w = g[0].size() & ~0u;

        auto mask_to_num_flips = [&](u32 m)
        {
            auto f = [&] [[gnu::always_inline]] (u32 x, u32 y) -> bool
            {
                u32 i = (y * w + x) & 31;
                return (m >> i) & (x < w) & (y < h);
            };
            auto is_bad = [&](auto yx)
            {
                auto [y, x] = yx;
                return g[y][x] ^ f(x, y) ^ f(x + 1, y) ^ f(x - 1, y) ^
                       f(x, y + 1) ^ f(x, y - 1);
            };
            auto coords =
                stdv::cartesian_product(stdv::iota(0u, h), stdv::iota(0u, w));
            bool t = std::ranges::any_of(coords, is_bad);
            return static_cast<u32>(std::popcount(m)) | -u32{t};
        };

        return std::bit_cast<int>(stdr::min(
            stdv::iota(0u, 1u << (w * h)) |
            stdv::transform(mask_to_num_flips)));
    }
};

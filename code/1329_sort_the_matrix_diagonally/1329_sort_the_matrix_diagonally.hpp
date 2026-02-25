#include <algorithm>
#include <functional>
#include <ranges>
#include <vector>

#include "force_inline.hpp"
#include "integral_aliases.hpp"

namespace stdr = std::ranges;
namespace stdv = std::views;

class Solution
{
public:
    template <typename Cmp = stdr::less>
    [[nodiscard]] static constexpr auto diagonalSort(
        std::vector<std::vector<int>>& g,
        Cmp cmp = Cmp{}) noexcept
    {
        const u8 h = g.size() & 0xFF, w = g[0].size() & 0xFF;

        auto diagGetter = [&](u8 x, u8 y) INLINE_LAMBDA
        {
            return [&, x, y](u8 i) -> int&
            {
                return g[y + i][x + i];
            };
        };

        auto sortDiag = [&](u8 x, u8 y) INLINE_LAMBDA
        {
            const u8 l = std::min<u8>(h - y, w - x);
            stdr::sort(
                stdv::iota(u8{0}, l) | stdv::transform(diagGetter(x, y)),
                cmp);
        };

        // Bottom-left
        stdr::for_each(
            stdv::iota(u8{0}, h) | stdv::reverse,
            std::bind(sortDiag, 0, std::placeholders::_1));

        // Top-right
        stdr::for_each(
            stdv::iota(u8{1}, w),
            std::bind(sortDiag, std::placeholders::_1, 0));

        return std::move(g);
    }
};

#include <bit>
#include <vector>

#include "cast_view.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> countBits(
        unsigned n) noexcept
    {
        namespace stdv = std::views;
        return std::ranges::to<std::vector>(
            stdv::iota(0u, n + 1) | stdv::transform(std::popcount<unsigned>) |
            cast_view<int>);
    }
};

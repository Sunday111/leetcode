#include <ranges>
#include <string>

#include "sync_stdio.hpp"

class Solution
{
public:
    std::string maxSumOfSquares(size_t num, size_t s) const noexcept
    {
        if (num * 9 < s) return {};
        using std::views::repeat;
        const size_t q = s / 9, r = s % 9, t = !!r;
        const char tc = static_cast<char>('0' + r);
        return std::array{
                   repeat('9', q),
                   repeat(tc, t),
                   repeat('0', num - q - t)} |
               std::views::join | std::ranges::to<std::string>();
    }
};

#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

namespace stdv = std::views;
namespace stdr = std::ranges;

class Solution
{
public:
    auto minDeletionSize(std::vector<std::string>& strs)
    {
        auto& map = stdv::transform;
        return stdr::count(
            stdv::iota(0uz, strs[0].size()) |
                map([&](size_t x)
                    { return strs | map([&, x](auto& s) { return s[x]; }); }) |
                map(stdr::is_sorted),
            false);
    }
};

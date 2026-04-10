#include <numeric>
#include <ranges>
#include <vector>


class Solution
{
public:
    std::vector<int> xorQueries(
        std::vector<int>& a,
        const std::vector<std::vector<int>>& queries)
    {
        std::inclusive_scan(a.begin(), a.end(), a.begin(), std::bit_xor{});

        return queries |
               std::views::transform(
                   [&](auto& q)
                   {
                       using u32 = uint32_t;
                       int l = q[0];
                       l = a[static_cast<u32>(std::max(0, l - 1))] & -!l;
                       return l ^ a[static_cast<u32>(q[1])];
                   }) |
               std::ranges::to<std::vector>();
    }
};

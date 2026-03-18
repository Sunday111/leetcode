// https://leetcode.com/problems/count-submatrices-with-top-left-element-and-sum-less-than-k/

#include <algorithm>
#include <functional>
#include <ranges>
#include <vector>

#include "namespaces.hpp"  // IWYU pragma: keep

class Solution
{
public:
    auto countSubmatrices(std::vector<std::vector<int>>& g, int k) noexcept
    {
        constexpr auto adj = stdv::adjacent<2>;

        // first row prefix sum
        for (auto [prev, curr] : g[0] | adj) curr += prev;

        // matrix prefix sum
        for (auto [prev, curr] : g | adj)
        {
            curr[0] += prev[0];
            for (size_t x = 1; x != curr.size(); ++x)
            {
                curr[x] += curr[x - 1] + prev[x] - prev[x - 1];
            }
        }

        return stdr::count_if(
            g | std::views::join,
            std::bind(stdr::less_equal{}, std::placeholders::_1, k));
    }
};

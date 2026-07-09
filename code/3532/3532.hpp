#include <ranges>
#include <vector>

#include "int_if.hpp"
#include "sync_stdio.hpp"

using u32 = uint32_t;
namespace stdr = std::ranges;
namespace stdv = std::views;
class Solution
{
public:
    std::vector<bool> pathExistenceQueries(
        const u32 n,
        std::vector<int>& nums,
        const int md,
        const std::vector<std::vector<int>>& queries) noexcept
    {
        auto p = reinterpret_cast<u32*>(nums.data());
        int vj = nums[0];
        p[0] = 0;
        for (u32 i = 1; i != n; ++i)
        {
            int vi = nums[i];
            p[i] = iif(vi - vj <= md, p[i - 1], i);
            vj = vi;
        }
        auto query = [&] [[gnu::always_inline]] (const std::vector<int>& q)
        {
            return p[q[0]] == p[q[1]];
        };
        return queries | stdv::transform(query) | stdr::to<std::vector>();
    }
};

#include <vector>

#include "cast_view.hpp"
#include "ceil_div.hpp"
#include "integral_aliases.hpp"
#include "sum.hpp"

namespace stdv = std::views;

class Solution
{
public:
    [[nodiscard]] static constexpr u64 minimumReplacement(
        const std::vector<int>& a) noexcept
    {
        return sum(
            a | stdv::reverse | cast_view<u32> |
                stdv::transform(
                    [&, p = ~0u >> 1](u32 v) INLINE_LAMBDA mutable
                    {
                        u32 k = ceil_div(v, p);
                        p = v / k;
                        return k - 1;
                    }),
            u64{});
    }
};

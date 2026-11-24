#include <vector>

#include "cast/cast_view.hpp"
#include "math/ceil_div.hpp"
#include "integral_aliases.hpp"
#include "math/sum.hpp"

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
                    [&, p = ~0u >> 1] [[gnu::always_inline]] (u32 v) mutable
                    {
                        u32 k = ceil_div(v, p);
                        p = v / k;
                        return k - 1;
                    }),
            u64{});
    }
};

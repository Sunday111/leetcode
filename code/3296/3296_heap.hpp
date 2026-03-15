#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

#include "integral_aliases.hpp"
#include "namespaces.hpp"  // IWYU pragma: keep

inline static constexpr auto arith_seq_sum =
    [] [[nodiscard, gnu::always_inline]] (u64 len) noexcept -> u64
{
    return (u64{len + 1} * len) / 2;
};

inline static constexpr auto max_arith_seq_len =
    [] [[nodiscard, gnu::always_inline]] (
        u64 limit_sum,
        u32 sum_multiplier = 1) noexcept -> u32
{
    auto q = 1 + static_cast<double>(8 * limit_sum) / sum_multiplier;
    auto x = (std::sqrt(q) - 1) / 2;
    return static_cast<u32>(x);
};

class Solution
{
public:
    [[nodiscard]] u64 minNumberOfSeconds(
        u32 height,
        const std::vector<int>& times) const noexcept
    {
        static std::pair<u32, u32> h[100'001];
        u32 hs = 0;
        for (int t : times) h[hs++] = {static_cast<u32>(t), 0};

        constexpr auto cmp = std::greater{};
        auto proj = [&] [[nodiscard, gnu::always_inline]] (
                        const std::pair<u32, u32>& p) noexcept
        {
            auto& [t, l] = p;
            return arith_seq_sum(l + 1) * u64{t};
        };
        stdr::make_heap(h, h + hs, cmp, proj);

        auto he = h + hs;
        auto& [t, l] = he[-1];
        while (height)
        {
            stdr::pop_heap(h, he, cmp, proj);
            u32 dl = std::min(height, max_arith_seq_len(proj(*h), t) - l);
            height -= dl;
            l += dl;
            stdr::push_heap(h, he, cmp, proj);
        }

        return stdr::max(
            std::span{h, hs} |
            stdv::transform(
                [](const std::pair<u32, u32>& p)
                { return u64{p.first} * arith_seq_sum(p.second); }));
    }
};

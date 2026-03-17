#include <vector>

#include "integral_aliases.hpp"
#include "namespaces.hpp"  // IWYU pragma: keep
#include "radix_sorter.hpp"
#include "upd_max.hpp"
#include "upd_min.hpp"

// https://leetcode.com/problems/largest-submatrix-with-rearrangements/

class Solution
{
public:
    template <size_t bits_per_pass>
    inline static constexpr auto rad_sort =
        [] [[gnu::always_inline, gnu::hot]] (std::vector<u32> & x) noexcept
    {
        radix_sort<bits_per_pass, 1, SortOrder::Descending>(std::span{x});
    };

    [[nodiscard]] u32 impl(std::vector<std::vector<u32>>& m) const noexcept
    {
        const u32 h = static_cast<u32>(m.size()),
                  w = static_cast<u32>(m[0].size());

        if (h == 1)
        {
            return static_cast<u32>(stdr::count(m[0], 1u));
        }

        if (w == 1)
        {
            u32 p = 0, r = 0;
            for (auto& row : m)
            {
                u32 v = row[0] & 1;
                p = (v + p) & -v;
                upd_max(r, p);
            }

            return r;
        }

        for (u32 y = 1; y != h; ++y)
        {
            for (auto [v, pv] : stdv::zip(m[y], m[y - 1]))
            {
                v += pv & -u32{!!v};
            }
        }

        auto run = [&] [[gnu::always_inline, gnu::hot, nodiscard]] (
                       auto&& sort) noexcept
        {
            u32 ans = 0;

            for (auto& row : m)
            {
                sort(row);

                u32 l = h, x = 0;
                while (x != w && l * w > ans)
                {
                    upd_min(l, row[x++]);
                    upd_max(ans, l * x);
                }
            }

            return ans;
        };

        if (w > 100'000 / 7) return run(rad_sort<3>);
        if (w > 100'000 / 15) return run(rad_sort<4>);
        if (w > 100'000 / 31) return run(rad_sort<5>);
        return run(
            std::bind(stdr::sort, std::placeholders::_1, std::greater{}));
    }

    u32 largestSubmatrix(std::vector<std::vector<int>>& matrix) const noexcept
    {
        return impl(reinterpret_cast<std::vector<std::vector<u32>>&>(matrix));
    }
};

#include "sync_stdio.hpp"


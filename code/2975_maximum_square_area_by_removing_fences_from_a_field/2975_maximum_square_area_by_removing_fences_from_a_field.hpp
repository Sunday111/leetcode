#include <algorithm>
#include <unordered_set>
#include <vector>

#include "force_inline.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    template <typename F>
    FORCE_INLINE static constexpr void gen_sides(
        std::vector<u32>& fences,
        F f) noexcept
    {
        std::ranges::sort(fences);

        for (u32 i = static_cast<u32>(fences.size() - 1); i; --i)
        {
            for (u32 j = 0; j != i; ++j)
            {
                if (f(fences[i] - fences[j]))
                {
                    break;
                }
            }
        }
    }

    FORCE_INLINE static int maximizeSquareArea(
        std::vector<u32>& x_fences,
        std::vector<u32>& y_fences) noexcept
    {
        std::unordered_set<u32> seen;
        const u32 n = static_cast<u32>(x_fences.size());
        seen.reserve(n * n);

        gen_sides(
            x_fences,
            [&](u32 side) INLINE_LAMBDA
            {
                seen.insert(side);
                return false;
            });

        u32 r = 0;
        gen_sides(
            y_fences,
            [&](u32 side) INLINE_LAMBDA
            {
                bool found = seen.contains(side);
                r = std::max(r, side & -u32{found});
                return found;
            });

        if (!r) return -1;

        return static_cast<int>((u64{r} * u64{r}) % 1000000007u);
    }

    static int maximizeSquareArea(
        u32 h,
        u32 w,
        std::vector<int>& h_fences,
        std::vector<int>& w_fences)
    {
        auto h_fences_u = reinterpret_cast<std::vector<u32>*>(&h_fences);
        h_fences_u->push_back(h);
        h_fences_u->push_back(1);
        auto w_fences_u = reinterpret_cast<std::vector<u32>*>(&w_fences);
        w_fences_u->push_back(w);
        w_fences_u->push_back(1);

        // w_fences go into the hash table so prefer smaller one
        if (w_fences_u->size() > h_fences_u->size())
        {
            std::swap(w_fences_u, h_fences_u);
        }

        return maximizeSquareArea(*w_fences_u, *h_fences_u);
    }
};

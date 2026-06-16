#include <algorithm>
#include <functional>
#include <tuple>
#include <utility>
#include <vector>

#include "integral_aliases.hpp"
#include "union_find.hpp"

class Solution
{
public:
    using UF = UnionFind<u32>;
    using UFNode = typename UF::Node;
    inline static UFNode nodes[1000];
    inline static std::pair<u16, u16> q[1'000'000 / 2];
    inline static std::pair<u32, u32> p[1'000];
    inline static constexpr auto dist =
        [] [[gnu::always_inline]] (u16 i, u16 j) noexcept -> u32
    {
        auto [xi, yi] = p[i];
        auto [xj, yj] = p[j];
        u32 dx = std::max(xi, xj) - std::min(xi, xj);
        u32 dy = std::max(yi, yj) - std::min(yi, yj);
        return dx + dy;
    };
    inline static constexpr auto proj =
        [] [[gnu::always_inline]] (auto ij) noexcept -> u32
    {
        return std::apply(dist, ij);
    };
    inline static constexpr auto cmp = std::greater{};

    [[gnu::target("avx2,bmi2"), nodiscard]]
    u32 minCostConnectPoints(std::vector<std::vector<int>>& points) noexcept
    {
        const u32 n = static_cast<u32>(points.size());
        if (n < 2) return 0;

        auto qe = q;
        for (u32 i = 0; i != n; ++i)
        {
            for (u32 j = i + 1; j != n; ++j)
            {
                *qe++ = {i, j};
            }

            auto& pt = points[i];
            p[i] = {pt[0] + 1'000'000, pt[1] + 1'000'000};
        }

        std::ranges::make_heap(q, qe, cmp, proj);

        u32 cost = 0;
        UF uf(nodes, n);

        while (nodes[uf.find(0)].size != n)
        {
            auto [i, j] = q[0];
            cost += dist(i, j) & -u32{uf.merge(i, j)};
            std::ranges::pop_heap(q, qe--, cmp, proj);
        }

        return cost;
    }
};

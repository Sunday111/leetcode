#include <algorithm>
#include <vector>

#include "integral_aliases.hpp"
#include "union_find.hpp"
#include "upd_min.hpp"

namespace stdr = std::ranges;

class Solution
{
public:
    [[nodiscard]] int impl(
        u32 n,
        const std::vector<std::vector<u32>>& edges,
        u32 k) const noexcept
    {
        using UF = UnionFind<u32>;
        using Node = typename UF::Node;

        static u32 edges_heap[100'001];

        static Node nodes[100'001];
        UF uf{nodes, n};
        u32 heap_size = 0;

        u32 min_edge = ~u32{};
        for (u32 i = 0; i != edges.size(); ++i)
        {
            auto& edge = edges[i];
            u32 u = edge[0], v = edge[1], s = edge[2], must = edge[3];
            if (must)
            {
                if (!uf.merge(u, v)) return -1;
                upd_min(min_edge, s);
            }
            else
            {
                edges_heap[heap_size++] = i;
            }
        }

        if (nodes[uf.find(0)].size != n)
        {
            constexpr auto cmp = std::less{};
            const auto proj =
                [&] [[nodiscard, gnu::always_inline]] (u32 i) noexcept -> u64
            {
                auto& edge = edges[i];
                u32 s = edge[2], must = edge[3];
                return s | (must << 20);
            };

            stdr::make_heap(edges_heap, edges_heap + heap_size, cmp, proj);

            auto vals_end = edges_heap + heap_size + 1;
            u32* vals = vals_end;

            while (heap_size && nodes[uf.find(0)].size != n)
            {
                auto& edge = edges[edges_heap[0]];
                u32 u = edge[0], v = edge[1], s = edge[2];

                if (uf.merge(u, v)) *(--vals) = s;

                stdr::pop_heap(edges_heap, edges_heap + heap_size--, cmp, proj);
            }

            u32 num_vals = static_cast<u32>(vals_end - vals);
            vals[0] <<= !!k;
            upd_min(min_edge, vals[0]);
            upd_min(min_edge, vals[k] | -u32{num_vals <= k});
        }

        if (nodes[uf.find(0)].size == n) return static_cast<int>(min_edge);

        return -1;
    }

    [[nodiscard]] int maxStability(
        int n,
        const std::vector<std::vector<int>>& edges,
        int k) const noexcept
    {
        return impl(
            static_cast<u32>(n),
            reinterpret_cast<const std::vector<std::vector<u32>>&>(edges),
            static_cast<u32>(k));
    }
};

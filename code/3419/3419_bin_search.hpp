#include <algorithm>
#include <cassert>
#include <ranges>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;

    struct Edge  // NOLINT
    {
        u32 link;
        u32 value;
        u32 next;
    };

    [[nodiscard]] static constexpr int minMaxWeight(
        u32 n,
        std::vector<std::vector<int>>& inedges,
        [[maybe_unused]] int threshold)
    {
        static u32 firstEdge[100'001];  // NOLINT
        std::fill_n(firstEdge, n, 0xFFFFFFFF);

        u32 numEdges = 0;
        static Edge edges[100'001];  // NOLINT

        u32 ans = 0;
        for (auto& inEdge : inedges)
        {
            ans = std::max(ans, static_cast<u32>(inEdge[2]));
            edges[numEdges] = {
                .link = static_cast<u32>(inEdge[0]),
                .value = static_cast<u32>(inEdge[2]),
                .next = std::exchange(
                    firstEdge[static_cast<u32>(inEdge[1])],
                    numEdges),
            };
            ++numEdges;
        }

        static u32 q[1'000'000], vis[3126];  // NOLINT

        auto bfs = [&](u32 mid) -> bool
        {
            std::ranges::fill_n(vis, (n / 32) + 1, 0);  // NOLINT
            u32 qb = 0, qe = 0, c = 1;
            vis[0] = 1, q[qe++] = 0;  // NOLINT

            while (qb != qe && c != n)
            {
                for (u32 eid = firstEdge[q[qb++]]; eid != 0xFFFFFFFF;)
                {
                    auto& edge = edges[eid];
                    u32& word = vis[edge.link / 32];
                    u32 mask = u32{1} << (edge.link % 32);

                    if (edge.value <= mid && !(word & mask))
                    {
                        word |= mask;
                        c++;
                        q[qe++] = edge.link;
                    }
                    eid = edge.next;
                }
            }

            return c == n;
        };

        if (!bfs(ans)) return -1;

        return static_cast<int>(*std::ranges::lower_bound(
            std::views::iota(u32{}, u32{1'000'001}),
            true,
            std::less{},
            bfs));
    }
};

#include <algorithm>
#include <cassert>
#include <set>
#include <vector>

#include "bump_set.hpp"

class Solution
{
public:
    struct Edge
    {
        u32 link;
        u32 value;
        u32 next;
    };

    struct Node
    {
        u32 maxEdge = 0xFFFFFFFF;
        u32 firstEdge = 0xFFFFFFFF;
    };

    [[nodiscard]] static constexpr int minMaxWeight(
        u32 n,
        const std::vector<std::vector<int>>& inedges,
        [[maybe_unused]] int threshold) noexcept
    {
        static Node nodes[100'001];  // NOLINT
        std::fill_n(nodes, n, Node{});

        u32 numEdges = 0;
        static Edge edges[100'001];  // NOLINT

        for (auto& inEdge : inedges)
        {
            edges[numEdges] = {
                .link = static_cast<u32>(inEdge[0]),
                .value = static_cast<u32>(inEdge[2]),
                .next = std::exchange(
                    nodes[static_cast<u32>(inEdge[1])].firstEdge,
                    numEdges),
            };
            ++numEdges;
        }

        nodes[0].maxEdge = 0;

        using SetStorage = GlobalBufferStorage<1 << 22>;
        SetStorage::Instance().Reset();
        ObjectWithoutDtor<BumpSet<
            std::pair<u32, u32>,
            SetStorage,
            std::less<std::pair<u32, u32>>>>
            queue;
        queue->emplace(0, 0);

        while (!queue->empty())
        {
            auto [w, node_id] = *queue->begin();
            queue->erase(queue->begin());

            auto& node = nodes[node_id];
            if (node.maxEdge < w) continue;

            for (u32 edgeId = node.firstEdge; edgeId != 0xFFFFFFFF;)
            {
                const Edge& edge = edges[edgeId];
                u32 maxEdgeInPath = std::max(node.maxEdge, edge.value);
                if (auto& src_node = nodes[edge.link];
                    maxEdgeInPath < src_node.maxEdge)
                {
                    src_node.maxEdge = maxEdgeInPath;
                    queue->emplace(maxEdgeInPath, edge.link);
                }
                edgeId = edge.next;
            }
        }

        return static_cast<int>(std::ranges::max_element(
                                    nodes,
                                    nodes + n,  // NOLINT
                                    std::less{},
                                    &Node::maxEdge)
                                    ->maxEdge);
    }
};

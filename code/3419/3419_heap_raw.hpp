#include <algorithm>
#include <cassert>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;

    struct Edge  // NOLINT
    {
        u32 link;
        u32 value;
        u32 next = 0xFFFFFFFF;
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
                    numEdges)};
            ++numEdges;
        }

        nodes[0].maxEdge = 0;

        static std::pair<u32, u32> queue[300'001];  // NOLINT
        u32 qSize = 0;

        auto heap_op = [&](auto op)
        {
            op(queue,
               queue + qSize,  // NOLINT
               std::greater{},
               &std::pair<u32, u32>::first);
        };
        queue[qSize++] = {0, 0};

        while (qSize)
        {
            heap_op(std::ranges::pop_heap);
            auto [w, node_id] = queue[--qSize];

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
                    queue[qSize++] = {maxEdgeInPath, edge.link};
                    heap_op(std::ranges::push_heap);
                }
                edgeId = edge.next;
            }
        }

        const u32 r = std::ranges::max_element(
                          nodes,
                          nodes + n,  // NOLINT
                          std::less{},
                          &Node::maxEdge)
                          ->maxEdge;

        if (r == 0xFFFFFFFF) return -1;
        return static_cast<int>(r);
    }
};

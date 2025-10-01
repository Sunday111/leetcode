#include <algorithm>
#include <array>
#include <cassert>
#include <span>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;

    struct Edge  // NOLINT
    {
        u32 src;
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
        const auto nodes = [&]()
        {
            static std::array<Node, 100'001> nodes_arr;
            std::fill_n(nodes_arr.begin(), n, Node{});
            return std::span{nodes_arr}.first(n);
        }();

        const auto edges = [&]()
        {
            static std::array<Edge, 100'001> edges_arr;
            u32 numEdges = 0;

            for (auto& inEdge : inedges)
            {
                u32 a = static_cast<u32>(inEdge[0]);
                u32 b = static_cast<u32>(inEdge[1]);
                u32 w = static_cast<u32>(inEdge[2]);

                auto& node = nodes[b];
                edges_arr[numEdges] = {a, w, node.firstEdge};
                node.firstEdge = numEdges++;
            }

            return std::span{edges_arr}.first(numEdges);
        }();

        nodes[0].maxEdge = 0;

        static std::vector<std::pair<u32, u32>> queue;
        auto heap_op = [&](auto op)
        {
            op(queue.begin(), queue.end(), std::greater{});
        };
        queue.emplace_back(0, 0);

        while (!queue.empty())
        {
            heap_op(std::ranges::pop_heap);
            auto [w, node_id] = queue.back();
            queue.pop_back();

            auto& node = nodes[node_id];
            if (node.maxEdge < w) continue;

            for (u32 edgeId = node.firstEdge; edgeId != 0xFFFFFFFF;)
            {
                const Edge& edge = edges[edgeId];
                u32 maxEdgeInPath = std::max(node.maxEdge, edge.value);
                if (auto& src_node = nodes[edge.src];
                    maxEdgeInPath < src_node.maxEdge)
                {
                    src_node.maxEdge = maxEdgeInPath;
                    queue.emplace_back(maxEdgeInPath, edge.src);
                    heap_op(std::ranges::push_heap);
                }
                edgeId = edge.next;
            }
        }

        u32 r = 0;
        for (auto& node : nodes) r = std::max(r, node.maxEdge);

        if (r == 0xFFFFFFFF) return -1;
        return static_cast<int>(r);
    }
};

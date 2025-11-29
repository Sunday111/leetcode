#include <algorithm>
#include <cstdint>
#include <vector>

#include "integral_aliases.hpp"
#include "to.hpp"

struct Node
{
    u16 in_degree;
    u16 out_degree;
    u16 offset;
};

struct Graph  // NOLINT
{
    std::array<Node, 401> nodes;
    std::array<u16, 10'001> links;
    std::array<u16, 401> q;

    void init(const u16 k, const std::vector<std::vector<int>>& conds)
    {
        std::ranges::fill_n(nodes.begin() + 1, k, Node{0, 0, 0});

        for (auto& cond : conds)
        {
            ++nodes[cast<u16>(cond[0])].out_degree;
            ++nodes[cast<u16>(cond[1])].in_degree;
        }

        u16 offset = 0;
        for (u16 node_id = 1; node_id <= k; ++node_id)
        {
            auto& node = nodes[node_id];
            node.offset = offset;
            offset += std::exchange(node.out_degree, u16{0});
        }

        for (auto& cond : conds)
        {
            auto& node = nodes[cast<u16>(cond[0])];
            links[node.offset + node.out_degree++] = cast<u16>(cond[1]);
        }
    }

    bool top_sort(const u16 k, std::array<u16, 401>& sorted) noexcept
    {
        u16 qe = 0, idx = 0;

        // Push all roots (nodes without incoming links)
        for (u16 node_id = 1; node_id <= k; ++node_id)
        {
            q[qe] = node_id;
            qe += !nodes[node_id].in_degree;
        }

        for (u16 qb = 0; qb != qe; ++qb)
        {
            sorted[idx++] = q[qb];
            const auto& node = nodes[q[qb]];
            for (u16 i = node.offset, end = i + node.out_degree; i != end; ++i)
            {
                u16 link = links[i];
                q[qe] = link;
                qe += !--nodes[link].in_degree;
            }
        }

        return idx == k;
    }
};

class Solution
{
public:
    static std::vector<std::vector<int>> buildMatrix(
        uint16_t k,
        std::vector<std::vector<int>>& rowConditions,
        std::vector<std::vector<int>>& colConditions) noexcept
    {
        static std::array<u16, 401> x, y, sorted;

        static Graph g;
        g.init(k, rowConditions);
        if (!g.top_sort(k, sorted)) return {};
        for (u16 i = 0; i != k; ++i) y[sorted[i]] = i;

        g.init(k, colConditions);
        if (!g.top_sort(k, sorted)) return {};
        for (u16 i = 0; i != k; ++i) x[sorted[i]] = i;

        std::vector<std::vector<int>> r(k);
        for (auto& row : r) row.resize(k);

        for (u16 v = k; v; --v) r[y[v]][x[v]] = v;

        return r;
    }
};

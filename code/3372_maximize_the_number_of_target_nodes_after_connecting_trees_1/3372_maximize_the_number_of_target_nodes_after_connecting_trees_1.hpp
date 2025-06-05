#pragma once

#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <vector>

#if defined(__GNUC__) || defined(__clang__)
#define ALWAYS_INLINE inline __attribute__((always_inline))
#else
#define ALWAYS_INLINE inline
#endif

struct Node
{
    uint16_t neighbors_offset = 0;
    uint16_t neighbors_count = 0;
};

enum class ControlFlow : uint8_t
{
    Break,
    Continue,
};

struct UndirectedTree
{
    constexpr void InitFromEdges(std::vector<std::vector<int>>& edges)
    {
        nodes.clear();
        nodes.resize(edges.size() + 1);

        all_neighbors.clear();
        all_neighbors.resize(edges.size() * 2);

        // Count the number of children for each node
        for (auto& edge : edges)
        {
            nodes[static_cast<uint16_t>(edge[0])].neighbors_count += 1;
            nodes[static_cast<uint16_t>(edge[1])].neighbors_count += 1;
        }

        // Calculate the offset for neighbor array for each node
        {
            uint16_t offset = 0;
            for (auto& node : nodes)
            {
                node.neighbors_offset = offset;
                offset += std::exchange(node.neighbors_count, 0);
            }
        }

        // Populate neighbors arrays with children
        for (auto& edge : edges)
        {
            auto from_index = static_cast<uint16_t>(edge[0]);
            auto& from_node = nodes[from_index];

            auto to_index = static_cast<uint16_t>(edge[1]);
            auto& to_node = nodes[to_index];

            all_neighbors
                [from_node.neighbors_offset + from_node.neighbors_count] =
                    to_index;
            from_node.neighbors_count += 1;

            all_neighbors[to_node.neighbors_offset + to_node.neighbors_count] =
                from_index;
            to_node.neighbors_count += 1;
        }
    }

    template <typename F>
    ALWAYS_INLINE constexpr auto ForEachNeighbor(uint16_t node_id, F f) const
    {
        using CallbackReturn = std::decay_t<decltype(f(0))>;
        const auto& node = nodes[node_id];
        const uint16_t end = node.neighbors_offset + node.neighbors_count;
        for (uint16_t i = node.neighbors_offset; i != end; ++i)
        {
            if constexpr (std::same_as<ControlFlow, CallbackReturn>)
            {
                if (f(all_neighbors[i]) == ControlFlow::Break)
                {
                    break;
                }
            }
            else
            {
                f(all_neighbors[i]);
            }
        }
    }

    std::vector<uint16_t> all_neighbors;
    std::vector<Node> nodes;
};

class CentroidDecomposition
{
private:
    const UndirectedTree* tree = nullptr;
    std::vector<bool> visited;
    std::vector<uint16_t> sizes;
    std::vector<uint16_t> result;
    std::vector<uint16_t> total;
    std::vector<uint16_t> count;
    std::unordered_set<uint16_t> active_prefixes;
    std::vector<std::vector<uint16_t>> prefixes;
    uint16_t n{};
    uint16_t k{};

    constexpr uint16_t subtree_sizes(uint16_t node, uint16_t parent)
    {
        auto& r = sizes[node];
        tree->ForEachNeighbor(
            node,
            [&](uint16_t child)
            {
                if (child != parent && !visited[child])
                {
                    r += subtree_sizes(child, node);
                }
            });

        return r;
    }

    constexpr uint16_t
    find_centroid(uint16_t node, uint16_t parent, uint16_t root)
    {
        uint16_t c = node;
        const uint16_t half_root_size = sizes[root] / 2;
        tree->ForEachNeighbor(
            node,
            [&](uint16_t child)
            {
                if (child != parent && !visited[child])
                {
                    if (sizes[child] > half_root_size)
                    {
                        c = find_centroid(child, node, root);
                        return ControlFlow::Break;
                    }
                }

                return ControlFlow::Continue;
            });

        return c;
    }

    constexpr void
    find_distances(uint16_t node, uint16_t parent, uint16_t depth)
    {
        if (depth > k) return;

        if (count.size() + 1 == depth)
        {
            count.push_back(1);
        }
        else
        {
            ++count[depth - 1];
        }

        tree->ForEachNeighbor(
            node,
            [&](uint16_t child)
            {
                if (child != parent && !visited[child])
                {
                    find_distances(child, node, depth + 1);
                }
            });
    }

    constexpr void count_target(
        uint16_t node,
        uint16_t parent,
        uint16_t depth,
        std::vector<uint16_t>& curr)
    {
        if (depth > k) return;
        result[node] += total[std::min<size_t>(k - depth, total.size() - 1)] -
                        curr[std::min<size_t>(k - depth, curr.size() - 1)];
        tree->ForEachNeighbor(
            node,
            [&](uint16_t child)
            {
                if (child != parent && !visited[child])
                {
                    count_target(child, node, depth + 1, curr);
                }
            });
    }

    constexpr void centroid_decomposition(uint16_t node)
    {
        active_prefixes.clear();

        sizes.clear();
        sizes.resize(n, 1);
        subtree_sizes(node, n);

        auto centroid = find_centroid(node, n, node);
        visited[centroid] = true;
        uint16_t maxlen = 1;
        tree->ForEachNeighbor(
            centroid,
            [&](uint16_t child)
            {
                if (visited[child]) return;
                count.clear();

                find_distances(child, centroid, 1);
                active_prefixes.insert(child);
                auto& child_prefix = prefixes[child];
                child_prefix = {0};
                for (auto v : count)
                {
                    child_prefix.push_back(child_prefix.back() + v);
                }
                maxlen = std::max(
                    maxlen,
                    static_cast<uint16_t>(child_prefix.size()));
            });

        total.resize(maxlen);
        std::ranges::fill(total, 1);

        for (uint16_t child : active_prefixes)
        {
            for (uint16_t i = 0; i != maxlen; ++i)
            {
                auto& child_prefixes = prefixes[child];
                total[i] += child_prefixes[std::min(
                    i,
                    static_cast<uint16_t>(child_prefixes.size() - 1))];
            }
        }

        result[centroid] +=
            total[std::min(k, static_cast<uint16_t>(total.size() - 1))];

        tree->ForEachNeighbor(
            centroid,
            [&](uint16_t child)
            {
                if (visited[child]) return;
                count_target(child, centroid, 1, prefixes[child]);
            });

        tree->ForEachNeighbor(
            centroid,
            [&](uint16_t child)
            {
                if (visited[child]) return;
                centroid_decomposition(child);
            });
    }

public:
    constexpr CentroidDecomposition() = default;

    [[nodiscard]] constexpr const std::vector<uint16_t>& get_result() const
    {
        return result;
    }

    constexpr void centroid_decomposition(
        const UndirectedTree& in_tree,
        uint16_t in_k)
    {
        tree = &in_tree;
        n = static_cast<uint16_t>(in_tree.nodes.size());
        k = in_k;
        visited.clear();
        visited.resize(n);
        result.clear();
        result.resize(n, 0);
        prefixes.resize(n);
        centroid_decomposition(0);
    }
};

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> maxTargetNodes(
        std::vector<std::vector<int>>& edges1,
        std::vector<std::vector<int>>& edges2,
        uint16_t k)
    {
        UndirectedTree tree;
        CentroidDecomposition cd;
        uint16_t max_count = 0;
        if (k > 0)
        {
            tree.InitFromEdges(edges2);
            cd.centroid_decomposition(tree, k - 1);
            max_count = *std::ranges::max_element(cd.get_result());
        }

        tree.InitFromEdges(edges1);
        cd.centroid_decomposition(tree, k);
        std::vector<int> result;
        result.resize(tree.nodes.size(), static_cast<int>(max_count));
        for (size_t i = 0; i != result.size(); ++i)
        {
            result[i] += static_cast<int>(cd.get_result()[i]);
        }

        return result;
    }
};

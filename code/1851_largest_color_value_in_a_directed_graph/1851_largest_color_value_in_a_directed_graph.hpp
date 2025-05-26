#pragma once

#include <algorithm>
#include <bitset>
#include <span>
#include <string>
#include <vector>

#define DEBUG_PRINT 0
#define CACHE_MEMORY 1
// #define ATTRS __attribute__((no_sanitize("all")))
#define ATTRS

#if DEBUG_PRINT
#include <print>
#endif

class SolutionImpl
{
public:
    enum class Error : uint8_t
    {
        Cycle
    };

    static constexpr uint8_t kNumColors = 26;

    struct Node
    {
        uint32_t children_offset = 0;
        uint32_t children_count = 0;
    };

    std::vector<Node> nodes;
    std::vector<uint32_t> all_children;
    std::bitset<100'000> visited;
    std::bitset<100'000> dfs_stack;
    std::vector<uint32_t> topological_order;
    std::vector<uint32_t> colors_counters;

    ATTRS void topSortDFS(uint32_t node_id)
    {
        [[unlikely]] if (dfs_stack[node_id])
        {
            throw Error::Cycle;  // NOLINT
        }

        if (visited[node_id]) return;

        dfs_stack[node_id] = true;
        visited[node_id] = true;
        const auto& node = nodes[node_id];
        const uint32_t child_index_end =
            node.children_offset + node.children_count;
        for (uint32_t child_index = node.children_offset;
             child_index != child_index_end;
             ++child_index)
        {
            uint32_t child_id = all_children[child_index];
            topSortDFS(child_id);
        }
        topological_order.push_back(node_id);
        dfs_stack[node_id] = false;
    }

    ATTRS void print_graph()
    {
#if DEBUG_PRINT
        for (size_t node_id = 0; node_id != nodes.size(); ++node_id)
        {
            auto& node = nodes[node_id];
            auto children = std::span{all_children}.subspan(
                node.children_offset,
                node.children_count);
            std::println("{}: {}", node_id, children);
        }
#endif
    }

    ATTRS void print_topological_order()
    {
#if DEBUG_PRINT
        std::println("Topological order: {}", topological_order);
#endif
    }

    ATTRS void topSort()
    {
        topological_order.clear();
        topological_order.reserve(nodes.size());
        visited = {};
        dfs_stack = {};

        uint32_t n = static_cast<uint32_t>(nodes.size());
        for (uint32_t node_id = 0; node_id != n; ++node_id)
        {
            if (!visited[node_id])
            {
                topSortDFS(node_id);
            }
        }
    }

    [[nodiscard]] ATTRS int largestPathValue(
        const std::string& colors,
        std::vector<std::vector<int>>& edges)
    {
        nodes.clear();
        nodes.resize(colors.size());
        all_children.resize(edges.size());

        // Count the number of children for each node
        // E
        for (auto& edge : edges)
        {
            auto from = std::bit_cast<uint32_t>(edge[0]);
            nodes[from].children_count += 1;
        }

        // Calculate the offset for children array for each node
        {
            uint32_t offset = 0;
            for (auto& node : nodes)
            {
                node.children_offset = offset;
                offset += std::exchange(node.children_count, 0);
            }
        }

        // Populate children arrays
        for (auto& edge : edges)
        {
            auto from_node_id = std::bit_cast<uint32_t>(edge[0]);
            auto to_node_id = std::bit_cast<uint32_t>(edge[1]);
            auto& from_node = nodes[from_node_id];
            all_children[from_node.children_offset + from_node.children_count] =
                to_node_id;
            from_node.children_count += 1;
        }

        print_graph();

        try
        {
            topSort();
        }
        catch (Error)
        {
            return -1;  // cycle detected
        }

        print_topological_order();

        colors_counters.clear();
        colors_counters.resize(nodes.size() * kNumColors);

        auto get_node_color_counters = [&](uint32_t node_id)
        {
            return std::span<uint32_t, kNumColors>{
                colors_counters.data() + node_id * 26,        // NOLINT
                colors_counters.data() + (node_id + 1) * 26,  // NOLINT
            };
        };

        uint32_t result = 0;
        for (const uint32_t node_id : topological_order)
        {
            auto node_color_counters = get_node_color_counters(node_id);

            const auto& node = nodes[node_id];
            const uint32_t child_index_end =
                node.children_offset + node.children_count;
            for (uint32_t child_index = node.children_offset;
                 child_index != child_index_end;
                 ++child_index)
            {
                uint32_t child_id = all_children[child_index];
                auto child_color_counters = get_node_color_counters(child_id);

                for (uint8_t i = 0; i != kNumColors; ++i)
                {
                    if (node_color_counters[i] < child_color_counters[i])
                    {
                        node_color_counters[i] = child_color_counters[i];
                        result = std::max(node_color_counters[i], result);
                    }
                }
            }

            const uint8_t node_color_index = (colors[node_id] - 'a') & 0xFF;
            node_color_counters[node_color_index] += 1;
            result = std::max(node_color_counters[node_color_index], result);
        }

        return static_cast<int>(result);
    }
};

class Solution
{
public:
    [[nodiscard]] static int largestPathValue(
        const std::string& colors,
        std::vector<std::vector<int>>& edges)
    {
#if CACHE_MEMORY
        static SolutionImpl impl{};
#else
        SolutionImpl impl{};
#endif
        return impl.largestPathValue(colors, edges);
    }
};

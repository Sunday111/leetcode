#include <bitset>
#include <cstdint>
#include <span>
#include <unordered_map>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

// n [1; 160]
// size(present), size(future) = n
// size(hierarchy) = n - 1
// hierarchy[i] -> [boss, sub]
// boss, sub -> [1, n]
// budget -> [1, 160]

struct Node
{
    u8 degree = 0;
    u8 offset = 0;
    u8 parent = 0;
};

class Solution
{
public:
    std::span<int> present;
    std::span<int> future;

    std::unordered_map<u32, int> memo;

    inline static Node nodes[161];
    inline static u8 links[160];
    inline static u8 topological_order[160];

    std::bitset<256> bought;
    std::bitset<256> visited;
    std::bitset<256> dfs_stack;

    u8 topological_index = 0;

    void topological_sort(u8 node_id)
    {
        if (visited[node_id]) return;

        dfs_stack[node_id] = true;
        visited[node_id] = true;
        const auto& node = nodes[node_id];
        const u8 child_index_end = node.offset + node.degree;
        for (u8 li = node.offset; li != child_index_end; ++li)
        {
            topological_sort(links[li]);
        }
        topological_order[topological_index++] = node_id;
        dfs_stack[node_id] = false;
    }

    int dfs(u8 i, u8 budget) noexcept
    {
        if (budget == 0 || i == 0xFF) return 0;

        int* r = nullptr;

        u8 employee = topological_order[i];
        bool discount = bought[nodes[employee].parent];
        {
            u32 key = employee;
            key = (key << 8) | u32{budget};
            key = (key << 1) | u32{discount};
            auto [it, added] = memo.try_emplace(key, 0);
            r = &it->second;
            if (!added) return *r;
        }

        int price = present[employee - 1] >> discount;
        if (price <= budget)
        {
            int profit = future[employee - 1] - price;

            bought[employee] = 1;
            *r = dfs(i - 1, (budget - price) & 0xFF) + profit;
            bought[employee] = 0;
        }

        *r = std::max(*r, dfs(i - 1, budget));

        return *r;
    }

    [[nodiscard]] int maxProfit(
        u32 n,
        std::vector<int>& present_,
        std::vector<int>& future_,
        [[maybe_unused]] std::vector<std::vector<int>>& hierarchy,
        u8 budget) noexcept
    {
        present = present_;
        future = future_;

        std::fill_n(nodes, n + 1, Node{});

        for (auto& edge : hierarchy)
        {
            u8 boss = edge[0] & 0xFF;
            u8 sub = edge[1] & 0xFF;
            ++nodes[boss].degree;
            nodes[sub].parent = boss;
        }

        u8 offset = 0;
        for (u8 id = 1; id <= n; ++id)
        {
            auto& node = nodes[id];
            node.offset = offset;
            offset += node.degree;
            node.degree = 0;
        }

        for (auto& edge : hierarchy)
        {
            u8 boss = edge[0] & 0xFF;
            u8 sub = edge[1] & 0xFF;
            u8 link_index = (nodes[boss].offset + nodes[boss].degree++) & 0xFF;
            links[link_index] = sub;
        }

        topological_sort(1);

        return dfs(--topological_index, budget);
    }
};

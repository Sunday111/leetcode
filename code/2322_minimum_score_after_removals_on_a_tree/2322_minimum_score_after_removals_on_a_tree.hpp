#pragma once

#include <span>
#include <vector>

#ifdef __GNUC__
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#define FORCE_INLINE inline
#endif

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

class Solution
{
public:
    static constexpr u16 kInvalid = ~0 & 0xFFFF;

    struct Node
    {
        u16 edges_offset = 0;
        u16 num_edges = 0;
        u16 in = 0;
        u16 out = 0;
        int xor_sum = 0;
    };

    std::array<Node, 1001> nodes{};
    std::array<u16, 2000> edges_arr{};
    std::span<const int> values;
    u16 timer = 0;

    constexpr void dfs(u16 node_id, u16 parent) noexcept
    {
        auto& node = nodes[node_id];
        node.in = timer++;
        node.xor_sum = values[node_id];
        const u16 end = nodes[node_id].edges_offset + nodes[node_id].num_edges;
        for (u16 i = nodes[node_id].edges_offset; i != end; ++i)
        {
            u16 neighbor = edges_arr[i];
            if (neighbor != parent)
            {
                dfs(neighbor, node_id);
                node.xor_sum ^= nodes[neighbor].xor_sum;
            }
        }
        node.out = timer++;
    }

    [[nodiscard]] FORCE_INLINE constexpr bool isAncestor(
        u16 ancestor,
        u16 descendant) const noexcept
    {
        return nodes[ancestor].in <= nodes[descendant].in &&
               nodes[descendant].out <= nodes[ancestor].out;
    }

    FORCE_INLINE static constexpr void swap_if_greater(int& a, int& b) noexcept
    {
        int cond = (a > b) ? ~0 : 0, mask = (a ^ b) & cond;
        a ^= mask, b ^= mask;
    }

    [[nodiscard]] FORCE_INLINE static constexpr int
    score(int x, int y, int z) noexcept
    {
        swap_if_greater(x, y);
        swap_if_greater(y, z);
        swap_if_greater(x, y);
        return z - x;
    }

    [[nodiscard]] constexpr int minimumScore(
        std::vector<int>& nums,
        std::vector<std::vector<int>>& edges) noexcept
    {
        u16 n = nums.size() & 0xFFFF;
        values = nums;

        for (auto& edge : edges)
        {
            u16 a = edge[0] & 0xFFFF, b = edge[1] & 0xFFFF;
            ++nodes[a].num_edges, ++nodes[b].num_edges;
        }

        u16 offset = 0;
        for (auto& node : nodes)
        {
            node.edges_offset = offset;
            offset += node.num_edges;
            node.num_edges = 0;
        }

        for (auto& edge : edges)
        {
            u16 a_idx = edge[0] & 0xFFFF, b_idx = edge[1] & 0xFFFF;
            auto& a = nodes[a_idx];
            auto& b = nodes[b_idx];
            edges_arr[a.edges_offset + a.num_edges++] = b_idx;
            edges_arr[b.edges_offset + b.num_edges++] = a_idx;
        }

        dfs(0, kInvalid);
        int total = nodes[0].xor_sum;
        int min_score = std::numeric_limits<int>::max();
        std::array<int, 4> decision;  // NOLINT

        for (u16 i = 1; i != n; i++)
        {
            const int a = nodes[i].xor_sum;
            for (u16 j = i + 1; j != n; j++)
            {
                int b = nodes[j].xor_sum, ab = a ^ b;
                decision[0b00] = score(a, b, total ^ ab);
                decision[0b01] = score(b, ab, total ^ a);
                decision[0b10] = score(a, ab, total ^ b);
                swap_if_greater(
                    min_score,
                    decision
                        [u32{isAncestor(i, j)} | (u32{isAncestor(j, i)} << 1)]);
            }
        }
        return min_score;
    }
};

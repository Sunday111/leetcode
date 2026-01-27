#include <algorithm>
#include <vector>

using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

#define FORCE_INLINE inline __attribute__((always_inline))

class Solution
{
public:
    struct Link
    {
        u16 id;
        u16 weight;
    };

    struct Node
    {
        u32 offset{};
        u32 degree{};
        u32 min_dist = ~u32{};
        u32 min_queued = ~u32{};
    };

    [[nodiscard]] FORCE_INLINE static u64 pack(u16 id, u32 w) noexcept
    {
        return (u64{w} << 16) | u64{id};
    }

    [[nodiscard]] FORCE_INLINE static std::pair<u16, u32> unpack(
        u64 packed) noexcept
    {
        return {packed & 0xFFFF, static_cast<u32>(packed >> 16)};
    }

    [[nodiscard]] static constexpr int minCost(
        u32 n,
        const std::vector<std::vector<int>>& edges) noexcept
    {
        static Link links[200'000];
        static Node nodes[50'000];

        std::ranges::fill_n(nodes, n, Node{});

        for (auto& edge : edges)
        {
            u16 src = edge[0] & 0xFFFF;
            u16 dst = edge[1] & 0xFFFF;

            nodes[src].degree += 1;
            nodes[dst].degree += 1;
        }

        for (u32 offset = 0, i = 0; i != n; ++i)
        {
            auto& node = nodes[i];
            node.offset = offset;
            offset += node.degree;
            node.degree = 0;
        }

        for (auto& edge : edges)
        {
            u16 src_id = edge[0] & 0xFFFF;
            u16 dst_id = edge[1] & 0xFFFF;
            u16 weight = edge[2] & 0xFFFF;
            auto &src = nodes[src_id], &dst = nodes[dst_id];
            links[src.offset + src.degree++] = {.id = dst_id, .weight = weight};
            weight *= 2;
            links[dst.offset + dst.degree++] = {.id = src_id, .weight = weight};
        }

        static u64 q[200'000];
        u32 qs = 0;

        q[qs++] = 0;

        const u32 target = n - 1;

        while (qs)
        {
            std::ranges::pop_heap(q, q + qs, std::greater{});
            auto [node_id, dist] = unpack(q[--qs]);
            if (node_id == target) return static_cast<int>(dist);

            auto& node = nodes[node_id];

            if (dist > node.min_dist) continue;
            node.min_dist = dist;

            for (u32 link_index = node.offset,
                     link_end = link_index + node.degree;
                 link_index != link_end;
                 ++link_index)
            {
                auto& link = links[link_index];
                u32 new_dist = dist + link.weight;
                if (new_dist < nodes[link.id].min_queued)
                {
                    nodes[link.id].min_queued = new_dist;
                    q[qs++] = pack(link.id, new_dist);
                    std::ranges::push_heap(q, q + qs, std::greater{});
                }
            }
        }

        return -1;
    }
};

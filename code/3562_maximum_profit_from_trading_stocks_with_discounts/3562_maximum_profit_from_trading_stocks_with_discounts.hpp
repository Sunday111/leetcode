#include <algorithm>
#include <cassert>
#include <span>
#include <vector>

#include "force_inline.hpp"
#include "integral_aliases.hpp"

template <typename T>
FORCE_INLINE constexpr void acc_max(T& acc, T val) noexcept
{
    acc = std::max(acc, val);
}

class Solution  // NOLINT
{
public:
    inline static std::array<int, 161 * 3> tmp_buf;
    inline static std::array<u8, 161> node_deg;
    inline static std::array<u8, 161> node_offset;
    inline static std::array<u8, 161> links;
    inline static std::array<int, 161 * 161 * 2> nodes_profits_buf;

    u8 budget, b1 = 0;
    int *regular, *discounted, *merged;
    const int* present;
    const int* future;

    void merge_knapsack(int* dst, const int* src) noexcept
    {
        constexpr auto bad = std::numeric_limits<int>::lowest();
        std::fill_n(merged, b1, bad);

        for (u32 bi = 0; bi <= budget; ++bi)
        {
            if (dst[bi] == bad) continue;

            for (u32 bj = 0; bj + bi <= budget; ++bj)
            {
                if (src[bj] == bad) continue;

                const u32 nb = bi + bj;
                const int val = dst[bi] + src[bj];
                merged[nb] = std::max(merged[nb], val);
            }
        }

        std::copy_n(merged, b1, dst);
    }

    FORCE_INLINE std::pair<int*, int*> get_node_profits(u8 node_id) noexcept
    {
        auto base = nodes_profits_buf.data() + u32{b1} * u32{node_id} * 2;
        return {base, base + b1};
    }

    FORCE_INLINE std::pair<u8*, u8*> children(u8 node_id) noexcept
    {
        u8* begin = links.data() + node_offset[node_id];
        return {begin, begin + node_deg[node_id]};
    }

    void computeProfits(u8 node_id) noexcept
    {
        for (auto [child, end] = children(node_id); child != end; ++child)
        {
            computeProfits(*child);
        }

        std::fill_n(regular, b1, 0);
        std::fill_n(discounted, b1, 0);
        for (auto [child, end] = children(node_id); child != end; ++child)
        {
            auto [child_regular, child_discounted] = get_node_profits(*child);
            merge_knapsack(regular, child_regular);
            merge_knapsack(discounted, child_discounted);
        }

        // Merge children profits
        auto [node_regular, node_discounted] = get_node_profits(node_id);

        // Case 1: Take without discount
        const int regular_price = present[node_id - 1];
        const int regular_profit = future[node_id - 1] - regular_price;
        for (u8 p = std::min<u8>(regular_price & 0xFF, b1), b = p; b != b1; ++b)
        {
            acc_max(node_regular[b], discounted[b - p] + regular_profit);
        }

        // Case 2: Ignore non-discounted stock
        for (u8 b = 0; b != b1; ++b)
        {
            acc_max(node_regular[b], regular[b]);
        }

        // Case 3: Take discounted stock
        const int discounted_price = regular_price / 2;
        const int discounted_profit = future[node_id - 1] - discounted_price;
        for (u8 p = std::min<u8>(discounted_price & 0xFF, b1), b = p; b != b1;
             ++b)
        {
            acc_max(node_discounted[b], discounted[b - p] + discounted_profit);
        }

        // Case 4: Ignore discounted stock.
        for (u8 b = 0; b != b1; ++b)
        {
            acc_max(node_discounted[b], regular[b]);
        }
    }

    void buildGraph(u8 n1, const std::vector<std::vector<int>>& hierarchy)
    {
        for (auto& edge : hierarchy)
        {
            u8 parent = edge[0] & 0xFF;
            node_deg[parent]++;
        }

        for (u8 offset = 0, node_id = 0; node_id != n1; ++node_id)
        {
            node_offset[node_id] = offset;
            offset += node_deg[node_id];
            node_deg[node_id] = 0;
        }

        for (auto& edge : hierarchy)
        {
            u8 parent = edge[0] & 0xFF;
            u8 child = edge[1] & 0xFF;
            u8 link_index = node_offset[parent] + node_deg[parent]++;
            links[link_index] = child;
        }
    }

    [[nodiscard]] int maxProfit(
        u8 n,
        const std::vector<int>& present_,
        const std::vector<int>& future_,
        const std::vector<std::vector<int>>& hierarchy,
        u8 budget_) noexcept
    {
        budget = budget_, b1 = (budget + 1) & 0xFF;
        present = present_.data();
        future = future_.data();

        regular = tmp_buf.data() + 0 * b1;
        discounted = tmp_buf.data() + 1 * b1;
        merged = tmp_buf.data() + 2 * b1;

        u8 n1 = n + 1u;
        std::fill_n(nodes_profits_buf.begin(), u32{n1} * u32{b1} * 2, 0);
        std::fill_n(node_deg.begin(), n1, 0);
        std::fill_n(node_offset.begin(), n1, 0);

        buildGraph(n1, hierarchy);

        // 1 is always the root and all nodes are reachable
        computeProfits(1);

        auto [root_regular, root_discounted] = get_node_profits(1);
        return std::ranges::max(std::span{root_regular, root_regular + b1});
    }
};

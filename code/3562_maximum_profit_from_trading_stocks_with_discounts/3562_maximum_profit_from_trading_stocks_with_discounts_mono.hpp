#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <ranges>
#include <span>
#include <unordered_map>
#include <utility>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

template <typename To>
inline static constexpr auto cast = []<typename From>(From&& v) INLINE_LAMBDA
{
    return static_cast<To>(std::forward<From>(v));
};

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

template <typename T>
FORCE_INLINE constexpr void acc_max(T& acc, T val) noexcept
{
    acc = std::max(acc, val);
}

class Solution
{
public:
    struct Node
    {
        std::vector<u8> children;

        // Index is budget, value is profit
        std::array<int, 161> regular{};
        std::array<int, 161> discounted{};
    };

    std::span<const int> present, future;

    std::vector<Node> g;
    u8 budget = 0;
    u8 b1 = 0;
    // merged from children
    std::array<int, 161 * 3> shared_buf;
    int *regular, *discounted, *merged;

    void merge_knapsack(int* dst, const int* src) noexcept
    {
        std::fill_n(merged, b1, 0);

        for (u8 bi = 0; bi <= budget; ++bi)
        {
            for (u8 bj = 0; bj + bi <= budget; ++bj)
            {
                acc_max(merged[bi + bj], dst[bi] + src[bj]);
            }
        }

        std::copy_n(merged, b1, dst);
    }

    void computeProfits(u8 node_id) noexcept
    {
        auto& node = g[node_id];
        for (u8 child_id : node.children)
        {
            computeProfits(child_id);
        }

        std::fill_n(regular, b1, 0);
        std::fill_n(discounted, b1, 0);
        for (u8 child_id : node.children)
        {
            merge_knapsack(regular, g[child_id].regular.data());
        }

        for (u8 child_id : node.children)
        {
            merge_knapsack(discounted, g[child_id].discounted.data());
        }

        const int regular_price = present[node_id - 1];
        const int discounted_price = regular_price / 2;
        const int regular_profit = future[node_id - 1] - regular_price;
        const int discounted_profit = future[node_id - 1] - discounted_price;

        // Case 1: Take discounted stock
        for (u8 p = discounted_price & 0xFF, b = p; b <= budget; ++b)
        {
            acc_max(node.discounted[b], discounted[b - p] + discounted_profit);
        }

        // Case 2: Ignore discounted stock.
        for (u8 b = 0; b <= budget; ++b)
        {
            acc_max(node.discounted[b], regular[b]);
        }

        // Case 3: Take without discount
        for (u8 p = regular_price & 0xFF, b = p; b <= budget; ++b)
        {
            acc_max(node.regular[b], discounted[b - p] + regular_profit);
        }

        // Case 4: Ignore non-discounted stock
        for (u8 b = 0; b <= budget; ++b)
        {
            acc_max(node.regular[b], regular[b]);
        }
    }

    [[nodiscard]] int maxProfit(
        u8 n,
        std::vector<int>& present_,
        std::vector<int>& future_,
        [[maybe_unused]] std::vector<std::vector<int>>& hierarchy,
        u8 budget_) noexcept
    {
        g.clear();
        g.resize(n + 1);
        budget = budget_;
        present = present_;
        future = future_;
        b1 = (budget + 1) & 0xFF;

        regular = shared_buf.data();
        discounted = regular + b1;
        merged = discounted + b1;

        for (auto& edge : hierarchy)
        {
            u8 parent = edge[0] & 0xFF;
            u8 child = edge[1] & 0xFF;
            g[parent].children.push_back(child);
        }

        // 1 is always the root and all nodes are reachable
        computeProfits(1);

        return std::ranges::max(g[1].regular);
    }
};

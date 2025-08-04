#pragma once

#include <algorithm>
#include <array>
#include <span>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

template <std::integral Int>
FORCE_INLINE static constexpr void swap_if_greater(Int& a, Int& b) noexcept
{
    Int cond = (a > b) ? ~Int{0} : 0;
    Int mask = (a ^ b) & cond;
    a ^= mask, b ^= mask;
}

class Solution
{
public:
    using u32 = uint32_t;
    using i32 = int32_t;

    struct FruitTree
    {
        u32 pos;
        u32 amount;
    };

    [[nodiscard]] static constexpr u32
    maxTotalFruits(std::span<FruitTree> trees, u32 start_pos, u32 k) noexcept
    {
        u32 max_sum = 0, sum = 0;
        auto begin = trees.begin(), end = begin;

        // Consider all cases where we have to go to the left
        while (begin->pos < start_pos)
        {
            u32 lo_steps = start_pos - begin->pos;
            u32 hi_steps = std::max(end->pos, start_pos) - start_pos;
            swap_if_greater(lo_steps, hi_steps);
            if (u32 min_steps = 2 * lo_steps + hi_steps; min_steps > k)
            {
                sum -= begin++->amount;
            }
            else
            {
                sum += end++->amount;
                max_sum = std::max(max_sum, sum);
            }
        }

        // How far we can go considering only trees to the right of starting
        // point. Could have been part of previous loop but this separation
        // removes a few corner cases checks and looks simpler imo.
        while (end->pos <= start_pos + k)
        {
            sum += end->amount;
            ++end;
        }

        return std::max(sum, max_sum);
    }

    [[nodiscard]] static u32 maxTotalFruits(
        std::vector<std::vector<int>>& fruits,
        u32 start_pos,
        u32 k) noexcept
    {
        static std::array<FruitTree, 100'001> trees;
        u32 n = 0;

        // Convert to a flat array. Filter away impossible options
        // and put a sentinel value at the end to avoid != .end checks
        {
            u32 min_pos = start_pos - std::min(start_pos, k);
            u32 max_pos = start_pos + k;
            for (auto& fruit : fruits)
            {
                u32 pos = static_cast<u32>(fruit[0]);
                if (pos < min_pos) continue;
                if (pos > max_pos) break;
                trees[n++] = {
                    .pos = pos,
                    .amount = static_cast<u32>(fruit[1]),
                };
            }
            trees[n++] = {
                .pos = (~u32{0}) - 200000,
                .amount = 0,
            };
        }

        return maxTotalFruits(std::span{trees}.first(n), start_pos, k);
    }
};

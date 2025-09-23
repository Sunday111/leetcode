#pragma once

#include <algorithm>
#include <span>
#include <utility>
#include <vector>

#include "radix_sorter.hpp"

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr u32 maxFrequency(
        std::vector<int>& nums_,
        const u32 k,
        const u32 numOperations) noexcept
    {
        const std::span<u32> nums{
            reinterpret_cast<u32*>(nums_.data()),  // NOLINT
            nums_.size(),
        };
        radix_sort<u32, SortOrder::Ascending, 7, 3>(nums);

        u32 r = 0;

        auto lo = nums.begin(), hi = lo, t = lo;

        for (auto it = nums.begin(); it != nums.end();)
        {
            auto v_begin = it;
            u32 v = *it;

            u32 freq = 0;
            do
            {
                ++it;
                ++freq;
            } while (it != nums.end() && *it == v);

            u32 left = v - std::min(v, k), right = v + k;
            while (*lo < left) ++lo;
            hi = std::max(hi, it);
            while (hi != nums.end() && *hi <= right) ++hi;
            if (std::cmp_less_equal(std::distance(lo, nums.end()), r)) break;
            u32 num_in_range = static_cast<u32>(std::distance(lo, hi));
            u32 possible_freq =
                freq + std::min(num_in_range - freq, numOperations);
            r = std::max(possible_freq, r);

            if (*(hi - 1) != v + k)
            {
                t = std::max(t, hi);
                u32 ahead = v + 2 * k;
                while (t != nums.end() && *t <= ahead) ++t;
                num_in_range = static_cast<u32>(std::distance(v_begin, t));
                possible_freq = std::min(num_in_range, numOperations);
                r = std::max(possible_freq, r);
            }
        }

        return r;
    }
};

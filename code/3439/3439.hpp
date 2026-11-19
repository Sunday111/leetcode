#pragma once

#include <span>
#include <vector>

using i32 = int32_t;
using u32 = uint32_t;

class Solution
{
public:
    [[nodiscard]] static constexpr u32 maxFreeTime(
        u32 event_time,
        u32 k,
        std::vector<int>& start_,
        std::vector<int>& finish_) noexcept
    {
        std::span<u32> start{
            reinterpret_cast<std::vector<u32>&>(start_)};  // NOLINT
        std::span<u32> finish{
            reinterpret_cast<std::vector<u32>&>(finish_)};  // NOLINT
        static std::array<u32, 100'001> gaps;               // NOLINT
        u32 n_gaps = 0;
        gaps[n_gaps++] = start.front();
        const u32 n = static_cast<u32>(start_.size());
        for (u32 i = 1; i != n; ++i) gaps[n_gaps++] = start[i] - finish[i - 1];
        gaps[n_gaps++] = event_time - finish.back();

        u32 i = 0;
        u32 j = 0;
        u32 sum = 0;
        u32 max_sum = 0;
        while (j != n_gaps)
        {
            u32 t = j - i;
            if (t <= k)
            {
                sum += gaps[j++];
                max_sum = std::max(sum, max_sum);
            }
            else
            {
                sum -= gaps[i++];
            }
        }

        return max_sum;
    }
};

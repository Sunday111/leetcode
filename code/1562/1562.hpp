#pragma once

#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    static constexpr u32 kInvalidIndex = std::numeric_limits<u32>::max();

    struct Interval
    {
        u32 begin, end;
    };

    [[nodiscard]] static constexpr int findLatestStep(
        std::vector<int>& arr,
        u32 m)
    {
        const u32 n = static_cast<u32>(arr.size());

        if (m == n) return static_cast<int>(m);

        std::vector<Interval> intervals(n);
        u32 next_interval = 0;

        std::vector<u32> idx_to_interval(n, kInvalidIndex);

        u32 t = 0;
        u32 num_m_sized = 0;
        int result = -1;

        for (int v : arr)
        {
            const u32 i = static_cast<u32>(v - 1);
            const u32 i_interval_idx = next_interval++;

            auto& i_interval = intervals[i_interval_idx];
            idx_to_interval[i] = i_interval_idx;

            i_interval.begin = i;
            i_interval.end = i + 1;

            // for left and right neighbors of i we check if they already belong
            // to some interval, which means they were already set to 1.
            // if thats the case - merge them with the current interval
            // and check the size of interval being merged

            if (const u32 left = i - 1;
                left != kInvalidIndex && idx_to_interval[left] != kInvalidIndex)
            {
                const auto& left_interval = intervals[idx_to_interval[left]];
                i_interval.begin = left_interval.begin;
                idx_to_interval[i_interval.begin] = i_interval_idx;
                if (u32 len = left_interval.end - left_interval.begin; len == m)
                {
                    if (--num_m_sized == 0) result = static_cast<int>(t);
                }
            }

            if (const u32 right = i + 1;
                right != n && idx_to_interval[right] != kInvalidIndex)
            {
                const auto& right_interval = intervals[idx_to_interval[right]];
                i_interval.end = right_interval.end;
                idx_to_interval[i_interval.end - 1] = i_interval_idx;
                if (u32 len = right_interval.end - right_interval.begin;
                    len == m)
                {
                    if (--num_m_sized == 0) result = static_cast<int>(t);
                }
            }

            if (auto len = i_interval.end - i_interval.begin; len == m)
            {
                ++num_m_sized;
            }

            ++t;
        }

        return result;
    }
};

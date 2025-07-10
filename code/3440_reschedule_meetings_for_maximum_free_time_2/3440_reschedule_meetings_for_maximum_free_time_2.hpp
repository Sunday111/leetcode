#pragma once

#include <array>
#include <vector>

class Solution
{
public:
    // Swap if a > b
    static constexpr void __attribute__((always_inline)) swap_if_greater(
        int& a,
        int& b)
    {
        int cond = (a > b) ? ~0 : 0;
        int mask = (a ^ b) & cond;
        a ^= mask;
        b ^= mask;
    }

    static constexpr void __attribute__((always_inline)) consider(
        std::array<int, 3>& biggest_gaps,
        int& r,
        int duration,
        int gap_a,
        int gap_b)
    {
        int add_cnt = 0, ca = 0, cb = 0;

#pragma GCC unroll 3
        for (auto g : biggest_gaps)
        {
            add_cnt += g >= duration;
            ca |= g >= duration && g == gap_a;
            cb |= g >= duration && g == gap_b;
        }

        int v = gap_a + gap_b + duration * (add_cnt > (ca + cb));
        swap_if_greater(v, r);
    }

    [[nodiscard]] static constexpr int maxFreeTime(
        int event_time,
        std::vector<int>& start,
        std::vector<int>& finish) noexcept
    {
        std::array<int, 3> biggest_gaps{};
        auto add_gap = [&](int gap)
        {
            swap_if_greater(gap, biggest_gaps[2]);
            swap_if_greater(gap, biggest_gaps[1]);
            swap_if_greater(gap, biggest_gaps[0]);
        };

        add_gap(start.front());
        using u32 = uint32_t;
        const u32 n = static_cast<u32>(start.size());
        for (u32 i = 1; i != n; ++i) add_gap(start[i] - finish[i - 1]);
        add_gap(event_time - finish.back());

        int r = 0;
        {
            int curr_start = start[0];
            int curr_finish = finish[0];
            int next_start = start[1];
            int prev_finish = 0;
            consider(
                biggest_gaps,
                r,
                curr_finish - curr_start,
                curr_start - prev_finish,
                next_start - curr_finish);
        }

        {
            int curr_start = start[n - 1];
            int curr_finish = finish[n - 1];
            int next_start = event_time;
            int prev_finish = finish[n - 2];
            consider(
                biggest_gaps,
                r,
                curr_finish - curr_start,
                curr_start - prev_finish,
                next_start - curr_finish);
        }

        for (u32 i = 1; i != n - 1; ++i)
        {
            int curr_start = start[i];
            int curr_finish = finish[i];
            int next_start = start[i + 1];
            int prev_finish = finish[i - 1];
            consider(
                biggest_gaps,
                r,
                curr_finish - curr_start,
                curr_start - prev_finish,
                next_start - curr_finish);
        }

        return r;
    }
};

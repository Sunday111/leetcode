#pragma once

#include <algorithm>
#include <span>
#include <vector>

using u32 = uint32_t;
using u64 = uint64_t;

#ifdef __GNUC__
#define ATTR inline __attribute__((always_inline))
#else
#define ATTR inline
#endif

class Solution
{
public:
    ATTR static u32&
    index(std::array<u32, 2'000'000>& data, u32 i, u32 j, u32 k) noexcept
    {
        return data[i * (k + 1) + j];
    }

    ATTR static constexpr u32 maxValue(
        std::vector<std::vector<int>>& events_,
        u32 k) noexcept
    {
        auto events = std::span{
            reinterpret_cast<std::vector<std::vector<u32>>&>(  // NOLINT
                events_)};
        std::ranges::sort(events, [](auto& a, auto& b) { return a[0] < b[0]; });

        std::array<u32, 2'000'000> dp{};
        const u32 n = static_cast<u32>(events.size());

        u32 r = 0;
        u32 i = n;
        do
        {
            --i;

            const u32 next_i = static_cast<u32>(std::distance(
                events.begin(),
                std::ranges::lower_bound(
                    events.begin() + i,
                    events.end(),
                    events[i][1] + 1,
                    std::less{},
                    [](const auto& e) { return e.front(); })));

            const u32 event_val = events[i][2];
            for (u32 j = 1; j <= k; ++j)
            {
                u32 skip_current = index(dp, i + 1, j, k);
                u32 take_current = event_val + index(dp, next_i, j - 1, k);
                index(dp, i, j, k) = std::max(skip_current, take_current);
                r = std::max(r, index(dp, i, j, k));
            }

        } while (i);

        return r;
    }
};

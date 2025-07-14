#pragma once

#include <algorithm>
#include <span>
#include <vector>

using u32 = uint32_t;

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

    struct Event
    {
        u32 begin;
        u32 end;
        u32 value;
    };

    inline static std::array<Event, 1'000'000> events_array;

    ATTR static constexpr u32 maxValue(
        std::vector<std::vector<int>>& events_,
        u32 k) noexcept
    {
        u32 n = 0;
        for (auto& e : events_)
        {
            events_array[n++] = Event{
                .begin = static_cast<u32>(e[0]),
                .end = static_cast<u32>(e[1]),
                .value = static_cast<u32>(e[2]),
            };
        }

        auto events = std::span{events_array}.first(n);
        std::ranges::sort(events, std::less{}, &Event::begin);

        std::array<u32, 2'000'000> dp{};

        u32 r = 0;
        for (u32 i = n; i--;)
        {
            const u32 next_i = static_cast<u32>(std::distance(
                events.begin(),
                std::ranges::lower_bound(
                    events.begin() + i,
                    events.end(),
                    events[i].end + 1,
                    std::less{},
                    &Event::begin)));

            const u32 event_val = events[i].value;
            for (u32 j = 1; j <= k; ++j)
            {
                u32 skip_current = index(dp, i + 1, j, k);
                u32 take_current = event_val + index(dp, next_i, j - 1, k);
                index(dp, i, j, k) = std::max(skip_current, take_current);
                r = std::max(r, index(dp, i, j, k));
            }
        }

        return r;
    }
};

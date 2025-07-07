#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <span>
#include <vector>

using u8 = uint8_t;
using u32 = uint32_t;

#ifdef __GNUC__
#define ATTR inline __attribute__((always_inline))
#else
#define ATTR inline
#endif

class Solution
{
public:
    struct Event
    {
        u32 begin;
        u32 end;
    };

    [[nodiscard]] ATTR static std::span<Event> to_events_span(
        const std::vector<std::vector<int>>& in_events) noexcept
    {
        static std::array<Event, 100'001> arr;  // NOLINT

        uint32_t n = 0;
        for (auto& e : in_events)
        {
            auto& val = arr[n++];
            val.begin = std::bit_cast<u32>(e[0]);
            val.end = std::bit_cast<u32>(e[1]) + 1;
        }

        return std::span{arr}.first(n);
    }

    [[nodiscard]] static u32 maxEvents(
        const std::vector<std::vector<int>>& in_events) noexcept
    {
        const auto events = to_events_span(in_events);
        std::ranges::sort(events, std::less{}, &Event::begin);

        u32 r = 0;
        const u32 n = static_cast<u32>(events.size());

        std::vector<Event> heap;
        constexpr auto heap_comp = std::greater{};
        constexpr auto heap_proj = &Event::end;
        heap.reserve(n);

        u32 next_available_day = 0;
        for (const auto& next_event : events)
        {
            // Attend events
            while (!heap.empty() && next_available_day < next_event.begin)
            {
                auto& event = heap.front();
                if (event.end > next_available_day)
                {
                    ++r;
                    ++next_available_day;
                }

                std::ranges::pop_heap(heap, heap_comp, heap_proj);
                heap.pop_back();
            }

            assert(next_available_day <= next_event.begin);
            next_available_day = next_event.begin;
            heap.push_back(next_event);
            std::ranges::push_heap(heap, heap_comp, heap_proj);
        }

        while (!heap.empty())
        {
            auto& event = heap.front();
            if (event.end > next_available_day)
            {
                ++r;
                ++next_available_day;
            }
            std::ranges::pop_heap(heap, heap_comp, heap_proj);
            heap.pop_back();
        }

        return r;
    }
};

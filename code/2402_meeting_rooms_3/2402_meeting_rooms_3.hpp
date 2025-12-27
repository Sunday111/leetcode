#pragma once

#include <algorithm>
#include <span>
#include <vector>

#include "int_if.hpp"
#include "integral_aliases.hpp"
#include "radix_sorter.hpp"
#include "reinterpret_range.hpp"

class Solution
{
public:
    struct Meeting
    {
        u64 end : 20;
        u64 begin : 20;
        u64 placeholder : 20;
    };

    struct Booking
    {
        u64 room : 7;
        u64 end_time : 57;
    };

    FORCE_INLINE static constexpr auto heap_cmp(Booking a, Booking b) noexcept
    {
        return std::bit_cast<u64>(a) > std::bit_cast<u64>(b);
    };

    FORCE_INLINE static constexpr void bitsetClear(
        std::array<u64, 2>& bs,
        u8 idx) noexcept
    {
        bs[idx > 63] &= ~(u64{1} << (idx & 63));
    }

    FORCE_INLINE static constexpr void bitsetSet(
        std::array<u64, 2>& bs,
        u8 idx) noexcept
    {
        bs[idx > 63] |= u64{1} << iif<u8>(idx > 63, idx - 64, idx);
    }

    FORCE_INLINE static constexpr u8 bitsetFindFirstZero(
        std::array<u64, 2>& bs) noexcept
    {
        auto a = std::countr_one(bs[0]);
        auto b = std::countr_one(bs[1]);
        return iif(a < 64, a, b + 64) & 0xFF;
    }

    [[nodiscard]] static u32 mostBooked(
        u32 num_rooms,
        const std::vector<std::vector<int>>& in_meetings) noexcept
    {
        static std::array<Meeting, 100'001> meettings_arr;
        const u32 num_meetings = static_cast<u32>(in_meetings.size());

        for (u32 i = 0; i != num_meetings; ++i)
        {
            const auto& src = in_meetings[i];
            meettings_arr[i] = {
                .end = std::bit_cast<u32>(src[1]),
                .begin = std::bit_cast<u32>(src[0]),
                .placeholder{},
            };
        }

        const auto meetings = std::span{meettings_arr}.first(num_meetings);

        // Choose between the std::sort (expect nlogn) and
        // different sets of parameters for radix sort
        {
            using SortFn = void (*)(std::span<u64>);

            auto radix_sort_weight =
                [num_meetings](u32 bits_per_pass, u32 num_passes)
            {
                return num_passes * ((1u << bits_per_pass) + num_meetings);
            };

            using WeightAndFn = std::pair<u32, SortFn>;
            std::array<WeightAndFn, 6> fns{{
                {num_meetings * cast<u32>(32 - std::countl_zero(num_meetings)),
                 [](std::span<u64> x) { std::ranges::sort(x); }},
                {radix_sort_weight(6, 7),
                 [](std::span<u64> x) { radix_sort<7, 6>(x); }},
                {radix_sort_weight(7, 6),
                 [](std::span<u64> x) { radix_sort<7, 6>(x); }},
                {radix_sort_weight(8, 5),
                 [](std::span<u64> x) { radix_sort<8, 5>(x); }},
                {radix_sort_weight(10, 4),
                 [](std::span<u64> x) { radix_sort<10, 4>(x); }},
                {radix_sort_weight(13, 3),
                 [](std::span<u64> x) { radix_sort<13, 3>(x); }},
            }};

            std::ranges::min(fns, std::less{}, &WeightAndFn::first)
                .second(reinterpret_range<u64>(meetings));
        }

        if (auto n = num_meetings, log_n = cast<u32>(32 - std::countl_zero(n));
            n * log_n < 5u * ((1u << 8) + n))
        {
            std::ranges::sort(reinterpret_range<u64>(meetings));
        }
        else
        {
            radix_sort<8, 5>(reinterpret_range<u64>(meetings));
        }

        Booking* const heap_arr = reinterpret_cast<Booking*>(meetings.data());
        u32 heap_size = 0;

        std::array<int, 100> rooms{};

        // zero bit means room is free
        std::array<u64, 2> bs{};

        for (const auto& meeting : meetings)
        {
            // pop meetings that end earlier than this event start
            while (heap_size && meeting.begin >= heap_arr->end_time)
            {
                bitsetClear(bs, heap_arr->room);
                std::ranges::pop_heap(heap_arr, heap_arr + heap_size, heap_cmp);
                --heap_size;
            }

            u64 start = meeting.begin;
            u8 room = bitsetFindFirstZero(bs);
            if (room == num_rooms)
            {
                auto booking = *heap_arr;
                std::ranges::pop_heap(heap_arr, heap_arr + heap_size, heap_cmp);
                --heap_size;
                start = booking.end_time;
                room = booking.room;
            }
            else
            {
                bitsetSet(bs, room);
            }

            ++rooms[room];
            heap_arr[heap_size++] = {
                .room = room,
                .end_time = start + (meeting.end - meeting.begin),
            };
            std::ranges::push_heap(heap_arr, heap_arr + heap_size, heap_cmp);
        }

        return static_cast<u32>(std::distance(
            rooms.begin(),
            std::max_element(rooms.begin(), rooms.begin() + num_rooms)));
    }
};

#include "sync_stdio.hpp"

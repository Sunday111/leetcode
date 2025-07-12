#pragma once

#include <algorithm>
#include <span>
#include <vector>

#ifdef __GNUC__
#define ATTR inline __attribute__((always_inline))
#else
#define ATTR inline
#endif

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;

template <
    std::unsigned_integral T,
    u8 bits_per_pass,
    u32 num_passes = ((63 + bits_per_pass) / bits_per_pass)>
struct RadixSorter
{
    [[nodiscard]] static std::vector<T>& get_static_data() noexcept
    {
        static std::vector<T> v;
        v.reserve(100'001);
        return v;
    }

    static constexpr u64 base = 1u << bits_per_pass;
    static constexpr u64 mask = base - 1;

    template <u8 pass>
    ATTR static void radixSortPass(
        std::span<u64> arr,
        std::array<u64, base>& count) noexcept
    {
        auto& temp = get_static_data();

        count.fill(0);
        constexpr u64 shift = pass * bits_per_pass;

        // Count digit occurrences
        for (auto v : arr) ++count[(v >> shift) & mask];

        // Prefix sums for positions
        for (u32 i = 1; i < base; ++i) count[i] += count[i - 1];

        // Stable placement
        u32 i = static_cast<u32>(arr.size());
        do
        {
            --i;
            u32 digit = (arr[i] >> shift) & mask;
            temp[--count[digit]] = arr[i];
        } while (i);

        std::ranges::copy(temp, arr.begin());
    }

    ATTR static void radixSort(std::span<u64> arr) noexcept
    {
        u32 n = static_cast<u32>(arr.size());
        if (n == 0) return;

        auto& temp = get_static_data();
        temp.clear();
        temp.resize(n);

        std::array<u64, base> count{};

        [&]<u8... pass>(std::integer_sequence<u8, pass...>)
        {
            (radixSortPass<pass>(arr, count), ...);
        }(std::make_integer_sequence<u8, num_passes>());
    }
};

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

    template <typename To, typename From, size_t extent = std::dynamic_extent>
    [[nodiscard]] ATTR static auto reinterpret_span(
        std::span<From, extent> in) noexcept
    {
        return std::span<To, extent>{
            reinterpret_cast<To*>(in.data()),  // NOLINT
            in.size()};
    }

    static constexpr auto heap_cmp = [](const Booking& a, const Booking& b)
    {
        if (a.end_time != b.end_time) return a.end_time > b.end_time;
        return a.room > b.room;
    };

    ATTR static constexpr void bitsetClear(
        std::array<u64, 2>& bs,
        u8 idx) noexcept
    {
        u64& v = idx < 64 ? bs[0] : bs[1];
        u64 i = idx % 64;
        v &= ~(u64{1} << i);
    }

    ATTR static constexpr void bitsetSet(
        std::array<u64, 2>& bs,
        u8 idx) noexcept
    {
        u64& v = idx < 64 ? bs[0] : bs[1];
        u32 i = idx < 64 ? idx : idx - 64;
        v |= u64{1} << i;
    }

    ATTR static constexpr u8 bitsetFindFirstZero(
        std::array<u64, 2>& bs) noexcept
    {
        auto a = std::countr_one(bs[0]);
        auto b = std::countr_one(bs[1]);
        return std::bit_cast<u32>(a < 64 ? a : b + 64) & 0xFF;
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
        RadixSorter<u64, 8, 5>::radixSort(reinterpret_span<u64>(meetings));

        Booking* const heap_arr =
            reinterpret_cast<Booking*>(meetings.data());  // NOLINT
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
                std::ranges::pop_heap(
                    heap_arr,
                    heap_arr + heap_size,  // NOLINT
                    heap_cmp);
                --heap_size;
            }

            u64 start = meeting.begin;
            u8 room = bitsetFindFirstZero(bs);
            if (room == num_rooms)
            {
                auto booking = *heap_arr;
                std::ranges::pop_heap(
                    heap_arr,
                    heap_arr + heap_size,  // NOLINT
                    heap_cmp);
                --heap_size;
                start = booking.end_time;
                room = booking.room;
            }
            else
            {
                bitsetSet(bs, room);
            }

            ++rooms[room];
            heap_arr[heap_size++] =  // NOLINT
                {
                    .room = room,
                    .end_time = start + (meeting.end - meeting.begin),
                };
            std::ranges::push_heap(
                heap_arr,
                heap_arr + heap_size,  // NOLINT
                heap_cmp);
        }

        return static_cast<u32>(std::distance(
            rooms.begin(),
            std::max_element(rooms.begin(), rooms.begin() + num_rooms)));
    }
};

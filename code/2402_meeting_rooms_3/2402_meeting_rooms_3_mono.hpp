#include <algorithm>
#include <array>
#include <concepts>
#include <cstdint>
#include <numeric>
#include <span>
#include <utility>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

template <typename To>
inline static constexpr auto cast = []<typename From>(From&& v) INLINE_LAMBDA
{
    return static_cast<To>(std::forward<From>(v));
};

template <std::integral T>
[[nodiscard]] FORCE_INLINE constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & cast<T>(-c)) + (b & cast<T>(~cast<T>(-c)));
}

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

#define HOT_PATH __attribute__((hot))

#define NO_SANITIZERS \
    __attribute__((no_sanitize("undefined", "address", "coverage", "thread")))

template <typename To, typename From, std::size_t extent = std::dynamic_extent>
    requires(sizeof(To) == sizeof(From))
[[nodiscard]] FORCE_INLINE static auto reinterpret_range(
    std::span<From, extent> in) noexcept
{
    return std::span<To, extent>{
        reinterpret_cast<To*>(in.data()),  // NOLINT
        in.size()};
}

template <typename To, typename From, typename Allocator>
    requires(sizeof(To) == sizeof(From))
[[nodiscard]] FORCE_INLINE static std::span<To> reinterpret_range(
    std::vector<From, Allocator>& v) noexcept
{
    return reinterpret_range<To>(std::span{v});
}

enum class SortOrder : u8
{
    Ascending,
    Descending
};

template <
    std::integral T,
    SortOrder order,
    bool stable,
    u8 bits_per_pass,
    u32 num_passes = ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass),
    u32 capacity = 100'001>
    requires(((num_passes * bits_per_pass) <= sizeof(T) * 8) && (sizeof(T) > 1))
class RadixSorter
{
    using UT = std::make_unsigned_t<T>;

    static constexpr UT base = 1u << bits_per_pass;
    static constexpr UT mask = base - 1;
    static constexpr auto pass_idx_seq =
        std::make_integer_sequence<u8, num_passes>();
    static constexpr size_t num_bits = sizeof(T) * 8;

    inline static std::array<UT, base> count;
    inline static std::array<UT, capacity> temp;

    template <u8 pass_index>
    FORCE_INLINE static void do_pass(std::span<UT> arr) noexcept
        NO_SANITIZERS HOT_PATH
    {
        count.fill(0);
        constexpr UT shift = pass_index * bits_per_pass;
        constexpr UT msb = UT{1} << (num_bits - 1);
        constexpr bool sign_masking = std::is_signed_v<T>;
        constexpr bool is_first_pass = pass_index == 0;
        constexpr bool is_last_pass = (pass_index == (num_passes - 1));
        constexpr UT pre_sign_mask = sign_masking && is_first_pass ? msb : UT{};
        constexpr UT post_sign_mask = sign_masking && is_last_pass ? msb : UT{};

        // Count digit occurrences
        for (auto& v : arr)
        {
            v ^= pre_sign_mask;
            ++count[(v >> shift) & mask];
        }

        const u32 n = cast<u32>(arr.size());

        if constexpr (order == SortOrder::Ascending)
        {
            if constexpr (stable)
            {
                std::inclusive_scan(count.begin(), count.end(), count.begin());

                for (u32 i = n; i--;)
                {
                    UT digit = (arr[i] >> shift) & mask;
                    temp[--count[digit]] = arr[i] ^ post_sign_mask;
                }
            }
            else
            {
                std::exclusive_scan(
                    count.begin(),
                    count.end(),
                    count.begin(),
                    0);

                for (u32 j = 0; j != n; ++j)
                {
                    UT v = arr[j];
                    temp[count[(v >> shift) & mask]++] = v ^ post_sign_mask;
                }
            }
        }
        else  // Descending
        {
            // Compute descending start positions
            std::exclusive_scan(
                count.rbegin(),
                count.rend(),
                count.rbegin(),
                UT{0});

            for (u32 i = 0; i != n; ++i)
            {
                UT v = (arr[i] >> shift) & mask;
                temp[count[v]++] = arr[i] ^ post_sign_mask;
            }
        }

        std::ranges::copy_n(temp.begin(), n, arr.begin());
    }

    // Invokes do_pass for each pass_index.
    template <u8... pass_index>
    FORCE_INLINE static void do_passes(
        std::span<UT> arr,
        std::integer_sequence<u8, pass_index...>) noexcept
        NO_SANITIZERS HOT_PATH
    {
        (do_pass<pass_index>(arr), ...);
    }

public:
    FORCE_INLINE static void sort(std::span<T> arr) noexcept
        NO_SANITIZERS HOT_PATH
    {
        if (arr.size()) do_passes(reinterpret_range<UT>(arr), pass_idx_seq);
    }
};

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    SortOrder order = SortOrder::Ascending,
    u32 capacity = 100'001,
    std::integral T>
FORCE_INLINE void radix_sort(std::span<T> arr) noexcept NO_SANITIZERS
{
    constexpr u32 np =
        num_passes == 0xFFFFFFFF
            ? ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)
            : num_passes;
    RadixSorter<T, order, false, bits_per_pass, np, capacity>::sort(arr);
}

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    SortOrder order = SortOrder::Ascending,
    u32 capacity = 100'001,
    std::integral T>
FORCE_INLINE void stable_radix_sort(std::span<T> arr) noexcept NO_SANITIZERS
{
    constexpr u32 np =
        num_passes == 0xFFFFFFFF
            ? ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)
            : num_passes;
    RadixSorter<T, order, true, bits_per_pass, np, capacity>::sort(arr);
}

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

#ifndef __clang__
auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
#endif

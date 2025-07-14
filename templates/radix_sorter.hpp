#pragma once

#include <algorithm>
#include <array>
#include <span>

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;

#ifdef __GNUC__
#define ATTR inline __attribute__((always_inline))
#else
#define ATTR inline
#endif

enum class SortOrder : u8
{
    Ascending,
    Descending
};

template <
    std::unsigned_integral T,
    SortOrder order,
    u8 bits_per_pass,
    u32 num_passes = ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)>
    requires((num_passes * bits_per_pass) <= sizeof(T) * 8)
class RadixSorter
{
    static constexpr T base = 1u << bits_per_pass;
    static constexpr T mask = base - 1;
    static constexpr auto pass_idx_seq =
        std::make_integer_sequence<u8, num_passes>();

    inline static std::array<T, base> count;
    inline static std::array<T, 100'001> temp;

    template <u8 pass_index>
    ATTR static void do_pass(std::span<T> arr) noexcept
    {
        count.fill(0);
        constexpr T shift = pass_index * bits_per_pass;

        // Count digit occurrences
        for (auto v : arr) ++count[(v >> shift) & mask];

        const u32 n = static_cast<u32>(arr.size());

        if constexpr (order == SortOrder::Ascending)
        {
            // Prefix sums for positions
            for (u32 i = 1; i != base; ++i) count[i] += count[i - 1];

            // Stable placement
            for (u32 i = n; i--;)
            {
                u32 digit = (arr[i] >> shift) & mask;
                temp[--count[digit]] = arr[i];
            }
        }
        else
        {
            // Compute descending start positions directly
            T sum = 0;
            for (u32 i = base; i--;)
            {
                T c = count[i];
                count[i] = sum;
                sum += c;
            }

            // Stable placement
            for (u32 i = 0; i != n; ++i)
            {
                u32 digit = (arr[i] >> shift) & mask;
                temp[count[digit]++] = arr[i];
            }
        }

        std::ranges::copy_n(temp.begin(), n, arr.begin());
    }

    // Invokes pass for each do_pass index.
    template <u8... pass_index>
    ATTR static void do_passes(
        std::span<T> arr,
        std::integer_sequence<u8, pass_index...>) noexcept
    {
        (do_pass<pass_index>(arr), ...);
    }

public:
    ATTR static void sort(std::span<T> arr) noexcept
    {
        if (arr.size()) do_passes(arr, pass_idx_seq);
    }
};

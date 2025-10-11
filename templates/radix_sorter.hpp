#pragma once

#include <algorithm>
#include <array>
#include <span>

#include "force_inline.hpp"
#include "hot_path.hpp"
#include "integral_aliases.hpp"
#include "no_sanitizers.hpp"
#include "reinterpret_range.hpp"

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
    u32 num_passes = ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)>
    requires(((num_passes * bits_per_pass) <= sizeof(T) * 8) && (sizeof(T) > 1))
class RadixSorter
{
    using UT = std::make_unsigned_t<T>;

    static constexpr UT base = 1u << bits_per_pass;
    static constexpr UT mask = base - 1;
    static constexpr auto pass_idx_seq =
        std::make_integer_sequence<u8, num_passes>();
    static constexpr size_t num_bits = sizeof(T) * 8;
    static constexpr UT sign_mask = UT{1} << (num_bits - 1);

    inline static std::array<UT, base> count;
    inline static std::array<UT, 100'001> temp;

    template <u8 pass_index>
    FORCE_INLINE static void do_pass(std::span<UT> arr) noexcept
        NO_SANITIZERS HOT_PATH
    {
        count.fill(0);
        constexpr UT shift = pass_index * bits_per_pass;

        // Count digit occurrences
        for (auto& v : arr)
        {
            constexpr bool is_first_pass = pass_index == 0;
            if constexpr (std::is_signed_v<T> && is_first_pass) v ^= sign_mask;

            ++count[(v >> shift) & mask];
        }

        const u32 n = static_cast<u32>(arr.size());

        constexpr bool post_flip =
            std::is_signed_v<T> && (pass_index == (num_passes - 1));

        if constexpr (order == SortOrder::Ascending)
        {
            // Prefix sums for positions
            for (u32 i = 1; i != base; ++i) count[i] += count[i - 1];

            if constexpr (stable)
            {
                // Stable placement (reverse)
                for (u32 i = n; i--;)
                {
                    UT digit = (arr[i] >> shift) & mask;
                    temp[--count[digit]] =
                        post_flip ? arr[i] ^ sign_mask : arr[i];
                }
            }
            else
            {
                // Unstable placement (forward, single linear pass)
                UT start = 0;
                for (u32 i = 0; i != base; ++i)
                {
                    start += std::exchange(count[i], start);
                }

                for (u32 j = 0; j != n; ++j)
                {
                    UT v = arr[j];
                    temp[count[(v >> shift) & mask]++] =
                        post_flip ? v ^ sign_mask : v;
                }
            }
        }
        else  // Descending
        {
            // Compute descending start positions
            UT sum = 0;
            for (u32 i = base; i--;) sum += std::exchange(count[i], sum);

            if constexpr (stable)
            {
                for (u32 i = 0; i != n; ++i)
                {
                    UT digit = (arr[i] >> shift) & mask;
                    temp[count[digit]++] =
                        post_flip ? arr[i] ^ sign_mask : arr[i];
                }
            }
            else
            {
                // Unstable descending placement (forward)
                for (u32 i = 0; i != n; ++i)
                {
                    UT digit = (arr[i] >> shift) & mask;
                    temp[count[digit]++] =
                        post_flip ? arr[i] ^ sign_mask : arr[i];
                }
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
    std::integral T,
    SortOrder order,
    u8 bits_per_pass,
    u32 num_passes = ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)>
FORCE_INLINE void radix_sort(std::span<T> arr) noexcept NO_SANITIZERS
{
    RadixSorter<T, order, true, bits_per_pass, num_passes>::sort(arr);
}

template <
    std::integral T,
    SortOrder order,
    u8 bits_per_pass,
    u32 num_passes = ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)>
FORCE_INLINE void stable_radix_sort(std::span<T> arr) noexcept NO_SANITIZERS
{
    RadixSorter<T, order, false, bits_per_pass, num_passes>::sort(arr);
}

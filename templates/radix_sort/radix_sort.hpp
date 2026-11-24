#pragma once

#include <algorithm>
#include <cstring>
#include <span>

#include "cast.hpp"
#include "integral_aliases.hpp"
#include "reinterpret_range.hpp"
#include "uint_for_value.hpp"

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

    using Count = UintForValue<capacity>;
    inline static Count count[base];
    inline static UT temp[capacity];

    template <u8 pass_index>
    [[gnu::always_inline, gnu::hot]] static void
    do_pass(UT* data, UT* output, u32 n) noexcept
    {
        std::memset(count, 0, sizeof(count));
        constexpr UT shift = pass_index * bits_per_pass;
        constexpr UT msb = UT{1} << (num_bits - 1);
        constexpr bool sign_masking = std::is_signed_v<T>;
        constexpr bool is_first_pass = pass_index == 0;
        constexpr bool is_last_pass = (pass_index == (num_passes - 1));
        constexpr UT pre_sign_mask = sign_masking && is_first_pass ? msb : UT{};
        constexpr UT post_sign_mask = sign_masking && is_last_pass ? msb : UT{};

        // Count digit occurrences
        for (u32 i = 0; i != n; ++i)
        {
            auto& v = data[i];
            v ^= pre_sign_mask;
            ++count[(v >> shift) & mask];
        }

        if constexpr (order == SortOrder::Ascending)
        {
            if constexpr (stable)
            {
                for (u32 i = 1; i != base; ++i) count[i] += count[i - 1];

                for (u32 i = n; i--;)
                {
                    UT digit = (data[i] >> shift) & mask;
                    output[--count[digit]] = data[i] ^ post_sign_mask;
                }
            }
            else
            {
                Count sum = 0;
                for (u32 i = 0; i != base; ++i)
                {
                    Count frequency = count[i];
                    count[i] = sum;
                    sum += frequency;
                }

                for (u32 j = 0; j != n; ++j)
                {
                    UT v = data[j];
                    output[count[(v >> shift) & mask]++] = v ^ post_sign_mask;
                }
            }
        }
        else  // Descending
        {
            // Compute descending start positions
            Count sum = 0;
            for (u32 i = base; i--;)
            {
                Count frequency = count[i];
                count[i] = sum;
                sum += frequency;
            }

            for (u32 i = 0; i != n; ++i)
            {
                UT v = (data[i] >> shift) & mask;
                output[count[v]++] = data[i] ^ post_sign_mask;
            }
        }
    }

    // Invokes do_pass for each pass_index.
    template <u8... pass_index>
    [[gnu::always_inline, gnu::hot]] inline static void do_passes(
        UT* data,
        u32 n,
        std::integer_sequence<u8, pass_index...>) noexcept
    {
        (do_pass<pass_index>(
             pass_index % 2 ? temp : data,
             pass_index % 2 ? data : temp,
             n),
         ...);
        if constexpr (num_passes % 2) std::memcpy(data, temp, n * sizeof(UT));
    }

public:
    [[gnu::always_inline, gnu::hot]] inline static void sort(
        T* data,
        u32 n) noexcept
    {
        if (n) do_passes(reinterpret_cast<UT*>(data), n, pass_idx_seq);
    }

    [[gnu::always_inline, gnu::hot]] inline static void sort(
        std::span<T> arr) noexcept
    {
        sort(arr.data(), cast<u32>(arr.size()));
    }
};

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    SortOrder order = SortOrder::Ascending,
    u32 capacity = 100'001,
    std::integral T>
[[gnu::always_inline]] inline void radix_sort(T* data, u32 n) noexcept
{
    constexpr u32 np =
        num_passes == 0xFFFFFFFF
            ? ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)
            : num_passes;
    RadixSorter<T, order, false, bits_per_pass, np, capacity>::sort(data, n);
}

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    SortOrder order = SortOrder::Ascending,
    u32 capacity = 100'001,
    std::integral T>
[[gnu::always_inline]] inline void radix_sort(std::span<T> arr) noexcept
{
    radix_sort<bits_per_pass, num_passes, order, capacity>(
        arr.data(),
        cast<u32>(arr.size()));
}

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    SortOrder order = SortOrder::Ascending,
    u32 capacity = 100'001,
    std::integral T>
[[gnu::always_inline]] inline void stable_radix_sort(T* data, u32 n) noexcept
{
    constexpr u32 np =
        num_passes == 0xFFFFFFFF
            ? ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)
            : num_passes;
    RadixSorter<T, order, true, bits_per_pass, np, capacity>::sort(data, n);
}

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    SortOrder order = SortOrder::Ascending,
    u32 capacity = 100'001,
    std::integral T>
[[gnu::always_inline]] inline void stable_radix_sort(std::span<T> arr) noexcept
{
    stable_radix_sort<bits_per_pass, num_passes, order, capacity>(
        arr.data(),
        cast<u32>(arr.size()));
}

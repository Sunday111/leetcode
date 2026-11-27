#pragma once

#include <concepts>
#include <cstring>
#include <type_traits>
#include <utility>

#include "integral_aliases.hpp"
#include "radix_sort/radix_sort_storage.hpp"
#include "sort_order.hpp"
#include "uint_for_value.hpp"

// Stably sort by key_bits bits starting at skip_bits. Full-width signed keys
// use signed order.
template <
    u32 key_bits,
    u8 bits_per_pass = 10,
    SortOrder order = SortOrder::Ascending,
    u32 capacity = 100'001,
    u32 skip_bits = 0,
    std::integral T>
    requires(
        sizeof(T) > 1 && bits_per_pass > 0 &&
        u64{skip_bits} + key_bits <= sizeof(T) * 8)
[[gnu::always_inline]] inline void radix_sort(T* data, u32 n) noexcept
{
    using UT = std::make_unsigned_t<T>;
    using Count = UintForValue<capacity>;
    constexpr u32 num_bits = sizeof(T) * 8;
    constexpr u32 passes = (key_bits + bits_per_pass - 1) / bits_per_pass;

    if (n < 2) return;
    auto* words = reinterpret_cast<UT*>(data);
    auto* temp = RadixSortStorage::scratch<UT, capacity>;
    const auto do_pass = [=]<u8 pass_index> [[gnu::always_inline]] () noexcept
    {
        constexpr u32 processed = pass_index * bits_per_pass;
        constexpr u32 shift = skip_bits + processed;
        constexpr u32 remaining = key_bits - processed;
        constexpr u32 digit_bits =
            remaining < bits_per_pass ? remaining : bits_per_pass;
        static_assert(digit_bits < 32);
        constexpr u32 base = 1u << digit_bits;
        constexpr UT mask = base - 1;
        UT* input = pass_index % 2 ? temp : words;
        UT* output = pass_index % 2 ? words : temp;
        auto* count = reinterpret_cast<Count*>(
            RadixSortStorage::counts<(digit_bits > 16 ? digit_bits : 16)>);
        std::memset(count, 0, base * sizeof(Count));
        constexpr UT msb = UT{1} << (num_bits - 1);
        constexpr bool sign_masking =
            std::is_signed_v<T> && key_bits == num_bits;
        constexpr bool is_first_pass = pass_index == 0;
        constexpr bool is_last_pass = (pass_index == (passes - 1));
        constexpr UT pre_sign_mask = sign_masking && is_first_pass ? msb : UT{};
        constexpr UT post_sign_mask = sign_masking && is_last_pass ? msb : UT{};

        // Count digit occurrences
        for (u32 i = 0; i != n; ++i)
        {
            auto& v = input[i];
            v ^= pre_sign_mask;
            ++count[(v >> shift) & mask];
        }

        Count sum = 0;
        for (u32 i = 0; i != base; ++i)
        {
            const u32 digit = order == SortOrder::Ascending ? i : base - 1 - i;
            const Count frequency = count[digit];
            count[digit] = sum;
            sum += frequency;
        }

        for (u32 i = 0; i != n; ++i)
        {
            const UT value = input[i];
            const UT digit = (value >> shift) & mask;
            output[count[digit]++] = value ^ post_sign_mask;
        }
    };

    [&]<u8... indices> [[gnu::always_inline]] (
        std::integer_sequence<u8, indices...>) noexcept
    {
        (do_pass.template operator()<indices>(), ...);
    }(std::make_integer_sequence<u8, passes>{});
    if constexpr (passes % 2) std::memcpy(words, temp, n * sizeof(UT));
}

#pragma once

#include <cassert>
#include <concepts>
#include <cstring>
#include <type_traits>
#include <utility>

#include "integral_aliases.hpp"
#include "radix_sort/radix_sort_storage.hpp"
#include "sort_order.hpp"
#include "uint_for_value.hpp"

// Stably sort indices by key_bits bits starting at skip_bits of proj(index).
// Full-width signed keys use signed order.
template <
    u32 key_bits,
    u8 bits_per_pass = 10,
    SortOrder order = SortOrder::Ascending,
    u32 capacity = 100'001,
    u32 skip_bits = 0,
    std::unsigned_integral I,
    typename Proj>
    requires(
        bits_per_pass > 0 &&
        std::integral<
            std::remove_cvref_t<std::invoke_result_t<Proj&, const I&>>> &&
        u64{skip_bits} + key_bits <=
            sizeof(std::invoke_result_t<Proj&, const I&>) * 8)
[[gnu::always_inline]] inline void
    radix_sort_indices_by(I* indices, u32 n, Proj proj) noexcept
{
    using Key = std::remove_cvref_t<std::invoke_result_t<Proj&, const I&>>;
    using Count = UintForValue<capacity>;
    constexpr u32 passes = (key_bits + bits_per_pass - 1) / bits_per_pass;
    assert(n <= capacity);  // NOLINT
    if (n < 2) return;
    auto* temp = RadixSortStorage::scratch<I, capacity>;
    const auto do_pass = [&]<u8 pass_index> [[gnu::always_inline]] () noexcept
    {
        constexpr u32 processed = pass_index * bits_per_pass;
        constexpr u32 shift = skip_bits + processed;
        constexpr u32 remaining = key_bits - processed;
        constexpr u32 digit_bits =
            remaining < bits_per_pass ? remaining : bits_per_pass;
        static_assert(digit_bits < 32);
        constexpr u32 base = 1u << digit_bits;
        constexpr u32 mask = base - 1;
        const I* input = pass_index % 2 ? temp : indices;
        I* output = pass_index % 2 ? indices : temp;
        auto* count = reinterpret_cast<Count*>(
            RadixSortStorage::counts<(digit_bits > 16 ? digit_bits : 16)>);
        std::memset(count, 0, base * sizeof(Count));

        const auto digit_of = [&] [[gnu::always_inline]] (const I& index)
        {
            return static_cast<u32>(proj(index) >> shift) & mask;
        };
        for (u32 i = 0; i != n; ++i) ++count[digit_of(input[i])];

        // Visit negative buckets first for a full-width signed ascending sort.
        constexpr bool sign_digit = std::is_signed_v<Key> &&
                                    key_bits == sizeof(Key) * 8 &&
                                    pass_index + 1u == passes;
        constexpr u32 bucket_mask =
            (order == SortOrder::Descending ? mask : 0) ^
            (sign_digit ? base / 2 : 0);
        Count sum = 0;
        for (u32 i = 0; i != base; ++i)
        {
            const u32 digit = i ^ bucket_mask;
            const Count frequency = count[digit];
            count[digit] = sum;
            sum += frequency;
        }

        for (u32 i = 0; i != n; ++i)
        {
            const I index = input[i];
            output[count[digit_of(index)]++] = index;
        }
    };

    [&]<u8... pass_indices> [[gnu::always_inline]] (
        std::integer_sequence<u8, pass_indices...>) noexcept
    {
        (do_pass.template operator()<pass_indices>(), ...);
    }(std::make_integer_sequence<u8, passes>{});
    if constexpr (passes % 2) std::memcpy(indices, temp, n * sizeof(I));
}

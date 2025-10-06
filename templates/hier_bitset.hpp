#pragma once

#include <array>
#include <cstdint>

#include "ceil_div.hpp"
#include "force_inline.hpp"
#include "integral_aliases.hpp"

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

template <u32 BITS>
struct HierBitset
{
    static_assert((1 << 18) == 64 * 64 * 64);
    static_assert(BITS <= (1 << 18));
    static constexpr u32 WORD_BITS = 64u;
    static constexpr u32 LEAF_WORDS = ceil_div(BITS, WORD_BITS);
    static constexpr u32 L1_WORDS = ceil_div(LEAF_WORDS, WORD_BITS);
    static constexpr u32 L2_WORDS = ceil_div(L1_WORDS, WORD_BITS);

    // Intentionally not initialized. Use init to clean the exact area you need
    std::array<u64, LEAF_WORDS> leaf;
    std::array<u64, L1_WORDS> l1;
    std::array<u64, L2_WORDS> l2;

    void init(u32 num_bits)
    {
        l2.fill(0);
        std::fill_n(std::begin(l1), ceil_div<u32>(num_bits, 64 * 64), 0);
        std::fill_n(std::begin(leaf), ceil_div<u32>(num_bits, 64), 0);
    }

    FORCE_INLINE constexpr void set(u32 pos) noexcept
    {
        const u32 leaf_idx = pos >> 6u;
        const u32 bit_in_leaf = pos & 63u;
        const u64 bit_mask = u64{1} << bit_in_leaf;

        leaf[leaf_idx] |= bit_mask;

        const u32 l1_idx = leaf_idx >> 6u;
        const u32 bit_in_l1 = leaf_idx & 63u;
        l1[l1_idx] |= u64{1} << bit_in_l1;

        const u32 l2_idx = l1_idx >> 6u;
        const u32 bit_in_l2 = l1_idx & 63u;
        l2[l2_idx] |= u64{1} << bit_in_l2;
    }

    [[nodiscard]] FORCE_INLINE constexpr bool test(u32 pos) const noexcept
    {
        const u32 leaf_idx = pos >> 6u;
        const u32 bit_in_leaf = pos & 63u;
        return (leaf[leaf_idx] >> bit_in_leaf) & 1u;
    }

    [[nodiscard]] FORCE_INLINE constexpr u16 min() const noexcept
    {
        constexpr u16 NONE = 0xFFFFu;

        const u64 top = l2[0];
        const u64 top_nonzero = static_cast<u64>((top != 0u) ? 1u : 0u);
        const u64 top_for_ctz = top | 1u;
        const u32 idx2_ctz = static_cast<u32>(__builtin_ctzll(top_for_ctz));

        const u32 l1_index = idx2_ctz;
        const u64 l1_word = l1[l1_index];
        const u64 l1_nonzero = static_cast<u64>((l1_word != 0u) ? 1u : 0u);
        const u64 l1_for_ctz = l1_word | 1u;
        const u32 idx1_ctz = static_cast<u32>(__builtin_ctzll(l1_for_ctz));

        const u32 leaf_word_index = (l1_index << 6u) + idx1_ctz;
        const u64 leaf_word = leaf[leaf_word_index];
        const u64 leaf_nonzero = static_cast<u64>((leaf_word != 0u) ? 1u : 0u);
        const u64 leaf_for_ctz = leaf_word | 1u;
        const u32 idx0_ctz = static_cast<u32>(__builtin_ctzll(leaf_for_ctz));

        const u32 final_idx = (idx2_ctz * (WORD_BITS * WORD_BITS)) +
                              (idx1_ctz * WORD_BITS) + idx0_ctz;
        const u32 mask_nonzero =
            static_cast<u32>(top_nonzero & l1_nonzero & leaf_nonzero);

        const u32 res32 = mask_nonzero ? final_idx : static_cast<u32>(NONE);
        return static_cast<u16>(res32);
    }

    FORCE_INLINE constexpr void clear(u32 pos) noexcept
    {
        const u32 bit_pos = static_cast<u32>(pos);
        const u32 leaf_idx = bit_pos >> 6u;
        const u32 bit_in_leaf = bit_pos & 63u;
        const u64 bit_mask = static_cast<u64>(1) << bit_in_leaf;

        const u64 prev_leaf = leaf[leaf_idx];
        const u64 new_leaf = prev_leaf & ~bit_mask;
        leaf[leaf_idx] = new_leaf;
        const u64 leaf_is_zero = static_cast<u64>((new_leaf == 0u) ? 1u : 0u);

        const u32 l1_idx = leaf_idx >> 6u;
        const u32 bit_in_l1 = leaf_idx & 63u;
        const u64 l1_clear_mask =
            leaf_is_zero * (static_cast<u64>(1) << bit_in_l1);
        const u64 prev_l1 = l1[l1_idx];
        const u64 new_l1 = prev_l1 & ~l1_clear_mask;
        l1[l1_idx] = new_l1;
        const u64 l1_is_zero = static_cast<u64>((new_l1 == 0u) ? 1u : 0u);

        const u32 l2_idx = l1_idx >> 6u;
        const u32 bit_in_l2 = l1_idx & 63u;
        const u64 l2_clear_mask =
            l1_is_zero * (static_cast<u64>(1) << bit_in_l2);
        l2[l2_idx] &= ~l2_clear_mask;
    }
};

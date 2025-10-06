#pragma once

#include <array>

#include "ceil_div.hpp"
#include "force_inline.hpp"
#include "integral_aliases.hpp"

template <u32 kCapacity>
class HierBitset
{
    using Word = u64;
    static constexpr u32 kWordBits = sizeof(Word) * 8;
    static constexpr u32 kShift = std::countr_zero(kWordBits);
    static constexpr u32 kMask = kWordBits - 1;
    static_assert(kCapacity <= kWordBits * kWordBits * kWordBits);
    static constexpr u32 kLeafWords = ceil_div(kCapacity, kWordBits);
    static constexpr u32 kL1Words = ceil_div(kLeafWords, kWordBits);
    static constexpr u32 kL2Words = ceil_div(kL1Words, kWordBits);

    // Intentionally not initialized. Use init to clean the exact area you need
    std::array<Word, kLeafWords> leaf;
    std::array<Word, kL1Words> l1;
    std::array<Word, kL2Words> l2;

public:
    FORCE_INLINE constexpr void clear(u32 num_bits) noexcept
    {
        l2.fill(0);
        std::fill_n(
            std::begin(l1),
            ceil_div<u32>(num_bits, kWordBits * kWordBits),
            0);
        std::fill_n(std::begin(leaf), ceil_div<u32>(num_bits, kWordBits), 0);
    }

    FORCE_INLINE constexpr void add(u32 i) noexcept
    {
        const u32 leaf_idx = i >> kShift;
        const u32 l1_idx = leaf_idx >> kShift;
        leaf[leaf_idx] |= (Word{1} << (i & kMask));
        l1[l1_idx] |= Word{1} << (leaf_idx & kMask);
        l2[l1_idx >> kShift] |= Word{1} << (l1_idx & kMask);
    }

    FORCE_INLINE constexpr void remove(u32 i) noexcept
    {
        const u32 leaf_idx = i >> kShift;
        const Word new_leaf = leaf[leaf_idx] & ~(Word{1} << (i & kMask));
        const u32 l1_idx = leaf_idx >> kShift;
        const Word new_l1 =
            l1[l1_idx] & ~(Word{new_leaf == 0u} << (leaf_idx & kMask));
        leaf[leaf_idx] = new_leaf;
        l1[l1_idx] = new_l1;
        l2[l1_idx >> kShift] &= ~(Word{new_l1 == 0u} << (l1_idx & kMask));
    }

    template <bool v>
    FORCE_INLINE constexpr void set(u32 i) noexcept
    {
        if constexpr (v)
        {
            add(i);
        }
        else
        {
            remove(i);
        }
    }

    [[nodiscard]] FORCE_INLINE constexpr bool empty() const noexcept
    {
        return l2[0] == 0;
    }

    [[nodiscard]] FORCE_INLINE constexpr bool test(u32 pos) const noexcept
    {
        return (leaf[pos >> kShift] >> (pos & kMask)) & 1u;
    }

    [[nodiscard]] FORCE_INLINE constexpr u32 min() const noexcept
    {
        const u32 i2 = static_cast<u32>(std::countr_zero(l2[0]));
        const u32 i1 = static_cast<u32>(std::countr_zero(l1[i2]));
        const u32 i0 =
            static_cast<u32>(std::countr_zero(leaf[(i2 << kShift) | i1]));
        return (i2 << (kShift << 1)) | (i1 << kShift) | i0;
    }

    [[nodiscard]] FORCE_INLINE constexpr u32 max() const noexcept
    {
        // Start from the top-level l2 word
        const u32 i2 =
            kWordBits - 1 - static_cast<u32>(std::countl_zero(l2[0]));
        const u32 i1 =
            kWordBits - 1 - static_cast<u32>(std::countl_zero(l1[i2]));
        const u32 i0 =
            kWordBits - 1 -
            static_cast<u32>(std::countl_zero(leaf[(i2 << kShift) | i1]));
        return (i2 << (kShift << 1)) | (i1 << kShift) | i0;
    }
};

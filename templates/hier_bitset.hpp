#pragma once

#include <array>

#include "ceil_div.hpp"
#include "force_inline.hpp"
#include "integral_aliases.hpp"

template <u32 kCapacity, typename Word = u64>
class HierBitset
{
    static constexpr u32 kWordBits = sizeof(Word) * 8;
    static constexpr u32 kShift = std::countr_zero(kWordBits);
    static constexpr u32 kMask = kWordBits - 1;
    static_assert(kCapacity <= kWordBits * kWordBits * kWordBits);
    static constexpr u32 kL0 = ceil_div(kCapacity, kWordBits);
    static constexpr u32 kL1 = ceil_div(kL0, kWordBits);

    // Intentionally not initialized. Use init to clean the exact area you need
    std::array<Word, kL0> l0;
    std::array<Word, kL1> l1;
    Word l2;

public:
    FORCE_INLINE constexpr void clear(u32 n) noexcept
    {
        l2 = 0;
        std::fill_n(std::begin(l1), ceil_div<u32>(n, kWordBits * kWordBits), 0);
        std::fill_n(std::begin(l0), ceil_div<u32>(n, kWordBits), 0);
    }

    FORCE_INLINE constexpr void add(u32 i) noexcept
    {
        const u32 i0 = i >> kShift;
        const u32 i1 = i0 >> kShift;
        l0[i0] |= (Word{1} << (i & kMask));
        l1[i1] |= Word{1} << (i0 & kMask);
        l2 |= Word{1} << (i1 & kMask);
    }

    FORCE_INLINE constexpr void remove(u32 i) noexcept
    {
        const u32 i0 = i >> kShift;
        const Word w0 = l0[i0] & ~(Word{1} << (i & kMask));
        const u32 i1 = i0 >> kShift;
        const Word w1 = l1[i1] & ~(Word{w0 == 0u} << (i0 & kMask));
        l0[i0] = w0;
        l1[i1] = w1;
        l2 &= ~(Word{w1 == 0u} << (i1 & kMask));
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

    [[nodiscard]] FORCE_INLINE static constexpr u32 capacity() noexcept
    {
        return kCapacity;
    }

    [[nodiscard]] FORCE_INLINE constexpr bool empty() const noexcept
    {
        return l2 == 0;
    }

    [[nodiscard]] FORCE_INLINE constexpr bool test(u32 pos) const noexcept
    {
        return (l0[pos >> kShift] >> (pos & kMask)) & 1u;
    }

    [[nodiscard]] FORCE_INLINE constexpr u32 min() const noexcept
    {
        const u32 i2 = static_cast<u32>(std::countr_zero(l2));
        const u32 i1 = static_cast<u32>(std::countr_zero(l1[i2]));
        const u32 i0 =
            static_cast<u32>(std::countr_zero(l0[(i2 << kShift) | i1]));
        return (i2 << (kShift << 1)) | (i1 << kShift) | i0;
    }

    [[nodiscard]] FORCE_INLINE constexpr u32 max() const noexcept
    {
        const u32 i2 = kWordBits - 1 - static_cast<u32>(std::countl_zero(l2));
        const u32 i1 =
            kWordBits - 1 - static_cast<u32>(std::countl_zero(l1[i2]));
        const u32 i0 =
            kWordBits - 1 -
            static_cast<u32>(std::countl_zero(l0[(i2 << kShift) | i1]));
        return (i2 << (kShift << 1)) | (i1 << kShift) | i0;
    }
};

#pragma once

#include <array>

#include "force_inline.hpp"
#include "integral_aliases.hpp"

class Bitset128
{
public:
    std::array<u64, 2> words{};

    [[nodiscard]] FORCE_INLINE constexpr u8 countr_zero() const noexcept
    {
        const u64 lo = words[0];
        const u64 hi = words[1];
        const u8 lo_zero = (lo == 0);
        return (std::countr_zero(lo) + lo_zero * std::countr_zero(hi)) & 0xFF;
    }

    FORCE_INLINE constexpr void set_bit(std::uint32_t index) noexcept
    {
        words[index >> 6] |= (u64{1} << (index & 63));
    }

    constexpr void remove_bit(std::uint32_t index) noexcept
    {
        const u64 bit = u64{1} << (index & 63);
        const u64 lane = index >> 6;
        const u64 lower_mask = ~u64{0} * (lane == 0);
        const u64 upper_mask = ~u64{0} * (lane == 1);
        words[0] &= ~(bit & lower_mask);
        words[1] &= ~(bit & upper_mask);
    }

    [[nodiscard]] FORCE_INLINE constexpr bool has_bit(
        std::uint32_t index) const noexcept
    {
        const u64 bit = u64{1} << (index & 63);
        const u64 lane = index >> 6;

        const u64 lower_mask = ~u64{0} * (lane == 0);
        const u64 upper_mask = ~u64{0} * (lane == 1);

        return ((words[0] & lower_mask) | (words[1] & upper_mask)) & bit;
    }

    [[nodiscard]] FORCE_INLINE constexpr bool is_empty() const noexcept
    {
        return (words[0] | words[1]) == 0;
    }
};

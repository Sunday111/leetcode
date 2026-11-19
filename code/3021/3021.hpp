#pragma once

#include <cstdint>

class Solution
{
public:
    using u32 = uint32_t;
    using u64 = uint64_t;
    [[nodiscard]] static constexpr u64 flowerGame(
        const u32 n,
        const u32 m) noexcept
    {
        const u64 n_even = n / 2, n_odd = n - n_even;
        const u64 m_even = m / 2, m_odd = m - m_even;
        return n_odd * m_even + n_even * m_odd;
    }
};

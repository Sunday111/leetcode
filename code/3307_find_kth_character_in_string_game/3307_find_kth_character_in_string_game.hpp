#pragma once

#include <bit>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr char kthCharacter(
        uint64_t k,
        const std::vector<int>& o) noexcept
    {
        uint8_t r{};
        while (k != 1)
        {
            r += o[(63 - std::countl_zero(k - 1)) & 0xFF] & 1;
            k -= std::bit_ceil(k) / 2;
        }

        return static_cast<char>('a' + (r > 26 ? r - 26 : r));
    }
};

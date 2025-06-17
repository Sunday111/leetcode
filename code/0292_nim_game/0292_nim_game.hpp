#pragma once

class Solution
{
public:
    [[nodiscard]] static constexpr bool canWinNim(int n) noexcept
    {
        return n % 4;
    }
};

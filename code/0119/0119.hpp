#pragma once

#include <array>
#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    using i128 = __int128;

    inline static constexpr auto factorials = []()
    {
        std::array<__int128, 34> r;  // NOLINT
        r[0] = 1;
        for (u8 i = 1; i != r.size(); ++i) r[i] = r[i - 1] * i128{i};
        return r;
    }();

    using u32 = uint32_t;
    [[nodiscard]] static constexpr std::vector<int> getRow(u8 n) noexcept
    {
        if (n == 0) return {1};

        std::vector<int> r;
        r.reserve(n + 1);
        for (u8 i = 0; i <= n; ++i)
        {
            r.push_back(
                static_cast<int>(
                    factorials[n] / (factorials[i] * factorials[n - i])));
        }
        return r;
    }
};

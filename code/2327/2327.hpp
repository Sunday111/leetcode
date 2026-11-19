#pragma once

#include <array>
#include <cstdint>

class Solution
{
public:
    using u16 = uint16_t;
    using u32 = uint32_t;
    using i32 = int32_t;

    [[nodiscard]] static constexpr int
    peopleAwareOfSecret(int n, u16 delay, u16 forget) noexcept
    {
        struct Day
        {
            int d_know = 0;
            int d_share = 0;
        };

        constexpr int64_t kMOD = 1'000'000'007;

        std::array<Day, 2002> days{};
        days[1].d_know = 1;
        days[1 + delay].d_share = 1;
        days[1 + forget] = {.d_know = -1, .d_share = -1};

        int64_t know = 0;
        int share = 0;
        for (u16 i = 1; i <= n; ++i)
        {
            share = static_cast<i32>((share + kMOD + days[i].d_share) % kMOD);
            know += days[i].d_know + share;
            days[i + delay].d_share += share;
            days[i + forget].d_know += static_cast<i32>(kMOD - share);
            days[i + forget].d_share += static_cast<i32>(kMOD - share);
        }

        return static_cast<i32>(know % kMOD);
    }
};

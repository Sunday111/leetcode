#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <span>

template <typename value_type, auto generator>
constexpr auto gen_options()
{
    constexpr size_t num_options = [&]()
    {
        size_t n = 0;
        generator([&](auto&&...) { ++n; });
        return n;
    }();

    std::array<value_type, num_options> options;  // NOLINT
    size_t i = 0;
    generator([&](value_type v) { options[i++] = v; });

    return options;
}

inline constexpr auto gen_perfect_squares = [](auto&& cb)
{
    std::bitset<10'001> bs;
    bs[1] = 1;

    for (uint32_t i = 2; i != 101; ++i)
    {
        uint32_t k = i * i;
        while (k <= 10'000 && !bs[k])
        {
            bs[k] = true;
            k *= k;
        }
    }

    for (uint16_t i = 1; i != bs.size(); ++i)
    {
        if (bs[i]) cb(i);
    }
};

inline constexpr auto kPerfectSquares =
    gen_options<uint16_t, gen_perfect_squares>();

class Solution
{
public:
    int32_t numSquares(int32_t in_n)
    {
        const auto n = static_cast<uint16_t>(in_n);
        std::array<uint32_t, 10'001> dp{};
        dp[0] = 1;

        auto options = std::span{kPerfectSquares}.subspan(
            0,
            static_cast<size_t>(std::distance(
                kPerfectSquares.begin(),
                std::ranges::upper_bound(kPerfectSquares, n))));

        for (auto v : options)
        {
            for (uint16_t i = v; i <= n; ++i)
            {
                if (auto kp = dp[i - v] + 1; kp != 1)
                {
                    auto& k = dp[i];
                    if (k == 0 || kp < k) k = kp;
                }
            }
        }

        return static_cast<int32_t>(dp[n]) - 1;
    }
};

#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
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

template <uint16_t power>
inline constexpr auto gen_numbers_in_power = [](auto&& cb)
{
    std::bitset<301> bs;
    bs[1] = 1;

    for (uint16_t i = 2; i <= bs.size(); ++i)
    {
        uint16_t k = i;
        uint8_t j = 1;
        while (true)
        {
            if (j++ == power)
            {
                bs[k] = true;
                break;
            }

            k *= i;
            if (k >= bs.size()) break;
        }
    }

    for (uint16_t i = 1; i != bs.size(); ++i)
    {
        if (bs[i]) cb(i);
    }
};

inline static constexpr uint32_t kMOD = 1'000'000'007;

constexpr uint32_t modMul(uint64_t a, uint64_t b)
{
    return (a * b) % kMOD;
}

constexpr uint32_t modAdd(uint64_t a, uint64_t b)
{
    return (a + b) % kMOD;
}

inline constexpr auto kNumbersInPower1 =
    gen_options<uint16_t, gen_numbers_in_power<1>>();
inline constexpr auto kNumbersInPower2 =
    gen_options<uint16_t, gen_numbers_in_power<2>>();
inline constexpr auto kNumbersInPower3 =
    gen_options<uint16_t, gen_numbers_in_power<3>>();
inline constexpr auto kNumbersInPower4 =
    gen_options<uint16_t, gen_numbers_in_power<4>>();
inline constexpr auto kNumbersInPower5 =
    gen_options<uint16_t, gen_numbers_in_power<5>>();

template <uint8_t x>
inline constexpr auto solveOne(uint16_t n) -> uint32_t
{
    std::array<uint32_t, 301> dp{};
    dp[0] = 1;
    dp[1] = 0;
    auto s = [&](std::span<const uint16_t> options)
    {
        // Only options <= n
        options = options.subspan(
            0,
            static_cast<size_t>(std::distance(
                options.begin(),
                std::ranges::upper_bound(options, n))));

        for (auto v : options)
        {
            // for (uint16_t j = v; j < n; --j)
            for (uint16_t j = n; j >= v; --j)
            {
                dp[j] = modAdd(dp[j], dp[j - v]);
            }
        }
    };

    switch (x)
    {
    case 1:
        s(kNumbersInPower1);
        break;
    case 2:
        s(kNumbersInPower2);
        break;
    case 3:
        s(kNumbersInPower3);
        break;
    case 4:
        s(kNumbersInPower4);
        break;
    case 5:
        s(kNumbersInPower5);
        break;
    }

    return dp[n];
}

inline constexpr auto kSolPow4_0 = []()
{
    std::array<uint32_t, 200> r;  // NOLINT
    r[0] = 0;
    for (uint16_t i = 1; i != r.size(); ++i)
    {
        r[i] = solveOne<4>(i);
    }

    return r;
}();

inline constexpr auto kSolPow4 = []()
{
    std::array<uint32_t, 301> r;  // NOLINT
    std::ranges::copy(kSolPow4_0, r.begin());
    for (uint16_t i = kSolPow4_0.size(); i != r.size(); ++i)
    {
        r[i] = solveOne<4>(i);
    }

    return r;
}();

inline constexpr auto kSolPow5_0 = []()
{
    std::array<uint32_t, 150> r;  // NOLINT
    r[0] = 0;
    for (uint16_t i = 1; i != r.size(); ++i)
    {
        r[i] = solveOne<5>(i);
    }

    return r;
}();

inline constexpr auto kSolPow5 = []()
{
    std::array<uint32_t, 301> r;  // NOLINT
    std::ranges::copy(kSolPow5_0, r.begin());
    for (uint16_t i = kSolPow5_0.size(); i != r.size(); ++i)
    {
        r[i] = solveOne<5>(i);
    }

    return r;
}();

class Solution
{
public:
    int32_t numberOfWays(int32_t in_n, int32_t in_x)
    {
        return std::bit_cast<int32_t>(
            [&]
            {
                const auto n = static_cast<uint16_t>(in_n);
                const auto x = static_cast<uint8_t>(in_x);

                std::array<uint32_t, 301> dp{};
                dp[0] = 1;
                dp[1] = 0;
                auto s = [&](std::span<const uint16_t> options)
                {
                    // Only options <= n
                    options = options.subspan(
                        0,
                        static_cast<size_t>(std::distance(
                            options.begin(),
                            std::ranges::upper_bound(options, n))));

                    for (auto v : options)
                    {
                        // for (uint16_t j = v; j < n; --j)
                        for (uint16_t j = n; j >= v; --j)
                        {
                            dp[j] = modAdd(dp[j], dp[j - v]);
                        }
                    }
                };

                switch (x)
                {
                case 1:
                    s(kNumbersInPower1);
                    break;
                case 2:
                    s(kNumbersInPower2);
                    break;
                case 3:
                    s(kNumbersInPower3);
                    break;
                case 4:
                    return kSolPow4[n];
                    break;
                case 5:
                    return kSolPow5[n];
                    break;
                }
                return dp[n];
            }());
    }
};

template <typename T, size_t... sizes>
static inline constexpr auto joinArrays(const std::array<T, sizes>&... arrays)
{
    constexpr size_t total_size = (0 + ... + sizes);
    std::array<T, total_size> r;  // NOLINT
    uint32_t num_added = 0;

    (
        [&](const auto& arr)
        {
            std::ranges::copy(arr, std::next(r.begin(), num_added));
            num_added += arr.size();
        }(arrays),
        ...);
    return r;
}

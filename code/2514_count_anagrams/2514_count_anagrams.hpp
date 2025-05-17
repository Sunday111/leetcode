#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <string_view>

inline static constexpr int32_t kMOD = 1'000'000'007;

static constexpr int32_t modInverse(int32_t a)
{
    int32_t x0 = 1, x1 = 0, mod = kMOD;
    while (a != 0)
    {
        int32_t q = mod / a;
        int32_t r = mod % a;
        int32_t x2 = x1 - q * x0;
        mod = a;
        a = r;
        x1 = x0;
        x0 = x2;
    }
    return (x1 + kMOD) % kMOD;
}

static constexpr int32_t modMul(int64_t a, int64_t b)
{
    return static_cast<int32_t>((a * b) % kMOD);
}

static constexpr int32_t modDiv(int64_t a, int32_t b)
{
    return modMul(a, modInverse(b));
}

// Generic Solution
class Solution
{
public:
    static constexpr int countAnagrams(std::string_view s)
    {
        std::array<uint32_t, 26> counters{};
        int32_t result = 1;
        uint32_t world_letter_index = 0;

        for (char c : s)
        {
            if (c == ' ')
            {
                counters.fill(0);
                world_letter_index = 0;
                continue;
            }

            result = modMul(result, ++world_letter_index);

            uint32_t& count = counters[std::bit_cast<unsigned>(c - 'a')];
            if (++count > 1)
            {
                result = modDiv(result, std::bit_cast<int32_t>(count));
            }
        }

        return static_cast<int>(result);
    }
};

class CachingFactorialsSolution
{
public:
    static inline constexpr auto kPrecomputedFactorials1 = []
    {
        std::array<int32_t, 50001> fact;  // NOLINT
        fact[0] = 1;
        for (uint32_t i = 1; i != fact.size(); i++)
        {
            fact[i] = modMul(fact[i - 1], i);
        }
        return fact;
    }();

    static inline constexpr auto kPrecomputedFactorials2 = []
    {
        std::array<int32_t, 50001> fact;  // NOLINT
        fact[0] = modMul(
            kPrecomputedFactorials1.back(),
            kPrecomputedFactorials1.size());
        for (uint32_t i = 1; i != fact.size(); i++)
        {
            fact[i] = modMul(
                fact[i - 1],
                i + static_cast<uint32_t>(kPrecomputedFactorials1.size()));
        }
        return fact;
    }();

    static constexpr auto kFactorials = []
    {
        std::array< // NOLINT
            uint32_t,
            kPrecomputedFactorials1.size() + kPrecomputedFactorials2.size()>
            r;

        std::ranges::copy(kPrecomputedFactorials1, r.begin());
        std::ranges::copy(
            kPrecomputedFactorials2,
            r.begin() + kPrecomputedFactorials1.size());
        return r;
    }();

    static constexpr int countAnagrams(std::string_view s)
    {
        std::array<uint32_t, 26> counters{};
        int32_t result = 1;

        auto finish_word = [&]
        {
            uint32_t word_length = 0;
            int32_t denominator = 1;
            for (auto& cnt : counters)
            {
                if (cnt != 0)
                {
                    word_length += cnt;
                    denominator = modMul(denominator, kFactorials[cnt]);
                    cnt = 0;
                }
            }
            result =
                modMul(result, modDiv(kFactorials[word_length], denominator));
        };

        for (char c : s)
        {
            if (c == ' ')
            {
                finish_word();
            }
            else
            {
                ++counters[std::bit_cast<unsigned>(c - 'a')];
            }
        }

        finish_word();

        return static_cast<int>(result);
    }
};

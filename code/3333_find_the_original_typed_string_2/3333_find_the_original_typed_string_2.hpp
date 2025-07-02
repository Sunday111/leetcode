#pragma once

#include <array>
#include <numeric>
#include <span>
#include <string>

#ifdef __GNUC__
#define ATTR inline __attribute__((always_inline))
#else
#define ATTR inline
#endif

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;
static constexpr int kMOD = 1'000'000'007;

struct ModInt
{
    ATTR constexpr ModInt& operator+=(const ModInt& rhs) noexcept
    {
        value += rhs.value;
        const u32 gt = value > kMOD;
        value -= (-gt & kMOD);

        return *this;
    }

    [[nodiscard]] ATTR constexpr ModInt operator+(
        const ModInt& rhs) const noexcept
    {
        auto copy = *this;
        copy += rhs;
        return copy;
    }

    ATTR constexpr ModInt& operator-=(const ModInt& rhs) noexcept
    {
        value += kMOD;
        value -= rhs.value;
        value -= (-u32{value > kMOD} & kMOD);
        return *this;
    }

    [[nodiscard]] ATTR constexpr ModInt operator-(
        const ModInt& rhs) const noexcept
    {
        auto copy = *this;
        copy -= rhs;
        return copy;
    }

    ATTR constexpr ModInt& operator*=(const ModInt& rhs) noexcept
    {
        u64 v = rhs.value;
        v *= value;
        if (v >= kMOD) v %= kMOD;
        value = static_cast<u32>(v);
        return *this;
    }

    [[nodiscard]] ATTR constexpr ModInt operator*(
        const ModInt& rhs) const noexcept
    {
        auto copy = *this;
        copy *= rhs;
        return copy;
    }

    u32 value = 0;
};

class Solution
{
public:
    [[nodiscard]] static constexpr u32 possibleStringCount(
        const std::string& word,
        u32 k) noexcept
    {
        const u32 n = static_cast<u32>(word.size());
        if (n < k) return 0;
        if (n == k) return 1;

        static std::array<u32, 500'001> seg_arr;
        u32 p = 0, m = 0;
        ModInt total{1};
        for (u32 i = 1; i <= n; i++)
        {
            if (word[i] != word[i - 1])
            {
                u32 len = i - p;
                seg_arr[m++] = len;
                p = i;
                total *= ModInt{len};
            }
        }

        if (total.value == 1) return 1;
        if (k <= m) return total.value;

        const auto seg = std::span{seg_arr}.first(m);
        const u32 max_t = k - m;

        std::array<std::array<ModInt, 2000>, 2> dp = {};
        std::array<ModInt, 2001> prefix{};
        dp[0][0].value = 1;

        for (u32 j = 0; j != m; ++j)
        {
            const u32 s = seg[j] - 1;
            auto& dpa = dp[j & 1];
            auto& dpb = dp[(j + 1) & 1];

            u32 i = 0;
            for (; i <= s && i != max_t; ++i)
            {
                prefix[i + 1] = prefix[i] + dpa[i];
                dpb[i] = prefix[i + 1] - prefix[0];
            }
            for (; i != max_t; ++i)
            {
                prefix[i + 1] = prefix[i] + dpa[i];
                dpb[i] = prefix[i + 1] - prefix[i - s];
            }
        }

        auto& final_dp = dp[m & 1];
        const auto num_invalid =
            std::accumulate(final_dp.begin(), final_dp.end(), ModInt{});
        return (total - num_invalid).value;
    }
};

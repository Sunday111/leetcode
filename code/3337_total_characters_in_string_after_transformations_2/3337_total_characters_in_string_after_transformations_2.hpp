#pragma once

#include <array>
#include <bit>
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <vector>

#define ATTRS __attribute__((no_sanitize("all"))) __attribute__((always_inline))

class Solution
{
public:
    static constexpr uint32_t kMOD = 1'000'000'007;

    [[nodiscard]]
    ATTRS constexpr uint32_t static modAdd(uint32_t a, uint32_t b) noexcept
    {
        uint64_t r = a + b;
        if (r >= kMOD) r -= kMOD;
        return static_cast<uint32_t>(r);
    }

    [[nodiscard]]
    ATTRS constexpr uint32_t static modMul(uint64_t a, uint64_t b) noexcept
    {
        auto r = a * b;
        if (r < kMOD) return static_cast<uint32_t>(r);
        return r % kMOD;
    }

    template <size_t k>
    using Vector = std::array<uint32_t, k>;

    template <size_t k>
    using Matrix = std::array<Vector<k>, k>;

    template <size_t k>
    [[nodiscard]]
    ATTRS inline static constexpr Matrix<k> multiply(
        const Matrix<k>& a,
        const Matrix<k>& b)
    {
        Matrix<k> c{};
        for (size_t i = 0; i != k; ++i)
        {
            for (size_t l = 0; l < k; ++l)
            {
                if (a[i][l] == 0) continue;
                for (size_t j = 0; j != k; ++j)
                {
                    c[i][j] = modAdd(c[i][j], modMul(a[i][l], b[l][j]));
                }
            }
        }

        return c;
    }

    template <size_t k>
    [[nodiscard]]
    ATTRS inline static constexpr Matrix<k> matrix_power(
        Matrix<k> base,
        uint32_t exp)
    {
        [[unlikely]] if (exp == 0)
        {
            Matrix<k> r{};
            for (size_t i = 0; i < k; ++i) r[i][i] = 1;
            return r;
        }

        auto r = base;
        std::bitset<32> b(exp);
        for (int i = 30 - std::countl_zero(exp); i >= 0; i--)
        {
            r = multiply(r, r);
            if (b[std::bit_cast<unsigned>(i)])
            {
                r = multiply(r, base);
            }
        }

        return r;
    }

    template <size_t k>
    [[nodiscard]]
    ATTRS inline static constexpr uint32_t
    solve_reccurence(const Matrix<k>& base, const Vector<k>& counts, uint32_t r)
    {
        const auto mp = matrix_power(base, r);
        uint32_t l = 0;
        for (size_t i = 0; i != k; ++i)
        {
            for (size_t j = 0; j != k; ++j)
            {
                l = modAdd(l, modMul(mp[i][j], counts[j]));
            }
        }

        return l;
    }

    static constexpr uint32_t lengthAfterTransformations(
        std::string_view s,
        uint32_t t,
        const std::vector<int>& nums)
    {
        Matrix<26> base{};
        for (uint8_t i = 0; i < 26; i++)
        {
            const int j_end = i + nums[i] + 1;
            for (uint8_t j = i + 1; j != j_end; j++)
            {
                base[j % 26][i] = 1;
            }
        }

        Vector<26> cnt{};
        for (char c : s) ++cnt[std::bit_cast<unsigned>(c - 'a')];

        return solve_reccurence(base, cnt, t);
    }
};

#pragma once

#include <array>
#include <bit>
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <vector>

class Solution2
{
public:
    static constexpr uint32_t kMOD = 1'000'000'007;

    [[nodiscard]] constexpr uint32_t static modAdd(
        uint32_t a,
        uint32_t b) noexcept
    {
        uint64_t r = a + b;
        if (r >= kMOD) r -= kMOD;
        return static_cast<uint32_t>(r);

        // if (r < kMOD) return static_cast<uint32_t>(r);
        // return r % kMOD;
    }

    [[nodiscard]] constexpr uint32_t static modMul(
        uint64_t a,
        uint64_t b) noexcept
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
    [[nodiscard]] static constexpr auto dot(
        const Vector<k>& a,
        const Vector<k>& b) -> uint32_t
    {
        uint32_t r{};
        for (size_t i = 0; i != k; ++i)
        {
            r = modAdd(r, modMul(a[i], b[i]));
        }
        return r;
    }

    template <size_t k>
    [[nodiscard]] static constexpr auto multiply(
        const Matrix<k>& a,
        const Vector<k>& b) -> Vector<k>
    {
        Vector<k> r;
        for (size_t i = 0; i != k; ++i) r[i] = dot(a[i], b);
        return r;
    }

    template <size_t k>
    [[nodiscard]] static constexpr auto multiply(
        const Matrix<k>& a,
        const Matrix<k>& b) -> Matrix<k>
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
    [[nodiscard]] static constexpr auto matrix_power(
        Matrix<k> base,
        uint32_t exp) -> Matrix<k>
    {
        Matrix<k> r;

        if (exp == 0)
        {
            r = {};
            for (size_t i = 0; i < k; ++i) r[i][i] = 1;
            return r;
        }

        r = base;
        std::bitset<32> B(exp);
        int bMax = 31 - std::countl_zero(exp);
        for (int i = bMax - 1; i >= 0; i--)
        {
            r = multiply(r, r);
            if (B[std::bit_cast<unsigned>(i)])
            {
                r = multiply(r, base);
            }
        }

        return r;
    }

    template <size_t k>
    [[nodiscard]] static constexpr auto
    solve_reccurence(const Matrix<k>& base, const Vector<k>& counts, uint32_t r)
        -> uint32_t
    {
        auto mp = matrix_power(base, r);
        uint32_t l = 0;
        for (auto v : multiply(mp, counts)) l = modAdd(l, v);
        return l;
    }

    static constexpr uint32_t lengthAfterTransformations(
        std::string_view s,
        uint32_t t,
        const std::vector<int>& nums)
    {
        Matrix<26> base{};

        for (uint8_t i = 0; i != 26; ++i)
        {
            auto& row = base[i];
            for (uint8_t j = 0; j != 26; ++j)
            {
                if (i == j) continue;
                auto k = nums[j];

                if (j < i)
                {
                    if ((j + k) >= i)
                    {
                        ++row[j];
                    }
                }
                else
                {
                    auto t1 = j + k;
                    auto t2 = t1 % 26;
                    if (t2 < t1 && t2 >= i)
                    {
                        ++row[j];
                    }
                }
            }
        }

        Vector<26> cnt{};
        for (char c : s) ++cnt[std::bit_cast<unsigned>(c - 'a')];

        return solve_reccurence(base, cnt, t);
    }
};

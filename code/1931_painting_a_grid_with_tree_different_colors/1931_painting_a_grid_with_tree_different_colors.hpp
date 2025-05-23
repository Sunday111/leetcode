#pragma once

#include <array>
#include <bit>
#include <bitset>

static constexpr uint32_t kMOD = 1'000'000'007;

[[nodiscard]] constexpr uint32_t static modAdd(uint32_t a, uint32_t b) noexcept
{
    uint64_t r = a + b;
    if (r >= kMOD) r -= kMOD;
    return static_cast<uint32_t>(r);
}

[[nodiscard]] constexpr uint32_t static modMul(uint64_t a, uint64_t b) noexcept
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
[[nodiscard]] static constexpr auto dot(const Vector<k>& a, const Vector<k>& b)
    -> uint32_t
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
[[nodiscard]] static constexpr Matrix<k> matrix_power(
    Matrix<k> base,
    uint16_t exp)
{
    Matrix<k> r;

    if (exp == 0)
    {
        r = {};
        for (size_t i = 0; i < k; ++i) r[i][i] = 1;
        return r;
    }

    r = base;
    std::bitset<sizeof(exp) * 8> exp_bits(exp);
    for (int i = 14 - std::countl_zero(exp); i >= 0; i--)
    {
        r = multiply(r, r);
        if (exp_bits[std::bit_cast<unsigned>(i)])
        {
            r = multiply(r, base);
        }
    }

    return r;
}

template <size_t k>
[[nodiscard]] static constexpr auto
solve_reccurence(const Matrix<k>& base, const Vector<k>& counts, uint16_t r)
    -> uint32_t
{
    auto mp = matrix_power(base, r);
    uint32_t l = 0;
    for (auto v : multiply(mp, counts)) l = modAdd(l, v);
    return l;
}

class Solution
{
public:
    template <uint8_t m, uint8_t prev_color, uint8_t idx>
    static constexpr void genColumns(uint16_t state, uint16_t*& out)
    {
        if constexpr (idx == m)
        {
            *out++ = state;  // NOLINT
            return;
        }
        else
        {
            if constexpr (prev_color != 0)
            {
                uint16_t new_state = (uint16_t{1} << (0 + 3u * idx)) | state;
                genColumns<m, 0, idx + 1>(new_state, out);
            }
            if constexpr (prev_color != 1)
            {
                uint16_t new_state = (uint16_t{1} << (1 + 3u * idx)) | state;
                genColumns<m, 1, idx + 1>(new_state, out);
            }
            if constexpr (prev_color != 2)
            {
                uint16_t new_state = (uint16_t{1} << (2 + 3u * idx)) | state;
                genColumns<m, 2, idx + 1>(new_state, out);
            }
        }
    }

    template <uint8_t m>
    static constexpr uint8_t kNumValidColumns = []
    {
        return (1 << (m - 1)) * 3;
    }();

    template <uint8_t m>
    static constexpr auto kValidColumns = []
    {
        std::array<uint16_t, kNumValidColumns<m>> columns;  // NOLINT
        uint16_t* p = columns.data();
        genColumns<m, 4, 0>(0, p);
        return columns;
    }();

    template <uint8_t m>
    static constexpr auto kTransitionMatrix = []
    {
        constexpr auto& columns = kValidColumns<m>;
        Matrix<columns.size()> matrix{};

        for (size_t i = 0; i != columns.size(); ++i)
        {
            auto from = columns[i];
            for (size_t j = 0; j != columns.size(); ++j)
            {
                auto to = columns[j];
                if ((from & to) == 0)
                {
                    matrix[i][j] = 1;
                }
            }
        }

        return matrix;
    }();

    template <uint8_t m>
    static uint32_t colorTheGrid(uint16_t n)
    {
        Vector<kNumValidColumns<m>> cnt;
        cnt.fill(1u);
        return solve_reccurence(kTransitionMatrix<m>, cnt, n - 1);
    };

    int colorTheGrid(int m, int n)
    {
        auto fn = [&]
        {
            switch (m)
            {
            case 1:
                return colorTheGrid<1>;
                break;
            case 2:
                return colorTheGrid<2>;
                break;
            case 3:
                return colorTheGrid<3>;
                break;
            case 4:
                return colorTheGrid<4>;
                break;
            default:
                return colorTheGrid<5>;
                break;
            }
        }();

        return std::bit_cast<int>(fn(static_cast<uint16_t>(n)));
    }
};

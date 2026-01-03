#include <array>
#include <bitset>

using u8 = uint8_t;
using u32 = uint32_t;

static constexpr u32 kMOD = 1'000'000'007;

[[nodiscard]] constexpr u32 static modAdd(u32 a, u32 b) noexcept
{
    uint64_t r = a + b;
    if (r >= kMOD) r -= kMOD;
    return static_cast<u32>(r);
}

[[nodiscard]] constexpr u32 static modMul(uint64_t a, uint64_t b) noexcept
{
    auto r = a * b;
    if (r < kMOD) return static_cast<u32>(r);
    return r % kMOD;
}

template <size_t k>
using Vector = std::array<u32, k>;

template <size_t k>
using Matrix = std::array<Vector<k>, k>;

template <size_t k>
[[nodiscard]] static constexpr auto dot(const Vector<k>& a, const Vector<k>& b)
    -> u32
{
    u32 r{};
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
[[nodiscard]] static constexpr Matrix<k> matrix_power(Matrix<k> base, u32 exp)
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
    for (int i = 30 - std::countl_zero(exp); i >= 0; i--)
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
solve_reccurence(const Matrix<k>& base, const Vector<k>& counts, u32 r) -> u32
{
    auto mp = matrix_power(base, r);
    u32 l = 0;
    for (auto v : multiply(mp, counts)) l = modAdd(l, v);
    return l;
}

class Solution
{
public:
    struct Triple
    {
        u8 a, b, c;
    };

    inline static constexpr auto kAllRows = []()
    {
        std::array<Triple, 12> rows{};
        u8 t = 0;

        for (u8 i = 0; i != 3; ++i)
        {
            for (u8 j = 0; j != 3; ++j)
            {
                if (j == i) continue;
                for (u8 k = 0; k != 3; ++k)
                {
                    if (k == j) continue;

                    rows[t++] = {i, j, k};
                }
            }
        }

        return rows;
    }();

    inline static constexpr auto kTransitionMatrix = []()
    {
        Matrix<12> m{};

        for (u8 i = 0; i != kAllRows.size(); ++i)
        {
            auto [ai, bi, ci] = kAllRows[i];
            for (u8 j = 0; j != kAllRows.size(); ++j)
            {
                auto [aj, bj, cj] = kAllRows[j];
                if (ai != aj && bi != bj && ci != cj)
                {
                    m[i][j] = 1;
                }
            }
        }

        return m;
    }();

    [[nodiscard]] static constexpr u32 numOfWays(u32 n) noexcept
    {
        Vector<12> cnt;
        cnt.fill(1);
        return solve_reccurence(kTransitionMatrix, cnt, n - 1);
    }
};

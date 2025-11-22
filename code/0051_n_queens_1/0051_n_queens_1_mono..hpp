#include <array>
#include <bit>
#include <cstdint>
#include <string>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

template <u8 n>
class SolutionT
{
public:
    std::vector<std::vector<std::string>> r;
    std::array<u16, n> grid{};
    std::array<u8, n> curr{};

    template <u8 y>
    constexpr void add_queen() noexcept
    {
        grid[y] = 0xFFFF;
        const u16 m = (1 << curr[y]) & 0xFFFF;
        u16 left = m, right = m;
        for (u8 yy = y + 1; yy != n; ++yy)
        {
            grid[yy] |= (m | (left <<= 1) | (right >>= 1));
        }
    }

    template <u8 y = 0>
    constexpr void solve() noexcept
    {
        if constexpr (y == n)
        {
            auto& board = r.emplace_back();
            board.resize(n);
            for (u8 yy = 0; yy != n; ++yy)
            {
                auto& row = board[yy];
                row.resize(n, '.');
                row[curr[yy]] = 'Q';
            }
        }
        else
        {
            constexpr u16 full = (0xFFFF >> (16 - n)) & 0xFFFF;
            u16 row = grid[y] & full;
            while (row != full)
            {
                curr[y] = std::countr_one(row) & 0xFF;
                row |= 1u << curr[y];
                auto saved = grid;
                add_queen<y>();
                solve<y + 1>();
                grid = saved;
            }
        }
    }
};

class Solution
{
public:
    template <u8 n>
    [[nodiscard]] FORCE_INLINE static constexpr auto solve() noexcept
    {
        SolutionT<n> s{};
        s.solve();
        return s.r;
    }

    [[nodiscard]] static constexpr std::vector<std::vector<std::string>>
    totalNQueens(u8 n) noexcept
    {
        constexpr std::array fn{
            &Solution::solve<1>,
            &Solution::solve<2>,
            &Solution::solve<3>,
            &Solution::solve<4>,
            &Solution::solve<5>,
            &Solution::solve<6>,
            &Solution::solve<7>,
            &Solution::solve<8>,
            &Solution::solve<9>,
        };

        return fn[n - 1]();
    }
};

#ifndef __clang__
auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
#endif

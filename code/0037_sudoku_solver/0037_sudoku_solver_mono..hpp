#include <array>
#include <bit>
#include <concepts>
#include <cstdint>
#include <optional>
#include <vector>

#ifdef __GNUC__
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#define FORCE_INLINE inline
#endif

#ifdef __GNUC__
#define HOT_PATH __attribute__((hot))
#else
#define FORCE_INLINE inline
#endif

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & static_cast<T>(-c)) + (b & static_cast<T>(~static_cast<T>(-c)));
}

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

struct OptionsBitset
{
    FORCE_INLINE constexpr void SetBit(u8 idx, bool value) noexcept
    {
        u16 mask = (0b1 << idx) & 0xFFFF;
        bits = iif<u16>(value, bits | mask, bits & ~mask);
    }

    [[nodiscard]] FORCE_INLINE constexpr bool HasBit(u8 idx) const noexcept
    {
        return bits & (0b1 << idx);
    }

    [[nodiscard]] FORCE_INLINE constexpr OptionsBitset operator&(
        const OptionsBitset& rhs) const noexcept
    {
        auto r = *this;
        r.bits &= rhs.bits;
        return r;
    }

    [[nodiscard]] FORCE_INLINE constexpr u8 get_min() const noexcept
    {
        return std::countr_zero(bits) & 0xFF;
    }

    [[nodiscard]] FORCE_INLINE constexpr u8 pop_min() noexcept
    {
        auto m = get_min();
        bits &= ~(1 << m);
        return m;
    }

    [[nodiscard]] FORCE_INLINE constexpr u8 num() const noexcept
    {
        return std::popcount(bits) & 0xFF;
    }

    u16 bits = 0b0011'1111'1110;
};

struct SudokuBoard
{
    [[nodiscard]] FORCE_INLINE constexpr const u8& cell(u8 x, u8 y)
        const noexcept
    {
        return board[y][x];
    }
    [[nodiscard]] FORCE_INLINE constexpr u8& cell(u8 x, u8 y) noexcept
    {
        return board[y][x];
    }

    [[nodiscard]] FORCE_INLINE static constexpr u8 regionIndex(
        u8 x,
        u8 y) noexcept
    {
        return (y / 3) * 3 + x / 3;
    }

    [[nodiscard]] static constexpr SudokuBoard fromArrays(
        const std::vector<std::vector<char>>& input) noexcept
    {
        SudokuBoard board{};
        for (u8 y = 0; y != 9; ++y)
        {
            for (u8 x = 0; x != 9; ++x)
            {
                char c = input[y][x];
                u8 v = (c == '.' ? 0 : c - '0') & 0xFF;
                board.cell(x, y) = v;
            }
        }

        for (u8 y = 0; y != 9; ++y)
        {
            auto& board_row = board.board[y];
            for (u8 x = 0; x != 9; ++x)
            {
                u8 v = board_row[x];
                if (v != 0)
                {
                    board.rows_options[y].SetBit(v, false);
                    board.colums_options[x].SetBit(v, false);
                    board.regions_options[regionIndex(x, y)].SetBit(v, false);
                }
            }
        }

        return board;
    }

    constexpr void toArrays(
        std::vector<std::vector<char>>& arrays) const noexcept
    {
        for (u8 y = 0; y != 9; ++y)
        {
            for (u8 x = 0; x != 9; ++x)
            {
                arrays[y][x] = static_cast<char>('0' + cell(x, y));
            }
        }
    }

    [[nodiscard]] HOT_PATH constexpr std::tuple<u8, u8, OptionsBitset>
    findBestCandidate() const noexcept
    {
        u8 min_vairance = 10, rx = 10, ry = 10;
        OptionsBitset best_opts{};

        for (u8 y = 0; y != 9; ++y)
        {
            for (u8 x = 0; x != 9; ++x)
            {
                u8 v = cell(x, y);
                if (v) continue;

                OptionsBitset opts = rows_options[y] & colums_options[x] &
                                     regions_options[regionIndex(x, y)];
                u8 variance = opts.num();
                if (variance < min_vairance)
                {
                    min_vairance = variance, rx = x, ry = y, best_opts = opts;
                    if (variance == 1)
                    {
                        break;
                    }
                }
            }
        }

        return {rx, ry, best_opts};
    }

    HOT_PATH constexpr bool setCellAndCheck(u8 x, u8 y, u8 v) noexcept
    {
        cell(x, y) = v;

        {
            auto& opts = rows_options[y];
            opts.SetBit(v, false);
            if (opts.num() == 0)
            {
                for (u8 tx = 0; tx != 9; ++tx)
                {
                    if (cell(tx, y) == 0) return false;
                }
            }
        }

        {
            auto& opts = colums_options[x];
            opts.SetBit(v, false);

            if (opts.num() == 0)
            {
                for (u8 ty = 0; ty != 9; ++ty)
                {
                    if (cell(x, ty) == 0) return false;
                }
            }
        }

        {
            u8 ri = regionIndex(x, y);
            auto& opts = regions_options[ri];
            opts.SetBit(v, false);

            if (opts.num() == 0)
            {
                u8 sx = 3 * (x / 3), sy = 3 * (y / 3);
                for (u8 dy = 0; dy != 3; ++dy)
                {
                    for (u8 dx = 0; dx != 3; ++dx)
                    {
                        if (cell(sx + dx, sy + dy) == 0) return false;
                    }
                }
            }
        }

        return true;
    }

    [[nodiscard]] constexpr std::optional<SudokuBoard> solve() const noexcept
    {
        auto b = *this;

        u8 x{}, y{};
        OptionsBitset opts;

        while (std::tie(x, y, opts) = b.findBestCandidate(), x != 10)
        {
            if (opts.num() == 0)
            {
                return std::nullopt;
            }

            if (opts.num() == 1)
            {
                // Only one option. Avoid unnecessary recursion step
                if (!b.setCellAndCheck(x, y, opts.get_min()))
                {
                    return std::nullopt;
                }

                continue;
            }

            // Try all available options
            while (opts.num())
            {
                auto tmp = b;
                if (tmp.setCellAndCheck(x, y, opts.pop_min()))
                {
                    auto solved = tmp.solve();
                    if (solved.has_value()) return solved;
                }
            }

            return std::nullopt;
        }

        return b;
    }

    std::array<std::array<u8, 9>, 9> board{};
    std::array<OptionsBitset, 9> rows_options{};
    std::array<OptionsBitset, 9> colums_options{};
    std::array<OptionsBitset, 9> regions_options{};
};

class Solution
{
public:
    static constexpr void solveSudoku(
        std::vector<std::vector<char>>& sb) noexcept
    {
        // there is a guarantee to have a solution so no need to check optional
        SudokuBoard::fromArrays(sb).solve()->toArrays(sb);
    }
};

#pragma once

#include <array>
#include <bit>
#include <optional>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;

struct OptionsBitset
{
    constexpr void SetBit(u8 idx, bool value) noexcept
    {
        u16 mask = (0b1 << idx) & 0xFFFF;
        options = value ? (options | mask) : (options & ~mask);
    }

    [[nodiscard]] constexpr bool HasBit(u8 idx) const noexcept
    {
        return options & (0b1 << idx);
    }

    [[nodiscard]] constexpr OptionsBitset operator&(
        const OptionsBitset& rhs) const noexcept
    {
        auto r = *this;
        r.options &= rhs.options;
        return r;
    }

    [[nodiscard]] constexpr u8 min() const noexcept
    {
        return std::countr_zero(options) & 0xFF;
    }

    [[nodiscard]] constexpr u8 num() const noexcept
    {
        return std::popcount(options) & 0xFF;
    }

    static constexpr u16 kAllOptions = 0b0011'1111'1110;
    u16 options = kAllOptions;
};

struct SudokuBoard
{
    [[nodiscard]] constexpr const u8& cell(u8 x, u8 y) const noexcept
    {
        return board[y][x];
    }
    [[nodiscard]] constexpr u8& cell(u8 x, u8 y) noexcept
    {
        return board[y][x];
    }

    [[nodiscard]] static constexpr u8 regionIndex(u8 x, u8 y) noexcept
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

    [[nodiscard]] constexpr std::tuple<u8, u8, OptionsBitset>
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

    constexpr bool setCellAndCheck(u8 x, u8 y, u8 v) noexcept
    {
        cell(x, y) = v;

        {
            auto& opts = rows_options[y];
            opts.SetBit(v, false);
            if (opts.num() == 0)
            {
                for (u8 tx = 0; tx != 9; ++tx)
                {
                    if (cell(tx, y) == 0)
                    {
                        return false;
                    }
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
                    if (cell(x, ty) == 0)
                    {
                        return false;
                    }
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
                        if (cell(sx + dx, sy + dy) == 0)
                        {
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }

    [[nodiscard]] constexpr std::optional<SudokuBoard> solve() const noexcept
    {
        auto b = *this;

        while (true)
        {
            auto [x, y, opts] = b.findBestCandidate();
            if (x == 10) return b;

            if (opts.num() == 0)
            {
                return std::nullopt;
            }

            if (opts.num() == 1)
            {
                if (!b.setCellAndCheck(x, y, opts.min()))
                {
                    return std::nullopt;
                }
            }
            else
            {
                while (opts.options)
                {
                    auto test = b;
                    if (test.setCellAndCheck(x, y, opts.min()))
                    {
                        auto solved = test.solve();
                        if (solved.has_value()) return solved;
                    }

                    opts.options &= ~(1 << opts.min());
                }

                return std::nullopt;
            }
        }

        std::unreachable();
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

#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <span>
#include <string>
#include <utility>
#include <vector>

#ifdef __GNUC__
#define ATTR inline __attribute__((always_inline))
#else
#define ATTR inline
#endif

using u8 = uint8_t;
using i8 = int8_t;

struct Vec2
{
    i8 x;
    i8 y;

    ATTR constexpr Vec2& operator+=(const Vec2& v) noexcept
    {
        x += v.x;  // NOLINT
        y += v.y;  // NOLINT
        return *this;
    }
    ATTR constexpr bool operator==(const Vec2&) const noexcept = default;

    [[nodiscard]] static constexpr Vec2 from_vector(
        const std::vector<int>& vec) noexcept
    {
        return Vec2{
            .x = static_cast<int8_t>(vec[0] - 1),
            .y = static_cast<int8_t>(vec[1] - 1),
        };
    }
};

struct PieceState
{
    Vec2 target_position;
    Vec2 current_direction;
};

enum class Piece : u8
{
    Rook,
    Bishop,
    Queen
};

inline constexpr std::array<Vec2, 4> kRookDirs{{
    {0, 1},
    {1, 0},
    {-1, 0},
    {0, -1},
}};

inline constexpr std::array<Vec2, 4> kBishopDirs{{
    {1, 1},
    {-1, 1},
    {1, -1},
    {-1, -1},
}};

inline constexpr std::array<Vec2, 8> kQueenDirs{{
    {1, 1},
    {-1, 1},
    {1, -1},
    {-1, -1},
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1},
}};

template <auto pieces>
class SolutionK
{
public:
    static constexpr u8 num_pieces = pieces.size() & 0xFF;

    [[nodiscard]] ATTR static constexpr u8 to_index(
        const Vec2& position) noexcept
    {
        return static_cast<u8>(position.y * 8 + position.x);
    }

    [[nodiscard]] ATTR static constexpr bool is_valid(const Vec2& p) noexcept
    {
        constexpr u8 mask = 0b111;
        return ((p.x & mask) == p.x) && ((p.y & mask) == p.y);
    }

    [[nodiscard]] constexpr bool ATTR validate_paths(
        const std::array<PieceState, num_pieces>& states) const noexcept
    {
        auto positions = start_positions;
        auto board = initial_board;

        u8 num_completed = 0;
        while (num_completed != num_pieces)
        {
            std::bitset<64> next_board;

            num_completed = 0;
            for (u8 i = 0; i != num_pieces; ++i)
            {
                auto& state = states[i];
                Vec2& pos = positions[i];
                if (pos == state.target_position)
                {
                    ++num_completed;
                }
                else
                {
                    pos += state.current_direction;
                }
                u8 idx = to_index(pos);
                if (next_board[idx]) return false;
                next_board[idx] = true;
            }

            board = next_board;
        }

        return true;
    }

    template <u8 piece_index>
    [[nodiscard]] ATTR static consteval auto& get_piece_directions() noexcept
    {
        if constexpr (pieces[piece_index] == Piece::Bishop)
        {
            return kBishopDirs;
        }
        else if constexpr (pieces[piece_index] == Piece::Rook)
        {
            return kRookDirs;
        }
        else
        {
            return kQueenDirs;
        }
    }

    template <u8 current_piece>
    [[nodiscard]] ATTR constexpr uint32_t solve_r(
        std::array<PieceState, num_pieces>& states) const noexcept
    {
        if constexpr (current_piece == num_pieces)
        {
            return validate_paths(states) ? 1 : 0;
        }
        else
        {
            auto& state = states[current_piece];
            // First pass - this piece does not move
            state.target_position = start_positions[current_piece];
            state.current_direction = {};
            uint32_t r = solve_r<current_piece + 1>(states);

            // Now move the piece in all available directions
            for (const Vec2& dir : get_piece_directions<current_piece>())
            {
                state.current_direction = dir;
                state.target_position = start_positions[current_piece];
                while (is_valid(state.target_position += dir))
                {
                    r += solve_r<current_piece + 1>(states);
                }
            }

            return r;
        }
    }

    std::array<Vec2, num_pieces> start_positions;
    std::bitset<64> initial_board;

    [[nodiscard]] constexpr uint32_t countCombinations(
        const std::array<Vec2, num_pieces>& in_start_positions) noexcept
    {
        start_positions = in_start_positions;
        for (u8 i = 0; i != num_pieces; ++i)
        {
            initial_board[to_index(start_positions[i])] = true;
        }

        std::array<PieceState, num_pieces> states;  // NOLINT
        return solve_r<0>(states);
    }
};

class Solution
{
public:
    template <u8 r, u8 b, u8 q>
    static constexpr std::array<u8, 3> kCntArr{r, b, q};

    template <size_t num_pieces>
    [[nodiscard]] ATTR static constexpr std::array<Vec2, num_pieces>
    make_coords_array(
        std::span<const u8> indices,
        const std::vector<std::vector<int>>& positions) noexcept
    {
        std::array<Vec2, num_pieces> coords;  // NOLINT

        for (u8 i = 0; i != num_pieces; ++i)
        {
            coords[i] = Vec2::from_vector(positions[indices[i]]);
        }

        return coords;
    }

    template <auto cnt_arr>
    [[nodiscard]] ATTR static constexpr auto cnt_arr_to_pieces() noexcept
    {
        std::array<Piece, cnt_arr[0] + cnt_arr[1] + cnt_arr[2]> r;  // NOLINT
        u8 next = 0;
        for (u8 i = 0; i != cnt_arr[0]; ++i) r[next++] = Piece::Rook;
        for (u8 i = 0; i != cnt_arr[1]; ++i) r[next++] = Piece::Bishop;
        for (u8 i = 0; i != cnt_arr[2]; ++i) r[next++] = Piece::Queen;
        return r;
    }

    template <size_t num_pieces, auto... variants>
    [[nodiscard]] ATTR static constexpr uint32_t choose(
        const std::array<u8, 3>& cnt,
        const std::array<u8, 4>& indices,
        const std::vector<std::vector<int>>& positions)
    {
        const auto coords =
            make_coords_array<num_pieces>(std::span{indices}, positions);
        uint32_t r = 0;
        auto try_one = [&]<auto variant>()
        {
            if (variant == cnt)
            {
                r = SolutionK<cnt_arr_to_pieces<variant>()>{}.countCombinations(
                    coords);
                return true;
            }

            return false;
        };

        if ((false || ... || try_one.template operator()<variants>()))
        {
            return r;
        }

        std::unreachable();
    }

    [[nodiscard]] ATTR static constexpr uint32_t countCombinations(
        std::vector<std::string>& pieces_str,
        std::vector<std::vector<int>>& positions) noexcept
    {
        std::array<Piece, 4> pieces_vals;  // NOLINT
        u8 n = positions.size() & 0xFF;
        std::array<u8, 3> cnt{};
        for (u8 i = 0; i != n; ++i)
        {
            switch (pieces_str[i].front())
            {
            case 'r':
                ++cnt[0];
                pieces_vals[i] = Piece::Rook;
                break;
            case 'b':
                ++cnt[1];
                pieces_vals[i] = Piece::Bishop;
                break;
            case 'q':
                ++cnt[2];
                pieces_vals[i] = Piece::Queen;
                break;
            }
        }

        std::array<u8, 4> indices_vals{0, 1, 2, 3};
        std::ranges::sort(
            std::span{indices_vals}.subspan(0, pieces_str.size()),
            std::less<>{},
            [&](u8 i) { return pieces_vals[i]; });

        switch (pieces_str.size())
        {
        case 1:
            return choose<
                1,
                kCntArr<1, 0, 0>,
                kCntArr<0, 1, 0>,
                kCntArr<0, 0, 1>>(cnt, indices_vals, positions);
        case 2:
            return choose<
                2,
                kCntArr<2, 0, 0>,
                kCntArr<1, 1, 0>,
                kCntArr<0, 2, 0>,
                kCntArr<1, 0, 1>,
                kCntArr<0, 1, 1>>(cnt, indices_vals, positions);

        case 3:
            return choose<
                3,
                kCntArr<3, 0, 0>,
                kCntArr<2, 1, 0>,
                kCntArr<1, 2, 0>,
                kCntArr<0, 3, 0>,
                kCntArr<2, 0, 1>,
                kCntArr<1, 1, 1>,
                kCntArr<0, 2, 1>>(cnt, indices_vals, positions);

        case 4:
            return choose<
                4,
                kCntArr<4, 0, 0>,
                kCntArr<3, 1, 0>,
                kCntArr<2, 2, 0>,
                kCntArr<1, 3, 0>,
                kCntArr<0, 4, 0>,
                kCntArr<3, 0, 1>,
                kCntArr<2, 1, 1>,
                kCntArr<1, 2, 1>,
                kCntArr<0, 3, 1>>(cnt, indices_vals, positions);

        default:
            std::unreachable();
        }
    }
};

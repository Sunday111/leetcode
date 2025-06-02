#pragma once

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

struct Vec2
{
    int8_t x;
    int8_t y;

    ATTR constexpr Vec2& operator+=(const Vec2& v) noexcept
    {
        x += v.x;  // NOLINT
        y += v.y;  // NOLINT
        return *this;
    }
    ATTR constexpr bool operator==(const Vec2&) const noexcept = default;
};

struct PieceState
{
    Vec2 target_position;
    Vec2 current_direction;
};

template <size_t num_pieces>
class SolutionK
{
public:
    static constexpr std::array<Vec2, 4> kRookDirs{{
        {0, 1},
        {1, 0},
        {-1, 0},
        {0, -1},
    }};

    static constexpr std::array<Vec2, 4> kBishopDirs{{
        {1, 1},
        {-1, 1},
        {1, -1},
        {-1, -1},
    }};

    static constexpr std::array<Vec2, 8> kQueenDirs{{
        {1, 1},
        {-1, 1},
        {1, -1},
        {-1, -1},
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1},
    }};

    [[nodiscard]] ATTR static constexpr uint8_t to_index(
        const Vec2& position) noexcept
    {
        return static_cast<uint8_t>(position.y * 8 + position.x);
    }

    [[nodiscard]] ATTR static constexpr bool is_valid(const Vec2& p) noexcept
    {
        constexpr uint8_t mask = 0b111;
        return ((p.x & mask) == p.x) && ((p.y & mask) == p.y);
    }

    [[nodiscard]] constexpr bool ATTR validate_paths(
        const std::array<PieceState, num_pieces>& states) const noexcept
    {
        auto positions = start_positions;
        auto board = initial_board;

        uint8_t num_completed = 0;
        while (num_completed != num_pieces)
        {
            std::bitset<64> next_board;

            num_completed = 0;
            for (uint8_t i = 0; i != num_pieces; ++i)
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
                uint8_t idx = to_index(pos);
                if (next_board[idx]) return false;
                next_board[idx] = true;
            }

            board = next_board;
        }

        return true;
    }

    template <uint8_t current_piece>
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
            for (const Vec2& dir : all_directions[current_piece])
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
    std::array<std::span<const Vec2>, num_pieces> all_directions;

    [[nodiscard]] constexpr uint32_t countCombinations(
        const std::vector<std::string>& in_pieces,
        const std::vector<std::vector<int>>& in_positions) noexcept
    {
        for (uint8_t i = 0; i != num_pieces; ++i)
        {
            start_positions[i].x = static_cast<int8_t>(in_positions[i][0] - 1);
            start_positions[i].y = static_cast<int8_t>(in_positions[i][1] - 1);
            initial_board[to_index(start_positions[i])] = true;
            switch (in_pieces[i].front())
            {
            case 'r':
                all_directions[i] = kRookDirs;
                break;
            case 'b':
                all_directions[i] = kBishopDirs;
                break;
            case 'q':
                all_directions[i] = kQueenDirs;
                break;
            }
        }

        std::array<PieceState, num_pieces> states;  // NOLINT
        return solve_r<0>(states);
    }
};

class Solution
{
public:
    [[nodiscard]] ATTR static constexpr uint32_t countCombinations(
        std::vector<std::string>& pieces,
        std::vector<std::vector<int>>& positions) noexcept
    {
        switch (pieces.size())
        {
        case 1:
            return SolutionK<1>{}.countCombinations(pieces, positions);
            break;
        case 2:
            return SolutionK<2>{}.countCombinations(pieces, positions);
            break;
        case 3:
            return SolutionK<3>{}.countCombinations(pieces, positions);
            break;
        case 4:
            return SolutionK<4>{}.countCombinations(pieces, positions);
            break;

        default:
            std::unreachable();
        }
    }
};

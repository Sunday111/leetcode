#pragma once

#include <cassert>
#include <vector>

class Solution
{
public:
    static constexpr auto kDead = 0;
    static constexpr auto kAlive = 1;
    static constexpr auto kDied = 2;
    static constexpr auto kBorn = 3;

    void gameOfLife(std::vector<std::vector<int>>& board)
    {
        const size_t h = board.size();
        const size_t w = board.front().size();

        auto get_cell = [&](size_t x, size_t y) -> int&
        {
            // assert(y < h);
            auto& row = board[y];
            // assert(x < row.size());
            return row[x];
        };

        for (size_t y = 0; y != h; ++y)
        {
            size_t ny_begin = y;
            if (y != 0) --ny_begin;
            size_t ny_end = y + 1;
            if (ny_end != h) ++ny_end;

            // auto& row = board[y];

            for (size_t x = 0; x != w; ++x)
            {
                size_t nx_begin = x;
                if (x != 0) --nx_begin;
                size_t nx_end = x + 1;
                if (nx_end != w) ++nx_end;

                auto& cell = get_cell(x, y);

                size_t alive_neighbours = 0;
                [&]
                {
                    for (size_t ny = ny_begin; ny != ny_end; ++ny)
                    {
                        for (size_t nx = nx_begin; nx != nx_end; ++nx)
                        {
                            const auto& neigbour = get_cell(nx, ny);
                            if (&neigbour != &cell &&
                                (neigbour == kAlive || neigbour == kDied))
                            {
                                if (++alive_neighbours > 3)
                                {
                                    return;
                                }
                            }
                        }
                    }
                }();

                if (cell == kAlive)
                {
                    if (alive_neighbours < 2 || alive_neighbours > 3)
                    {
                        cell = kDied;
                    }
                }
                else
                {
                    if (alive_neighbours == 3)
                    {
                        cell = kBorn;
                    }
                }
            }
        }

        for (size_t y = 0; y != h; ++y)
        {
            auto& row = board[y];
            for (size_t x = 0; x != w; ++x)
            {
                auto& cell = row[x];
                if (cell == kBorn) cell = kAlive;
                if (cell == kDied) cell = kDead;
            }
        }
    }
};

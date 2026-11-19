#pragma once

#include <string>
#include <vector>

class Robot
{
public:
    struct Cell
    {
        std::vector<int> pos;
        std::string dir;
    };

    Robot(size_t width, size_t height)
    {
        size_t p = 2 * (width + height - 2);
        perimeter_cells.reserve(p);
        size_t max_x = width - 1;
        size_t max_y = height - 1;

        {
            auto& cell = perimeter_cells.emplace_back();
            cell.pos = {0, 0};
            cell.dir = "South";
        }

        size_t x{}, y{};
        for (x = 1, y = 0; x != width; ++x)
        {
            auto& cell = perimeter_cells.emplace_back();
            cell.pos = {static_cast<int>(x), static_cast<int>(y)};
            cell.dir = "East";
        }

        ;
        for (x = max_x, y = 1; y != height; ++y)
        {
            auto& cell = perimeter_cells.emplace_back();
            cell.pos = {static_cast<int>(x), static_cast<int>(y)};
            cell.dir = "North";
        }

        x = max_x, y = max_y;
        do
        {
            --x;
            auto& cell = perimeter_cells.emplace_back();
            cell.pos = {static_cast<int>(x), static_cast<int>(y)};
            cell.dir = "West";
        } while (x != 0);

        x = 0;
        y = max_y;
        while (--y != 0)
        {
            auto& cell = perimeter_cells.emplace_back();
            cell.pos = {static_cast<int>(x), static_cast<int>(y)};
            cell.dir = "South";
        }
    }

    void step(size_t num)
    {
        [[unlikely]] if (!moved && num > 0)
        {
            moved = true;
        }

        offset += num;
    }

    const std::vector<int>& getPos() const
    {
        auto& cell = perimeter_cells[offset % perimeter_cells.size()];
        return cell.pos;
    }

    const std::string& getDir() const
    {
        if (!moved) return perimeter_cells[1].dir;
        return perimeter_cells[offset % perimeter_cells.size()].dir;
    }

    bool moved = false;
    size_t offset = 0;
    std::vector<Cell> perimeter_cells;
};

#pragma once

#include <algorithm>
#include <functional>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    struct Building
    {
        u32 left;
        u32 right;
        u32 height;
    };

    [[nodiscard]] static std::vector<std::vector<int>> getSkyline(
        const std::vector<std::vector<int>>& buildings) noexcept
    {
        const size_t n = buildings.size();
        constexpr Building kGround{
            .left = 0,
            .right = std::numeric_limits<u32>::max(),
            .height = 0,
        };

        std::vector<const Building*> heap;
        heap.reserve(n);
        heap.push_back(&kGround);

        std::vector<std::vector<int>> skyline_;
        auto& skyline =
            reinterpret_cast<std::vector<std::vector<u32>>&>(  // NOLINT
                skyline_);

        auto pop_tallest = [&]
        {
            auto& prev_tallest = *heap.front();
            while (heap.front()->right <= prev_tallest.right)
            {
                std::ranges::pop_heap(heap, std::less<>{}, &Building::height);
                heap.pop_back();
            }

            auto& tallest = *heap.front();
            if (tallest.height != prev_tallest.height &&
                prev_tallest.right > skyline.back()[0])
            {
                skyline.push_back(
                    std::vector<u32>{prev_tallest.right, tallest.height});
            }
        };

        auto building_at = [&](size_t idx) -> const Building&
        {
            auto& vec = buildings[idx];
            auto& building =
                *reinterpret_cast<const Building*>(vec.data());  // NOLINT
            return building;
        };

        for (size_t next = 0; next != n;)
        {
            const u32 x = building_at(next).left;

            // pop all buildings that end before x
            while (heap.front()->right < x)
            {
                pop_tallest();
            }

            // Add all buildings that start at the same X
            const u32 prev_height = heap.front()->height;
            for (; next != n && building_at(next).left == x; ++next)
            {
                heap.push_back(&building_at(next));
                std::ranges::push_heap(heap, std::less<>{}, &Building::height);
            }

            // Add skyline point if height increased
            if (const u32 height = heap.front()->height; height > prev_height)
            {
                auto& building = *heap.front();
                skyline.push_back(
                    std::vector<u32>{
                        building.left,
                        building.height,
                    });
            }
        }

        while (heap.size() > 1) pop_tallest();

        return skyline_;
    }
};

#pragma once

#include <algorithm>
#include <vector>

class Solution
{
    template <bool size_is_odd>
    static constexpr void flipAndInvertImageRow(std::vector<int>& row)
    {
        auto left = row.begin();
        auto right = std::prev(row.end());
        while (left < right)
        {
            std::swap(*left, *right);
            *left = !*left;
            *right = !*right;
            left = std::next(left);
            right = std::prev(right);
        }

        // invert midpoint if size is odd
        if constexpr (size_is_odd) *left = !*left;
    }

public:
    [[nodiscard]] static constexpr std::vector<std::vector<int>>
    flipAndInvertImage(std::vector<std::vector<int>>& image)
    {
        if (image.size() % 2)
        {
            std::ranges::for_each(image, flipAndInvertImageRow<true>);
        }
        else
        {
            std::ranges::for_each(image, flipAndInvertImageRow<false>);
        }

        return std::move(image);
    }
};

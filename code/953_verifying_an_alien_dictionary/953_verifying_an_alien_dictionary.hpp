#pragma once

#include <algorithm>
#include <array>
#include <string>
#include <string_view>
#include <vector>

class Solution
{
public:
    static bool isAlienSorted(
        const std::vector<std::string>& words,
        std::string_view order)
    {
        constexpr size_t num_letters = ('z' - 'a') + 1;
        std::array<uint8_t, num_letters> letters_indices{};

        auto relative_letter_index = [](char c) -> size_t
        {
            return static_cast<size_t>(c - 'a');
        };

        for (size_t i = 0; i != order.size(); ++i)
        {
            letters_indices[relative_letter_index(order[i])] =
                static_cast<uint8_t>(i);
        }

        auto get_letter_order = [&](char letter) -> uint8_t
        {
            return letters_indices[relative_letter_index(letter)];
        };

        auto less = [&](const std::string& left, const std::string& right)
        {
            const size_t n = std::min(left.size(), right.size());
            for (size_t i = 0; i != n; ++i)
            {
                const uint8_t left_order = get_letter_order(left[i]);
                const uint8_t right_order = get_letter_order(right[i]);
                if (left_order != right_order) return left_order < right_order;
            }

            return left.size() < right.size();
        };

        return std::ranges::is_sorted(words, less);
    }
};

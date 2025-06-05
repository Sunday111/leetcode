#pragma once

#include <algorithm>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<std::string> printVertically(
        std::string_view s) noexcept
    {
        uint8_t column = 0, row_idx = 0;
        std::vector<std::string> rows;
        rows.reserve(101);

        for (char c : s)
        {
            if (c == ' ')
            {
                row_idx = 0;
                ++column;
                continue;
            }

            rows.resize(std::max<size_t>(row_idx + 1, rows.size()));
            auto& row = rows[row_idx++];

            while (std::cmp_less(row.size(), column))
            {
                row.push_back(' ');
            }

            row.push_back(c);
        }

        return rows;
    }
};

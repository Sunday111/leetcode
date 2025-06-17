#pragma once

#include <string_view>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> executeInstructions(
        int n,
        const std::vector<int>& startPos,
        std::string_view s) noexcept
    {
        const int start_y = startPos[0], start_x = startPos[1];

        std::vector<int> r;
        r.reserve(s.size());

        for (size_t i = 0; i != s.size(); ++i)
        {
            int x = start_x, y = start_y;
            size_t j = i;
            for (; j != s.size(); ++j)
            {
                switch (s[j])
                {
                case 'L':
                    --x;
                    break;
                case 'R':
                    ++x;
                    break;
                case 'U':
                    --y;
                    break;
                case 'D':
                    ++y;
                    break;
                }

                if (x < 0 || x == n || y < 0 || y == n) break;
            }

            r.push_back(static_cast<int>(j - i));
        }

        return r;
    }
};

#pragma once

#include <string_view>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<std::vector<int>>
    largeGroupPositions(std::string_view s) noexcept
    {
        std::vector<std::vector<int>> r;
        const size_t n = s.size();

        size_t i = 0, j = 1;
        auto flush = [&]()
        {
            size_t l = j - i;
            if (l >= 3)
            {
                r.push_back(
                    std::vector<int>{
                        static_cast<int>(i),
                        static_cast<int>(j - 1),
                    });
            }
        };

        for (; j != n; ++j)
        {
            if (s[j] != s[i])
            {
                flush();
                i = j;
            }
        }

        flush();

        return r;
    }
};

#pragma once

#include <string>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<std::string> buildArray(
        const std::vector<int>& target,
        size_t n) noexcept
    {
        std::vector<std::string> r;
        r.reserve(n * 2);

        const std::string push{"Push"};
        const std::string pop{"Pop"};

        int i = 1;
        for (int t : target)
        {
            while (i++ != t)
            {
                r.emplace_back(push);
                r.emplace_back(pop);
            }
            r.emplace_back(push);
        }

        return r;
    }
};

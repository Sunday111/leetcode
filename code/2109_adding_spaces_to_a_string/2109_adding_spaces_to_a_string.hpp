#pragma once

#include <string>
#include <string_view>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::string addSpaces(
        const std::string_view s,
        const std::vector<int>& spaces) noexcept
    {
        std::string r;
        r.reserve(s.size() + spaces.size());

        size_t prev = 0;
        for (int ii : spaces)
        {
            const size_t i = static_cast<size_t>(ii);
            r.append(s.substr(prev, i - prev));
            r.push_back(' ');
            prev = i;
        }

        r.append(s.substr(prev));
        return r;
    }
};

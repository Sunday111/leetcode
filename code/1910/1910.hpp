#pragma once

#include <string>
#include <string_view>

class Solution
{
public:
    [[nodiscard]] static constexpr std::string removeOccurrences(
        std::string_view s,
        std::string_view part) noexcept
    {
        std::string r;
        r.reserve(s.size());

        for (char c : s)
        {
            r.push_back(c);
            while (r.ends_with(part))
            {
                r.resize(r.size() - part.size());
            }
        }

        return r;
    }
};

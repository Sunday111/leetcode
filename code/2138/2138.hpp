#pragma once

#include <string>
#include <string_view>
#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] static constexpr auto
    divideString(std::string_view s, u8 k, char fill) noexcept
    {
        std::vector<std::string> r;

        r.reserve((s.size() / k) + 1);

        while (s.size() >= k)
        {
            r.emplace_back(s.substr(0, k));
            s = s.substr(k);
        }

        if (!s.empty())
        {
            r.emplace_back(s);
            r.back().resize(k, fill);
        }

        return r;
    }
};

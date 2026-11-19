#pragma once

#include <string>

namespace simple
{

class Solution
{
public:
    [[nodiscard]] static constexpr std::string mergeAlternately(
        std::string_view a,
        std::string_view b) noexcept
    {
        const size_t la = a.size(), lb = b.size(), ls = std::min(la, lb);
        std::string r;
        r.reserve(la + lb);
        for (size_t i = 0; i != ls; ++i)
        {
            r.push_back(a[i]);
            r.push_back(b[i]);
        }
        r.append((la > lb ? a : b).substr(ls));
        return r;
    }
};

}  // namespace simple

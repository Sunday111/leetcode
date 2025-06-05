#pragma once

#include <ranges>
#include <string_view>

class Solution
{
public:
    [[nodiscard]] static constexpr size_t numSteps(std::string_view s) noexcept
    {
        auto t = s.rfind('1');
        auto tail = s.substr(1, t);
        size_t r = s.size() - 1 - t;
        for (char c : tail | std::views::reverse) r += c == '0';
        if (tail.size()) r += tail.size() + 2;
        return r;
    }
};

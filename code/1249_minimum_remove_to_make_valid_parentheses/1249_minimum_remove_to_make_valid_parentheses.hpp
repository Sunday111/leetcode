#pragma once

#include <algorithm>
#include <ranges>
#include <string>
#include <string_view>

class Solution
{
public:
    template <char open, char closed>
    constexpr static uint32_t pass(
        std::ranges::input_range auto&& from,
        std::string& to)
    {
        uint32_t num_open = 0;
        for (char c : from)
        {
            bool add = true;
            switch (c)
            {
            case open:
                ++num_open;
                break;
            case closed:
                if (num_open == 0)
                {
                    add = false;
                }
                else
                {
                    --num_open;
                }
                break;
            }

            if (add) to.push_back(c);
        }

        return num_open;
    }

    [[nodiscard]] constexpr static std::string minRemoveToMakeValid(
        std::string a)
    {
        std::string b;
        b.reserve(a.size());
        if (pass<'(', ')'>(a, b) != 0)
        {
            a.clear();
            pass<')', '('>(std::views::reverse(b), a);
            std::ranges::reverse(a);
            std::swap(a, b);
        }

        return b;
    }
};

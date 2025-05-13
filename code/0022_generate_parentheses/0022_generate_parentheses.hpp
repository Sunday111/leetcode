#pragma once

#include <array>
#include <string>
#include <vector>

// class Solution
// {
// public:
//     std::vector<std::string> r;
//     std::string current;
//     uint8_t n = 0, open = 0, closed = 0;

//     void dfs()
//     {
//         if (closed == n)
//         {
//             r.push_back(current);
//             return;
//         }

//         if (open < n)
//         {
//             current.push_back('(');
//             ++open;
//             dfs();
//             --open;
//             current.pop_back();
//         }

//         if (closed < open)
//         {
//             current.push_back(')');
//             ++closed;
//             dfs();
//             --closed;
//             current.pop_back();
//         }
//     }

//     std::vector<std::string> generateParenthesis(uint8_t in_n)
//     {
//         r.reserve(1430);
//         open = 0;
//         closed = 0;
//         n = in_n;
//         dfs();
//         return std::move(r);
//     }
// };

class Solution
{
public:
    std::vector<std::string> generateParenthesis(uint8_t n)
    {
        constexpr uint8_t entry = 0, try_open = 1, tried_open = 2,
                          try_closed = 3, tried_closed = 4;

        std::vector<std::string> r;
        r.reserve(1430);

        std::string current;
        current.reserve(n * 2);
        std::array<uint8_t, 24> states{entry};
        uint8_t open = 0, closed = 0, stack_depth = 1;

        auto push = [&](auto... s)
        {
            ((states[stack_depth++] = s), ...);
        };

        do
        {
            switch (states[--stack_depth])
            {
            case entry:
                if (closed == n)
                {
                    r.push_back(current);
                }
                else
                {
                    if (open < n) push(try_open);
                    if (closed < open) push(try_closed);
                }
                break;
            case try_open:
                current.push_back('(');
                ++open;
                push(tried_open, entry);
                break;
            case tried_open:
                current.pop_back();
                --open;
                break;
            case try_closed:
                current.push_back(')');
                ++closed;
                push(tried_closed, entry);
                break;
            case tried_closed:
                current.pop_back();
                --closed;
                break;
            }
        } while (stack_depth != 0);

        return r;
    }
};

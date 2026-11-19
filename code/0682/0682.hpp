#pragma once

#include <string>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int parse(const std::string& s)
    {
        int r = 0;
        size_t i = 0;
        bool negative = false;
        if (s[i] == '-')
        {
            negative = true;
            ++i;
        }

        for (; i != s.size(); ++i)
        {
            r = r * 10 + (s[i] - '0');
        }

        return negative ? -r : r;
    }

    [[nodiscard]] static constexpr int calPoints(
        const std::vector<std::string>& operations)
    {
        int r = 0;

        std::vector<int> values;
        auto push = [&](int v)
        {
            r += v;
            values.push_back(v);
        };

        for (const auto& op : operations)
        {
            if (op == "C")
            {
                r -= values.back();
                values.pop_back();
                continue;
            }

            if (op == "D")
            {
                push(values.back() * 2);
                continue;
            }

            if (op == "+")
            {
                push(values.back() + values[values.size() - 2]);
                continue;
            }

            push(parse(op));
        }

        return r;
    }
};

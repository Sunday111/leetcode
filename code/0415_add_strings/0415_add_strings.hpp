#pragma once

#include <algorithm>
#include <string>
#include <string_view>

class Solution
{
public:
    std::string addStrings(std::string_view num1, std::string_view num2)
    {
        std::string r;
        r.reserve(std::max(num1.size(), num2.size()) + 1);

        auto a = num1.rbegin();
        auto b = num2.rbegin();

        uint8_t carry = 0;

        while (true)
        {
            bool has_a = a != num1.rend();
            bool has_b = b != num2.rend();

            if (has_a || has_b)
            {
                auto advance = [](auto& it, bool valid) -> uint8_t
                {
                    if (valid)
                    {
                        char value = *it;
                        it = std::next(it);
                        return static_cast<uint8_t>(value - '0');
                    }

                    return 0;
                };

                carry += advance(a, has_a) + advance(b, has_b);
                r.push_back(static_cast<char>('0' + carry % 10));
                carry /= 10;
            }
            else
            {
                if (carry)
                {
                    r.push_back(static_cast<char>('0' + carry));
                }

                break;
            }
        }

        std::ranges::reverse(r);

        return r;
    }
};

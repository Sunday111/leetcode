#pragma once

class Solution
{
public:
    [[nodiscard]] static constexpr int sumDigits(int num)
    {
        int r = 0;
        while (num)
        {
            r += num % 10;
            num /= 10;
        }
        return r;
    }

    [[nodiscard]] static constexpr int addDigits(int num)
    {
        while (num > 9) num = sumDigits(num);
        return num;
    }
};

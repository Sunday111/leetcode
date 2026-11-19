#pragma once

#include "swap_if_greater.hpp"

class Solution
{
public:
    int countOperations(int num1, int num2)
    {
        int r = 0;
        while (num1 && num2)
        {
            swap_if_greater(num2, num1);
            int t = num1 / num2;
            r += t;
            num1 -= t * num2;
        }
        return r;
    }
};

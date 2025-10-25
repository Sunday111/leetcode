#pragma once

class Solution
{
public:
    int totalMoney(int n)
    {
        int w = n / 7, k = n % 7;
        return ((7 * w * (w + 7)) + (k * (2 * w + k + 1))) / 2;
    }
};

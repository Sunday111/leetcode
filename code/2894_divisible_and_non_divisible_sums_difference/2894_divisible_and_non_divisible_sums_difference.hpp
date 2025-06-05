#pragma once

class Solution
{
public:
    [[nodiscard]] static constexpr int differenceOfSums(int n, int m)
    {
        auto f = [](int v)
        {
            return v * (v + 1);
        };

        const int k = n / m;
        return f(n) / 2 - m * f(k);
    }
};

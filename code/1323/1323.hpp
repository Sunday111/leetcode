#pragma once

class Solution
{
public:
    [[nodiscard]] static constexpr int maximum69Number(int num) noexcept
    {
        int k = 1, mk = -1;
        for (int n = num; n; n /= 10, k *= 10) mk = (n % 10 == 6) ? k : mk;

        return num + mk * 3 * (mk >= 0);
    }
};

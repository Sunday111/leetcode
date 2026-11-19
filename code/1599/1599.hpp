#pragma once

#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr int minOperationsMaxProfit(
        const std::vector<int>& customers,
        const int boardingCost,
        const int runningCost) noexcept
    {
        const auto n = static_cast<u32>(customers.size());

        int balance = 0;
        int max_balance = 0;
        u32 max_balance_at = 0;

        int awaiting = 0;
        u32 i = 0;
        while (true)
        {
            if (i < n) awaiting += customers[i];

            if (balance > max_balance)
            {
                max_balance = balance;
                max_balance_at = i;
            }

            int to_board = std::min(4, awaiting);
            if (i >= customers.size() && to_board == 0)
            {
                break;
            }

            awaiting -= to_board;
            balance += to_board * boardingCost;
            balance -= runningCost;

            ++i;
        }

        if (max_balance < 1) return -1;
        return static_cast<int>(max_balance_at);
    }
};

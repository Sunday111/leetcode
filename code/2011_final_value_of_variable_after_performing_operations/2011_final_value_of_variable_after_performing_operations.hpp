#pragma once

#include <string>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int finalValueAfterOperations(
        const std::vector<std::string>& operations) noexcept
    {
        int x = 0;
        for (const auto& op : operations)
        {
            x += (op.find('+') == op.npos) ? -1 : 1;
        }

        return x;
    }
};

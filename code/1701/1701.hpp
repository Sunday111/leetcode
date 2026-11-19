#pragma once

#include <vector>

class Solution
{
public:
    using u64 = uint64_t;
    [[nodiscard]] static constexpr double averageWaitingTime(
        std::vector<std::vector<int>>& customers) noexcept
    {
        u64 total_waiting_time = 0, t = 0;
        for (auto& customer : customers)
        {
            const u64 arrival_time = static_cast<u64>(customer[0]);
            const u64 duration = static_cast<u64>(customer[1]);
            t = std::max(t, arrival_time) + duration;
            total_waiting_time += t - arrival_time;
        }

        return static_cast<double>(
            static_cast<long double>(total_waiting_time) / customers.size());
    }
};

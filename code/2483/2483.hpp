#include <algorithm>
#include <string_view>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr u32 bestClosingTime(
        std::string_view customers) noexcept
    {
        u32 fomo = static_cast<u32>(std::ranges::count(customers, 'Y'));
        u32 min_penalty = fomo, idle = 0, min_penalty_hour = 0xFFFFFFFF;
        for (u32 hour = 0; hour != customers.size(); ++hour)
        {
            bool y = customers[hour] == 'Y';
            fomo -= y;
            idle += !y;
            if (u32 penalty = fomo + idle; penalty < min_penalty)
            {
                min_penalty = penalty;
                min_penalty_hour = hour;
            }
        }
        return min_penalty_hour + 1;
    }
};

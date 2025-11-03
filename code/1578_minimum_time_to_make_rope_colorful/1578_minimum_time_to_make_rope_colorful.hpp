#include <string_view>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int minCost(
        std::string_view colors,
        const std::vector<int>& neededTime) noexcept
    {
        char curr_color = 0;
        int max_time = 0, sum_time = 0, r = 0;

        for (size_t i = 0; i != neededTime.size(); ++i)
        {
            char c = colors[i];
            bool b = c != std::exchange(curr_color, c);
            r += (!b - 1) & (sum_time - max_time);
            sum_time &= b - 1;
            max_time &= b - 1;

            int t = neededTime[i];
            max_time = std::max(max_time, t);
            sum_time += t;
        }

        return r + sum_time - max_time;
    }
};

#include <algorithm>
#include <ranges>
#include <vector>

class Solution
{
public:
    int earliestFinishTime(
        const std::vector<int>& landStartTime,
        const std::vector<int>& landDuration,
        const std::vector<int>& waterStartTime,
        const std::vector<int>& waterDuration) const noexcept
    {
        auto calc = [] [[gnu::always_inline]] (auto&& a, auto&& b) noexcept
        {
            int a_end = 1'000'000;
            for (auto [start, dur] : a)
            {
                a_end = std::min(a_end, start + dur);
            }
            int r = 1'000'000;
            for (auto [start, dur] : b)
            {
                r = std::min(r, std::max(a_end, start) + dur);
            }

            return r;
        };

        const auto land = std::views::zip(landStartTime, landDuration);
        const auto water = std::views::zip(waterStartTime, waterDuration);
        return std::min(calc(land, water), calc(water, land));
    }
};

#include <ranges>
#include <vector>


class Solution
{
public:
    constexpr int earliestFinishTime(
        const std::vector<int>& landStartTime,
        const std::vector<int>& landDuration,
        const std::vector<int>& waterStartTime,
        const std::vector<int>& waterDuration) noexcept
    {
        constexpr auto zip = std::views::zip;

        int r = 1'000'000'000;
        for (auto [ls, ld] : zip(landStartTime, landDuration))
        {
            for (auto [ws, wd] : zip(waterStartTime, waterDuration))
            {
                r = std::min(
                    r,
                    std::min(
                        std::max(ls + ld, ws) + wd,
                        std::max(ws + wd, ls) + ld));
            }
        }
        return r;
    }
};

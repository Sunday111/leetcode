#include <algorithm>
#include <vector>

class Solution
{
public:
    int maxTwoEvents(std::vector<std::vector<int>>& events)
    {
        std::ranges::sort(events, std::less{});

        static int max_after[100'001];
        max_after[events.size()] = events.back()[2];
        for (auto i = events.size(); i--;)
        {
            max_after[i] = std::max(events[i][2], max_after[i + 1]);
        }

        int r = max_after[0];
        for (auto a = events.begin(); a != events.end(); ++a)
        {
            int req_start_time = (*a)[1] + 1;

            auto b = std::ranges::lower_bound(
                a + 1,
                events.end(),
                req_start_time,
                std::less{},
                [](auto& e) { return e[0]; });

            if (b != events.end())
            {
                r = std::max(
                    r,
                    (*a)[2] + max_after[std::distance(events.begin(), b)]);
            }
        }

        return r;
    }
};

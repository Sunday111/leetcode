#include <algorithm>
#include <vector>

class Solution
{
public:
    int minimumEffort(std::vector<std::vector<int>>& tasks)
    {
        std::ranges::sort(
            tasks,
            std::greater{},
            [](const auto& t) { return t[1] - t[0]; });

        int r = 0, e = 0;
        for (const auto& t : tasks)
        {
            int add = std::max(t[1] - e, 0);
            r += add;
            e += add - t[0];
        }

        return r;
    }
};

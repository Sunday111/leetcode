#include <algorithm>
#include <vector>

class Solution
{
public:
    inline static unsigned kFact[]{1, 1, 2, 6, 24, 120, 720};
    auto permute(std::vector<int>& nums)
    {
        auto target = kFact[nums.size()];

        std::vector<std::vector<int>> r;
        r.reserve(target);
        r.emplace_back(std::move(nums));

        while (r.size() != target)
        {
            r.emplace_back(r.back());
            std::ranges::next_permutation(r.back());
        }

        return r;
    }
};

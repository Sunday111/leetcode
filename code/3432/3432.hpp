#include <numeric>
#include <vector>

class Solution
{
public:
    int countPartitions(const std::vector<int>& nums)
    {
        return (static_cast<int>(nums.size()) - 1) &
               -(!(std::accumulate(nums.begin(), nums.end(), 0) & 1));
    }
};

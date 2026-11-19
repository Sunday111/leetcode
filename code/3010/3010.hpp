#include <vector>

#include "swap_if_greater.hpp"

class Solution
{
public:
    int minimumCost(std::vector<int>& nums)
    {
        int a = nums[1], b = nums[2];

        swap_if_greater(a, b);

        for (size_t i = 3; i != nums.size(); ++i)
        {
            int x = nums[i];
            swap_if_greater(b, x);
            swap_if_greater(a, b);
        }

        return nums[0] + a + b;
    }
};

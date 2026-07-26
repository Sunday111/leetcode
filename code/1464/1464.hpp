#include <vector>

#include "swap_if_greater.hpp"

class Solution
{
public:
    int maxProduct(std::vector<int>& nums)
    {
        int a = 0, b = 0;
        for (int x : nums) swap_if_greater(b = std::max(b, x), a);
        return --a * --b;
    }
};

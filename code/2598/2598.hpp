
#include <vector>

#include "int_if.hpp"

int mod[100000];  // NOLINT
class Solution
{
public:
    static int findSmallestInteger(std::vector<int>& nums, int value) noexcept
    {
        const int n = static_cast<int>(nums.size());
        std::fill_n(mod, value, 0);
        for (int x : nums)
        {
            x %= value;
            x += iif(x < 0, value, 0);
            ++mod[x];
        }
        for (int i = 0; i != n; ++i)
        {
            if (!(mod[i % value]--))
            {
                return i;
            }
        }
        return n;
    }
};

#include "sync_stdio.hpp"

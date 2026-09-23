#include <print>
#include <utility>
#include <vector>


class Solution
{
public:
    int smallestIndex(const std::vector<int>& nums) const noexcept
    {
        for (size_t i = 0; i != nums.size(); ++i)
        {
            const int v = nums[i];
            [[assume(v >= 0)]];
            [[assume(v <= 1000)]];

            // digit sum
            int s = 0;
            for (int t = v; t; t /= 10)
            {
                s += t % 10;
            }

            std::println("digit sum for {} at index {} is {}", v, i, s);

            [[unlikely]] if (std::cmp_equal(s, i))
            {
                return static_cast<int>(i);
            }
        }
        return -1;
    }
};

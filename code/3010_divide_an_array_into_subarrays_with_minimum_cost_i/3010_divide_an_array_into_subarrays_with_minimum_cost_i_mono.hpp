#include <concepts>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

// Swaps a and b if a > b. Only for integers. Branchless
template <std::integral Int>
FORCE_INLINE static constexpr void swap_if_greater(Int& a, Int& b) noexcept
{
    Int mask = (a ^ b) & -Int{a > b};
    a ^= mask, b ^= mask;
}

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

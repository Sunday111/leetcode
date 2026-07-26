#include <algorithm>
#include <concepts>
#include <vector>






// Swaps a and b if condition is true. Only for integers. Branchless
inline static constexpr auto swap_if =
    []<std::integral Int> [[gnu::always_inline]] (
        bool condition,
        Int& a,
        Int& b) noexcept
{
    Int mask = static_cast<Int>(static_cast<Int>(a ^ b) & -Int{condition});
    a ^= mask, b ^= mask;
};

// Swaps a and b if a > b. Only for integers. Branchless
inline static constexpr auto swap_if_greater =
    []<std::integral Int> [[gnu::always_inline]] (Int & a, Int& b) noexcept
{
    swap_if(a > b, a, b);
};



// Swaps a and b if a < b. Only for integers. Branchless
inline static constexpr auto swap_if_lower =
    []<std::integral Int> [[gnu::always_inline]] (Int & a, Int& b) noexcept
{
    swap_if(a < b, a, b);
};

class Solution
{
public:
    int maximumProduct(const std::vector<int>& nums) noexcept
    {
        int hi[3]{-1000, -1000, -1000}, lo[2]{1000, 1000};

        for (int x : nums)
        {
            hi[0] = std::max(x, hi[0]);
            lo[1] = std::min(lo[1], x);
            swap_if_greater(hi[0], hi[1]);
            swap_if_greater(hi[1], hi[2]);
            swap_if_lower(lo[1], lo[0]);
        }

        return std::max(hi[0] * hi[1] * hi[2], hi[2] * lo[0] * lo[1]);
    }
};

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

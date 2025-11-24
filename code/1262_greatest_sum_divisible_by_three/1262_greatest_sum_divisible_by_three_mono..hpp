#include <array>
#include <concepts>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

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
    [[nodiscard]] static constexpr int maxSumDivThree(
        const std::vector<int>& nums) noexcept
    {
        int s = 0;

        constexpr auto mi = std::numeric_limits<int>::max();
        std::array<int, 2> m[3]{};
        int n[3]{0, 0, 0};
        m[1].fill(mi), m[2].fill(mi);

        for (int v : nums)
        {
            s += v;
            int mod = v % 3;
            ++n[mod];
            swap_if_greater(m[mod][0], v);
            swap_if_greater(m[mod][1], v);
        }

        int mod = s % 3, k = s & -!!mod;
        if (n[1] > 0 && mod == 1) k = std::min(k, m[1][0]);
        if (n[2] > 1 && mod == 1) k = std::min(k, m[2][0] + m[2][1]);
        if (n[1] > 1 && mod == 2) k = std::min(k, m[1][0] + m[1][1]);
        if (n[2] > 0 && mod == 2) k = std::min(k, m[2][0]);
        return s - k;
    }
};

#ifndef __clang__
auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
#endif

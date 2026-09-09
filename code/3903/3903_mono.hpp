#include <vector>


#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

class Solution
{
public:
    using u32 = uint32_t;
    inline static u32 x[100];

    auto firstStableIndex(std::vector<int>& nums, u32 k) noexcept
    {
        auto a = reinterpret_cast<const u32*>(nums.data());
        auto n = static_cast<u32>(nums.size());

        for (u32 lo = ~0u, i = n; i--;)
        {
            x[i] = lo = std::min<u32>(lo, a[i]);
        }

        for (u32 hi = 0, i = 0; i != n; ++i)
        {
            hi = std::max<u32>(hi, a[i]);
            [[unlikely]] if (hi <= k + x[i])
            {
                return static_cast<int>(i);
            }
        }

        return -1;
    }
};

#include <algorithm>
#include <limits>
#include <numeric>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    inline static u32 sorted[100'001];
    std::vector<int> arrayRankTransform(std::vector<int>& a) noexcept
    {
        const u32 n = static_cast<u32>(a.size());

        std::iota(sorted, sorted + n, 0u);
        std::ranges::sort(
            sorted,
            sorted + n,
            std::less{},
            [&] [[gnu::always_inline]] (u32 i) { return a[i]; });

        int pv = std::numeric_limits<int>::lowest();
        int rank = 0;

        for (u32 i = 0; i != n; ++i)
        {
            int& v = a[sorted[i]];
            rank += v > pv;
            pv = v;
            v = rank;
        }

        return std::move(a);
    }
};

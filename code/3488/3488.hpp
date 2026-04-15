#include <algorithm>
#include <vector>

#include "int_if.hpp"
#include "upd_min.hpp"

class Solution
{
public:
    using u32 = uint32_t;

    inline static constexpr u32 kMaxVal = 1'000'000;
    inline static constexpr u32 kMaxN = 100'000;

    static constexpr void impl(
        const std::vector<u32>& nums,
        std::vector<u32>& queries) noexcept
    {
        const auto n = cast<u32>(nums.size());
        [[assume(n <= kMaxN)]];

        constexpr u32 lim = 100'000;
        static u32 d[kMaxN + 1], p[kMaxVal + 1];

        [[maybe_unused]] static const auto _ = [&]
        {
            std::ranges::fill(p, lim);
            return ' ';
        }();

        for (u32 i = 0; i != n; ++i)
        {
            const auto v = nums[i];
            [[assume(v <= kMaxVal)]];
            auto& j = p[v];
            j = std::min(j, i);
            u32 x = iif(i == j, ~u32{}, i - j);
            d[i] = x;
            upd_min(d[j], x);
            j = i;
        }
        for (u32 i = 0; i != n; ++i)
        {
            const auto v = nums[i];
            [[assume(v <= kMaxVal)]];
            auto& j = p[v];
            u32 x = iif(j == lim, lim, n - j + i);
            upd_min(d[i], x);
            upd_min(d[j], x);
            j = lim;
        }

        for (auto& i : queries)
        {
            i = iif(d[i] == 0 || d[i] == n, ~u32{}, d[i]);
        }
    }
    std::vector<int> solveQueries(
        std::vector<int>& nums,
        std::vector<int>& queries)
    {
        impl(
            reinterpret_cast<std::vector<u32>&>(nums),
            reinterpret_cast<std::vector<u32>&>(queries));
        return std::move(queries);
    }
};

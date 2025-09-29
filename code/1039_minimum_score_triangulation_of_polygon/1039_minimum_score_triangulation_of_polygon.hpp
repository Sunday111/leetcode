#include <algorithm>
#include <array>
#include <span>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    static u32 minScoreTriangulation(const std::vector<int>& values) noexcept
    {
        static std::array<u32, (50 << 6) | 50> dp_array;
        const u32 n = static_cast<u32>(values.size());
        std::ranges::fill_n(dp_array.begin(), (n << 6) | n, 0);
        std::span<const u32> v{
            // NOLINTNEXTLINE
            reinterpret_cast<const u32*>(values.data()),
            n};

        auto dp = [&](u32 i, u32 j) -> u32&
        {
            return dp_array[(i << 6) | j];
        };

        u32 r{};
        for (u32 i = n - 2; i--;)
        {
            for (u32 j = i + 2; j < n; j++)
            {
                u32 k = i + 1;
                r = v[i] * v[j] * v[k] + dp(k, j);
                while (++k < j)
                {
                    u32 s2 = dp(i, k) + v[i] * v[j] * v[k] + dp(k, j);
                    r = std::min(r, s2);
                }
                dp(i, j) = r;
            }
        }
        return r;
    }
};

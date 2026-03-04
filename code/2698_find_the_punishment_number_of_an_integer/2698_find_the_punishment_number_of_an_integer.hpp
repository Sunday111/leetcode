#include <array>

class Solution
{
public:
    using u32 = uint32_t;

    [[nodiscard]] constexpr u32 punishmentNumber(u32 n) noexcept
    {
        constexpr auto kArr = []
        {
            std::array<u32, 1001> a;  // NOLINT
            a[0] = 0;
            for (u32 i = 1, s = 0; i != a.size(); ++i)
            {
                u32 sq = i * i;
                const bool is_valid = [](this auto&& dfs, u32 x, u32 t) -> bool
                {
                    if (x == t) return true;

                    u32 r = 0, m = 1;
                    while (x > 9 && r < t)
                    {
                        r += (x % 10) * m;
                        x /= 10, m *= 10;
                        if (dfs(x, t - r)) return true;
                    }

                    return false;
                }(sq, i);

                if (is_valid) s += sq;
                a[i] = s;
            }
            return a;
        }();

        return kArr[n];
    }
};

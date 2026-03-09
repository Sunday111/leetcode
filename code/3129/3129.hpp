#include <vector>

#include "bump_allocator.hpp"
#include "bump_vector.hpp"
#include "integral_aliases.hpp"
#include "signed_integral_aliases.hpp"

class Solution
{
    static constexpr i64 MOD = 1'000'000'007;

public:
    using SolutionStorage = GlobalBufferStorage<1 << 25>;
    template <typename T>
    using Vec = BumpVector<T, SolutionStorage>;

    i32 numberOfStableArrays(u16 zero, u16 one, u16 limit)
    {
        auto arena = SolutionStorage::Instance().StartArena();
        u16 z1 = zero + 1, o1 = one + 1, l1 = limit + 1;

        Vec<Vec<std::array<i32, 2>>> dp;
        dp.resize(z1);
        for (auto& e : dp) e.resize(one + 1);
        for (u16 i = std::min(z1, l1); i--;) dp[i][0][0] = 1;
        for (u16 j = std::min(o1, l1); j--;) dp[0][j][1] = 1;
        for (u16 i = 1; i != z1; ++i)
        {
            for (u16 j = 1; j != o1; ++j)
            {
                u16 j1 = j - 1, i1 = i - 1;
                i32 bi = i >= l1, bj = j >= l1;
                u16 loi = std::min<u16>(i1 - limit, i1);
                u16 loj = std::min<u16>(j1 - limit, j1);
                dp[i][j][0] = static_cast<int>(
                    (dp[i1][j][0] + dp[i1][j][1] - (dp[loi][j][1] & -bi) +
                     MOD) %
                    MOD);
                dp[i][j][1] = static_cast<int>(
                    (dp[i][j1][0] + dp[i][j1][1] - (dp[i][loj][0] & -bj) +
                     MOD) %
                    MOD);
            }
        }
        return static_cast<int>((dp[zero][one][0] + dp[zero][one][1]) % MOD);
    }
};

#include <vector>

#include "bump_allocator.hpp"
#include "bump_vector.hpp"
#include "integral_aliases.hpp"
#include "signed_integral_aliases.hpp"

class Solution
{
    static constexpr i64 MOD = 1'000'000'007;

public:
    using SolutionStorage = GlobalBufferStorage<1 << 20>;
    template <typename T>
    using Vec = BumpVector<T, SolutionStorage>;

    i32 numberOfStableArrays(u16 zero, u16 one, u16 limit)
    {
        auto arena = SolutionStorage::Instance().StartArena();

        Vec<Vec<std::array<i32, 2>>> dp;
        dp.resize(zero + 1);
        for (auto& e : dp) e.resize(one + 1);

        for (u16 i = std::min(zero, limit) + 1; i--;)
        {
            dp[i][0][0] = 1;
        }

        for (u16 j = std::min(one, limit) + 1; j--;)
        {
            dp[0][j][1] = 1;
        }

        for (u16 i = 1; i <= zero; ++i)
        {
            for (u16 j = 1; j <= one; ++j)
            {
                bool bi = i >= limit + 1;
                bool bj = j >= limit + 1;
                u16 loi = std::min<u16>(i - 1 - limit, zero);
                u16 loj = std::min<u16>(j - 1 - limit, one);
                dp[i][j][0] = static_cast<int>(
                    (dp[i - 1][j][0] + dp[i - 1][j][1] -
                     (dp[loi][j][1] & -i32{bi}) + MOD) %
                    MOD);
                dp[i][j][1] = static_cast<int>(
                    (dp[i][j - 1][0] + dp[i][j - 1][1] -
                     (dp[i][loj][0] & -i32{bj}) + MOD) %
                    MOD);
            }
        }
        return static_cast<int>((dp[zero][one][0] + dp[zero][one][1]) % MOD);
    }
};

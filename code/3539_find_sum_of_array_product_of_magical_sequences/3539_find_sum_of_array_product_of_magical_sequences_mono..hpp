#include <array>
#include <bit>
#include <cstdint>
#include <span>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

#define NO_SANITIZERS \
    __attribute__((no_sanitize("undefined", "address", "coverage", "thread")))
#ifndef __clang__
#define SYNC_STDIO                   \
    auto init = []()                 \
    {                                \
        ios::sync_with_stdio(false); \
        cin.tie(nullptr);            \
        cout.tie(nullptr);           \
        return 'c';                  \
    }();
#else
#define SYNC_STDIO
#endif

template <typename To>
[[nodiscard]] constexpr To to(auto v) noexcept
{
    return static_cast<To>(v);
}

class Solution
{
    static constexpr u32 kMOD = 1'000'000'007;
    inline static u32 dp[32][32][64][32];  // NOLINT
    u32 i = 0, k = 0, m = 0;
    std::span<const int> nums;

    inline static constexpr auto C = []()
    {
        std::array<std::array<u32, 32>, 32> C{};
        for (u32 i = 1; i != 31; i++)
        {
            C[i][0] = C[i][i] = 1;
            for (u32 j = 1; j <= i / 2; j++)
            {
                const u32 Cij = C[i - 1][j - 1] + C[i - 1][j];
                C[i][j] = C[i][i - j] = Cij;
            }
        }

        return C;
    }();

    u32 dfs(u32 flag) noexcept NO_SANITIZERS
    {
        const u32 bz = to<u32>(std::popcount(flag));
        if (k == 0xFFFFFFFF || m + bz < k) return 0;
        if (m == 0) return (k == bz) ? 1 : 0;
        if (i >= nums.size()) return 0;

        if (dp[m][k][i][flag] != 0xFFFFFFFF) return dp[m][k][i][flag];

        u64 r = 0, p = 1;
        const u32 x = to<u32>(nums[i++]);
        for (u32 f = 0; f <= m; ++f)
        {
            u64 perm = C[m][f] * p % kMOD;
            const u32 newFlag = flag + f;
            bool bitSet = newFlag & 1;
            k -= bitSet, m -= f;
            r += perm * dfs(newFlag >> 1);
            k += bitSet, m += f;
            p *= x, p %= kMOD;
        }
        return dp[m][k][--i][flag] = r % kMOD;
    }

    static void clearDP(u32 m, u32 n) noexcept NO_SANITIZERS
    {
        for (u32 i = 0; i <= m; ++i)
        {
            for (u32 j = 0; j <= m; ++j)
            {
                for (u32 s = 0; s != n; ++s)
                {
                    std::fill_n(std::begin(dp[i][j][s]), m + 1, 0xFFFFFFFF);
                }
            }
        }
    }

public:
    u32 magicalSum(u32 m_, u32 k_, const std::vector<int>& nums_) noexcept
        NO_SANITIZERS
    {
        i = 0, k = k_, m = m_, nums = nums_;
        clearDP(m, to<u32>(nums.size()));
        auto r = dfs(0);
        return r;
    }
};

SYNC_STDIO

#include <array>
#include <vector>

#ifdef __GNUC__
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#define FORCE_INLINE inline
#endif

#ifdef __GNUC__
#define HOT_PATH __attribute__((hot))
#else
#define FORCE_INLINE inline
#endif

// This is a reformatted version of.
// https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/solutions/7007108/dynamic-programming-with-o-n-time-c-4-ms-beating-100-of-fair-submissions
class Solution
{
private:
    using u64 = uint64_t;
    using u32 = uint32_t;

    FORCE_INLINE HOT_PATH static constexpr void
    ins(const u32 v, u32& a, u32& b) noexcept
    {
        // inserting v into descending-sorted list [a, b] excluding the bottom
        const u32 in = static_cast<u32>(-(v > b));
        const u32 top = static_cast<u32>(-(v > a));
        const u32 mid = in & ~top;
        b = (a & top) + (v & mid) + (b & ~in);
        a = (v & top) + (a & ~top);
    }

    template <std::integral T>
    FORCE_INLINE HOT_PATH static constexpr void swap_if_greater(
        T& a,
        T& b) noexcept
    {
        T cond = (a > b) ? ~T{0} : 0;
        T mask = (a ^ b) & cond;
        a ^= mask, b ^= mask;
    }

public:
    [[nodiscard]] FORCE_INLINE static u64 maxSubarrays(
        const u32 n,
        const std::vector<std::vector<int>>& conflictingPairs) noexcept
    {
        static std::array<u32, 200'000> leftconf;
        static std::array<u64, 100'000> inc;
        for (const auto& p : conflictingPairs)
        {
            u32 p0 = static_cast<u32>(p[0]), p1 = static_cast<u32>(p[1]);
            swap_if_greater(p0, p1);
            u32 idx = (p1 - 1) * 2;
            ins(p0, leftconf[idx], leftconf[idx + 1]);
        }

        u64 res = 0, maxi = 0;
        u32 lf = 0, ls = 0;
        for (u32 r = 0; r != n; ++r)
        {
            u32 idx = r * 2;
            ins(leftconf[idx], lf, ls);
            ins(leftconf[idx + 1], lf, ls);
            res += (r + 1) - lf;
            u64 i = inc[lf] += lf - ls;
            swap_if_greater(i, maxi);
        }

        std::fill_n(inc.begin(), n, 0);
        std::fill_n(leftconf.begin(), n * 2, 0);

        return res + maxi;
    }
};

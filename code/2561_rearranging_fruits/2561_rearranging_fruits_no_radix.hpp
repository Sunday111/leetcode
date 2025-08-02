#include <algorithm>
#include <array>
#include <optional>
#include <span>
#include <vector>

using u32 = uint32_t;
using u64 = uint64_t;
using i32 = int32_t;
using i64 = int64_t;

#define FORCE_INLINE inline __attribute__((always_inline))

class Solution
{
    template <typename To, typename From, typename Allocator>
        requires(sizeof(To) == sizeof(From))
    [[nodiscard]] FORCE_INLINE static std::span<To> reinterpret_range(
        std::vector<From, Allocator>& v) noexcept
    {
        return std::span<To>{
            reinterpret_cast<To*>(v.data()),  // NOLINT
            v.size()};
    }

    [[nodiscard]] static std::optional<u64> minCost(
        std::span<u32> basket1,
        std::span<u32> basket2) noexcept
    {
        std::ranges::sort(basket1);
        std::ranges::sort(basket2);

        const u32 n = static_cast<u32>(basket1.size());
        const u32 min_fruit_cost =
            std::min(basket1.front(), basket2.front()) * 2;

        u32 num_unique = 0, to_swap = 0;

        // n in range [1; 10^5] and both arrays can potentially have
        // all unique values. So length of 2*10^5 + 1 is required
        static std::array<std::pair<u32, u32>, 200'001> freq;

        {
            u32 i = 0, j = 0;
            while (i != n || j != n)
            {
                u32 vi = i == n ? ~u32{0} : basket1[i];
                u32 vj = j == n ? ~u32{0} : basket2[j];
                u32 ni = 0, nj = 0;

                if (vi <= vj)
                {
                    while (i != n && basket1[i] == vi) ++ni, ++i;
                }

                if (vj <= vi)
                {
                    while (j != n && basket2[j] == vj) ++nj, ++j;
                }

                u32 diff = std::max(ni, nj) - std::min(ni, nj);
                if (diff & 1) return std::nullopt;
                diff /= 2;
                freq[num_unique++] = {std::min(vi, vj), diff};
                to_swap += diff;
            }

            to_swap /= 2;
        }

        u64 total_swap_cost = 0;

        for (auto [cost, cnt] : std::span{freq}.first(num_unique))
        {
            u64 c = std::min(min_fruit_cost, cost);
            if (cnt < to_swap)
            {
                total_swap_cost += u64{cnt} * c;
                to_swap -= cnt;
            }
            else
            {
                total_swap_cost += u64{to_swap} * c;
                break;
            }
        }

        return total_swap_cost;
    }

public:
    [[nodiscard]] static i64 minCost(
        std::vector<i32>& basket1,
        std::vector<i32>& basket2) noexcept
    {
        if (auto r = minCost(
                reinterpret_range<u32>(basket1),
                reinterpret_range<u32>(basket2)))
        {
            return static_cast<i64>(*r);
        }
        return -1;
    }
};

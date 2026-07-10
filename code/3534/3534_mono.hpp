#include <algorithm>
#include <bit>
#include <concepts>
#include <cstdint>
#include <ranges>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;


// Swaps a and b if condition is true. Only for integers. Branchless
inline static constexpr auto swap_if =
    []<std::integral Int> [[gnu::always_inline]] (
        bool condition,
        Int& a,
        Int& b) noexcept
{
    Int mask = static_cast<Int>(static_cast<Int>(a ^ b) & -Int{condition});
    a ^= mask, b ^= mask;
};

namespace stdr = std::ranges;
namespace stdv = std::views;

class Solution
{
public:
    // nums indices sorted by nums value
    inline static u32 sorted[100'001];

    // order[i] -> index of nums ith element in sorted
    inline static u32 order[100'001];

    template <typename T>
    [[nodiscard, gnu::always_inline]] constexpr static auto deref_array(
        T* arr) noexcept
    {
        return [arr] [[gnu::always_inline]] (u32 i) noexcept
        {
            return arr[i];
        };
    };

    // up[k][i] -> index reachable from i after 2^k greedy jumps
    // here i index in sorted array, so value of i would be nums[sorted[i]]
    inline static u32 up[18][100'000];

    static void impl(
        const u32 n,
        const u32 md,
        const std::vector<u32>& nums,
        const std::vector<std::vector<u32>>& queries,
        std::vector<u32>& result) noexcept
    {
        const u32 nq = static_cast<u32>(queries.size());
        const auto deref_nums = deref_array(nums.data());

        stdr::copy(stdv::iota(0u, n), sorted);
        stdr::sort(sorted, sorted + n, std::less{}, deref_nums);
        for (u32 i = 0; i != n; ++i) order[sorted[i]] = i;

        // build binary uplifting table starting with one greedy jump
        {
            u32 i = 0;
            for (u32 j = 0; j != n; ++j)
            {
                u32 vi = nums[sorted[i]];
                u32 vj = nums[sorted[j]];
                while (vj - vi > md)
                {
                    up[0][i] = j - 1;
                    ++i;
                    vi = nums[sorted[i]];
                }
            }
            while (i != n)
            {
                up[0][i++] = n - 1;
            }
        }

        u32 lim_k = static_cast<u32>(std::bit_width(n));
        for (u32 k = 1; k != lim_k; ++k)
        {
            for (u32 i = 0; i != n; ++i)
            {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }

        result.resize(nq);
        for (u32 qi = 0; qi != nq; ++qi)
        {
            auto& q = queries[qi];
            u32 i = order[q[0]], j = order[q[1]];

            if (i == j)
            {
                result[qi] = 0;
                continue;
            }

            swap_if(i > j, i, j);

            if (up[lim_k - 1][up[lim_k - 1][i]] < j)
            {
                result[qi] = ~u32{};
                continue;
            }

            u32 curr = i, steps = 0;
            for (u32 k = lim_k; k--;)
            {
                u32 next = up[k][curr];
                if (next < j)
                {
                    curr = next;
                    steps += 1u << k;
                }
            }

            result[qi] = steps + 1;
        }
    }

    [[nodiscard, gnu::always_inline]] auto pathExistenceQueries(
        int n,
        std::vector<int>& nums,
        int maxDiff,
        std::vector<std::vector<int>>& in_queries) noexcept
    {
        std::vector<int> result;
        impl(
            static_cast<u32>(n),
            static_cast<u32>(maxDiff),
            reinterpret_cast<const std::vector<u32>&>(nums),
            reinterpret_cast<const std::vector<std::vector<u32>>&>(in_queries),
            reinterpret_cast<std::vector<u32>&>(result));
        return result;
    }
};

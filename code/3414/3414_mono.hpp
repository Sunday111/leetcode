#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <functional>
#include <numeric>
#include <ranges>
#include <type_traits>
#include <vector>




inline static constexpr auto iif =
    []<std::integral T> [[nodiscard, gnu::always_inline]] (
        bool c,
        T a,
        std::type_identity_t<T> b) noexcept -> T
{
    return b ^ ((a ^ b) & static_cast<T>(-c));
};


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;



template <u8 bits_per_pass, u32 capacity = 100'001, std::unsigned_integral I, typename Proj>
void radix_sort_by(I* indices, u32 n, Proj proj) noexcept
{
    using Key = std::remove_cvref_t<std::invoke_result_t<Proj&, I>>;
    static_assert(std::unsigned_integral<Key>);
    static_assert(bits_per_pass > 0 && bits_per_pass <= 16);

    constexpr u32 radix = 1u << bits_per_pass;
    constexpr Key mask = radix - 1;
    constexpr u32 passes = (sizeof(Key) * 8 + bits_per_pass - 1) / bits_per_pass;

    static std::array<I, capacity> scratch;
    std::array<u32, radix> counts{};
    assert(n <= capacity);

    for (u32 pass = 0; pass < passes; ++pass)
    {
        counts.fill(0);
        const u32 shift = pass * bits_per_pass;
        for (u32 pos = 0; pos < n; ++pos)
            ++counts[(std::invoke(proj, indices[pos]) >> shift) & mask];

        std::inclusive_scan(counts.begin(), counts.end(), counts.begin());
        for (u32 pos = n; pos--;)
        {
            const I index = indices[pos];
            const Key digit = (std::invoke(proj, index) >> shift) & mask;
            scratch[--counts[digit]] = index;
        }
        std::copy_n(scratch.data(), n, indices);
    }
}




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

// Swaps a and b if a > b. Only for integers. Branchless
inline static constexpr auto swap_if_greater =
    []<std::integral Int> [[gnu::always_inline]] (Int & a, Int& b) noexcept
{
    swap_if(a > b, a, b);
};
#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

struct Interval
{
    u32 l{};
    u32 r{};
    u32 w{};
};

struct Cell
{
    std::array<u32, 4> sums{};
    std::array<u16, 10> indices{};

    static constexpr std::array<u8, 5> offsets{0, 0, 1, 3, 6};
    static constexpr std::array<u64, 5> masks{
        0,
        0xFFFF'0000'0000'0000,
        0xFFFF'FFFF'0000'0000,
        0xFFFF'FFFF'FFFF'0000,
        0xFFFF'FFFF'FFFF'FFFF};

    [[gnu::always_inline]] u16* indices_for(u32 count) noexcept
    {
        return indices.data() + offsets[count];
    }

    [[gnu::always_inline]] const u16* indices_for(u32 count) const noexcept
    {
        return indices.data() + offsets[count];
    }

    [[gnu::target("avx2,bmi2")]] [[gnu::always_inline]] u64 lex_key(
        u32 count) const noexcept
    {
        const u16* p = indices.data() + offsets[count];
        const u64 key = (u64{p[0]} << 48) | (u64{p[1]} << 32) |
                        (u64{p[2]} << 16) | u64{p[3]};
        return key & masks[count];
    }

    [[gnu::target("avx2,bmi2")]] [[gnu::always_inline]] bool
    better_than(const Cell& rhs, u32 count, u32 rhs_count) const noexcept
    {
        const u32 sum = sums[count - 1];
        const u32 rhs_sum =
            iif(rhs_count, rhs.sums[(rhs_count - 1) & 3], u32{});
        return sum > rhs_sum ||
               (sum == rhs_sum && lex_key(count) < rhs.lex_key(rhs_count));
    }
};

class Solution
{
public:
    inline static u16 sorted[100'000];
    inline static Interval intervals[100'000];
    inline static Cell dp[100'001];

    [[gnu::target("avx2,bmi2")]]
    std::vector<int> maximumWeight(
        const std::vector<std::vector<int>>& g) const noexcept
    {
        const u16 n = g.size() & 0xFFFF;
        std::ranges::copy(
            reinterpret_cast<const std::vector<std::vector<u32>>&>(g) |
                std::views::transform(
                    [](const auto& x)
                    { return Interval{.l = x[0], .r = x[1], .w = x[2]}; }),
            intervals);

        std::ranges::copy(std::views::iota(u16{}, n), sorted);
        radix_sort_by<8>(
            sorted,
            n,
            [](u16 index) { return intervals[index].r; });

        for (u32 pos = 0; pos < n; ++pos)
        {
            const u16 i = sorted[pos];
            auto& x = intervals[i];
            const auto compatible = std::ranges::lower_bound(
                sorted,
                sorted + pos,
                x.l,
                std::less{},
                [](u16 index) { return intervals[index].r; });
            const auto prefix = static_cast<u32>(compatible - sorted);

            dp[pos + 1] = dp[pos];
            for (u32 count = 1; count <= 4; ++count)
            {
                const auto& previous = dp[prefix];
                if (count > 1 && previous.sums[count - 2] == 0) continue;

                Cell candidate{};
                u16* candidate_indices = candidate.indices_for(count);
                if (count > 1)
                {
                    std::copy_n(
                        previous.indices_for(count - 1),
                        count - 1,
                        candidate_indices);
                }
                candidate_indices[count - 1] = i;
                candidate.sums[count - 1] =
                    (count == 1 ? 0 : previous.sums[count - 2]) + x.w;
                for (u32 j = count - 1; j; --j)
                {
                    swap_if_greater(
                        candidate_indices[j - 1],
                        candidate_indices[j]);
                }

                auto& current = dp[pos + 1];
                if (candidate.better_than(current, count, count))
                {
                    current.sums[count - 1] = candidate.sums[count - 1];
                    std::copy_n(
                        candidate_indices,
                        count,
                        current.indices_for(count));
                }
            }
        }

        const auto& final = dp[n];
        u32 best_count = 0;
        for (u32 count = 1; count <= 4; ++count)
        {
            if (final.better_than(final, count, best_count))
            {
                best_count = count;
            }
        }

        std::vector<int> result(best_count);
        for (u32 i = 0; i != best_count; ++i)
        {
            result[i] = static_cast<int>(final.indices_for(best_count)[i]);
        }

        return result;
    }
};

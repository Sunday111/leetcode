#include <algorithm>
#include <cstdint>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif
// Specialised for suffix distinct counts, not arbitrary range additions.
// Weighted buckets store sums of selected indices; for max_n <= 100000,
// each is at most 2,684,338,176. Prefix totals still require u64.
template <u32 max_n>
class BIT
{
    static_assert(max_n <= 100'000);

public:
    explicit BIT(u32 size) : n(size)
    {
        std::fill_n(diff, n + 1, u32{0});
        std::fill_n(weighted_diff, n + 1, u32{0});
    }

    [[gnu::no_sanitize_address, gnu::target("bmi")]]
    // Call once per successive r, with l = previous_position + 1 (or zero).
    void update(u32 l, u32 r)
    {
        add(l, u32{1}, -l);
        add(r + 1, -u32{1}, r + 1);
        total_sum += r - l + 1;
    }

    [[gnu::no_sanitize_address, gnu::target("bmi")]]
    u64 query(u32 l, u32 r) const
    {
        return prefix_sum(r + 1) - prefix_sum(l);
    }

    [[gnu::no_sanitize_address, gnu::target("bmi")]]
    u64 suffix_sum(u32 l) const
    {
        return total_sum - prefix_sum(l);
    }

private:
    inline static u32 diff[max_n + 1]{};
    inline static u32 weighted_diff[max_n + 1]{};
    u32 n;
    u64 total_sum = 0;

    [[gnu::no_sanitize_address, gnu::target("bmi")]]
    void add(u32 index, u32 delta, u32 weighted_delta)
    {
        for (++index; index <= n; index += index & -index)
        {
            diff[index] += delta;
            weighted_diff[index] += weighted_delta;
        }
    }

    [[gnu::no_sanitize_address, gnu::target("bmi")]]
    u64 prefix_sum(u32 count) const
    {
        u32 sum = 0;
        u64 weighted_sum = 0;
        for (u32 index = count; index != 0; index -= index & -index)
        {
            sum += diff[index];
            weighted_sum += weighted_diff[index];
        }
        return u64{sum} * count + weighted_sum;
    }
};

class Solution
{
    static constexpr u32 max_n = 100'000;
    static constexpr u32 max_value = 100'000;
    static constexpr u32 mod = 1'000'000'007;
    inline static u32 last[max_value + 1]{};

public:
    // Keep initialisation instrumented so zero-fills lower to memset.
    u32 sumCounts(std::vector<int>& input)
    {
        auto nums = reinterpret_cast<const u32*>(input.data());
        u32 n = static_cast<u32>(input.size());
        BIT<max_n> bit(n);
        std::fill_n(last, max_value + 1, u32{0});

        return calculate(nums, n, bit);
    }

private:
    [[gnu::no_sanitize_address, gnu::target("bmi")]]
    static u32 calculate(const u32* nums, u32 n, BIT<max_n>& bit)
    {
        // At n = 100000, the exact answer is at most
        // 8,333,666,670,833,350,000, so only the final modulo is needed.
        u64 ans = 0;
        u64 ending_sum = 0;
        for (u32 r = 0; r < n; ++r)
        {
            u32 l = last[nums[r]];
            ending_sum += 2 * bit.suffix_sum(l) + r - l + 1;
            ans += ending_sum;
            bit.update(l, r);
            last[nums[r]] = r + 1;
        }
        return ans % mod;
    }
};

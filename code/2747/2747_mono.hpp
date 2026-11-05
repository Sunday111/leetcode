#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <cstring>
#include <type_traits>
#include <utility>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

template <u64 value>
using UintForValue = std::conditional_t < value < (1 << 8),
      u8,
      std::conditional_t <
          value<
              (1 << 16),
              u16,
              std::conditional_t<value<(1UL << 32), u32, u64>>>;

struct RadixSortIndicesByStorage
{
    template <std::unsigned_integral I, u32 capacity>
    inline static I scratch[capacity];

    alignas(u32) inline static u8 counts[sizeof(u32) << 16];
};

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    u32 capacity = 100'001,
    std::unsigned_integral I,
    typename Proj>
[[gnu::no_sanitize_address, gnu::flatten]] void
radix_sort_indices_by(I* indices, u32 n, Proj proj) noexcept
{
    using Key = std::remove_cvref_t<std::invoke_result_t<Proj&, I>>;
    using Count = UintForValue<capacity>;
    static_assert(std::unsigned_integral<Key>);
    static_assert(bits_per_pass > 0 && bits_per_pass <= 16);

    constexpr u32 radix = 1u << bits_per_pass;
    constexpr Key mask = radix - 1;
    constexpr u32 max_passes =
        (sizeof(Key) * 8 + bits_per_pass - 1) / bits_per_pass;
    constexpr u32 passes = num_passes == 0xFFFFFFFF ? max_passes : num_passes;
    static_assert(passes <= max_passes);

    auto* counts = reinterpret_cast<Count*>(RadixSortIndicesByStorage::counts);
    assert(n <= capacity);  // NOLINT
    I* src = indices;
    I* dst = RadixSortIndicesByStorage::scratch<I, capacity>;

    for (u32 pass = 0; pass < passes; ++pass)
    {
        std::memset(counts, 0, radix * sizeof(Count));
        const u32 shift = pass * bits_per_pass;
        for (u32 pos = 0; pos < n; ++pos)
        {
            ++counts[(proj(src[pos]) >> shift) & mask];
        }

        for (u32 i = 1; i < radix; ++i)
        {
            counts[i] += counts[i - 1];
        }
        for (u32 pos = n; pos--;)
        {
            const I index = src[pos];
            const Key digit = (proj(index) >> shift) & mask;
            dst[--counts[digit]] = index;
        }
        std::swap(src, dst);
    }
    if (passes % 2 && n)
    {
        std::memcpy(indices, src, n * sizeof(I));
    }
}
#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

class Solution
{
public:
    inline static constexpr u32 kCapacity = 100'000;
    inline static constexpr u32 kIndexBits = 17;
    inline static constexpr u32 kIndexMask = (1u << kIndexBits) - 1;
    inline static auto& srv_cnt =
        RadixSortIndicesByStorage::scratch<u32, kCapacity + 1>;
    inline static u64 sorted_logs[kCapacity];
    inline static u32 sorted_q[kCapacity];

    [[nodiscard, gnu::no_sanitize_address, gnu::flatten]]
    std::vector<int> countServers(
        u32 n,
        std::vector<std::vector<int>>& logs,
        u32 x,
        std::vector<int>& q)
    {
        const u32 nl = logs.size() & ~u32{};
        const u32 nq = q.size() & ~u32{};
        const auto* log_rows = logs.data();
        const auto* query_data = reinterpret_cast<const u32*>(q.data());
        u32 log_bits = 0, query_bits = 0;
        for (u32 i = 0; i != nl; ++i)
        {
            const auto* log = reinterpret_cast<const u32*>(log_rows[i].data());
            sorted_logs[i] = (u64{log[1]} << kIndexBits) | log[0];
            log_bits |= log[1];
        }
        for (u32 i = 0; i != nq; ++i)
        {
            sorted_q[i] = i;
            query_bits |= query_data[i];
        }
        const auto sort = [] [[gnu::always_inline]] (
                              auto* values,
                              u32 size,
                              u32 used_bits,
                              auto key)
        {
            if (size <= 64)
            {
                std::sort(
                    values,
                    values + size,
                    [key] [[gnu::always_inline]] (auto a, auto b)
                    { return key(a) < key(b); });
            }
            else if (used_bits < (1u << 10))
            {
                radix_sort_indices_by<10, 1, kCapacity + 1>(values, size, key);
            }
            else
            {
                radix_sort_indices_by<10, 2, kCapacity + 1>(values, size, key);
            }
        };
        sort(
            sorted_logs,
            nl,
            log_bits,
            [](u64 log) { return static_cast<u32>(log >> kIndexBits); });
        sort(
            sorted_q,
            nq,
            query_bits,
            [query_data](u32 i) { return query_data[i]; });

        std::vector<int> ans = std::move(q);
        auto* ans_data = reinterpret_cast<u32*>(ans.data());
        std::memset(srv_cnt, 0, sizeof(srv_cnt[0]) * (n + 1));
        u32 b = 0, e = 0, cnt = 0;
        u32 i = 0;
        for (; i != nq && b != nl; ++i)
        {
            const u32 qi = sorted_q[i];
            const u32 hi = query_data[qi];
            const u32 lo = hi - x;
            while (e != nl && (sorted_logs[e] >> kIndexBits) <= hi)
            {
                const u32 srv = sorted_logs[e++] & kIndexMask;
                cnt += srv_cnt[srv]++ == 0;
            }
            while (b != e && (sorted_logs[b] >> kIndexBits) < lo)
            {
                const u32 srv = sorted_logs[b++] & kIndexMask;
                cnt -= 0 == --srv_cnt[srv];
            }
            ans_data[qi] = n - cnt;
        }
        for (; i != nq; ++i) ans_data[sorted_q[i]] = n;
        return ans;
    }
};

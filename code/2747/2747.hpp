#include <algorithm>
#include <cstring>
#include <utility>
#include <vector>

#include "radix_sort_indices_by.hpp"
#include "sync_stdio.hpp"

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

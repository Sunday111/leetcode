#include <algorithm>
#include <array>
#include <ranges>
#include <set>
#include <vector>

#include "bump_allocator.hpp"
#include "radix_sorter.hpp"

template <typename To>
[[nodiscard]] FORCE_INLINE static constexpr To to(auto v) noexcept
{
    return static_cast<To>(v);
}

struct NoPrefixSumCheck
{
    FORCE_INLINE constexpr static void InitPrefixSumCheck(auto&&...) {}
    [[nodiscard]] FORCE_INLINE static constexpr bool CheckPrefixSum(
        auto&&...) noexcept
    {
        return true;
    }
};

struct PrefixSumCheck
{
    FORCE_INLINE static void InitPrefixSumCheck(
        std::vector<int>& tasks,
        std::vector<int>& workers) noexcept
    {
        std::ranges::copy(tasks, ts.begin());
        std::partial_sum(
            ts.begin(),
            ts.begin() + tasks.size(),  // NOLINT
            ts.begin());
        std::ranges::copy(workers, ws.begin());
        std::partial_sum(
            ws.begin(),
            ws.begin() + workers.size(),  // NOLINT
            ws.begin());
    }

    [[nodiscard]] FORCE_INLINE static constexpr bool CheckPrefixSum(
        u32 num_tasks,
        u32 num_workers,
        u32 pills,
        int strength) noexcept
    {
        u64 req = 0;
        if (num_tasks > 0) req = ts[num_tasks - 1];

        u32 w0 = num_workers - num_tasks;
        u64 available =
            ws[num_workers - 1] +
            cast<u64>(std::min(pills, num_workers)) * cast<u64>(strength);
        if (w0 > 0) available -= ws[w0 - 1];

        return req <= available;
    }
    inline static std::array<u64, 50'001> ws, ts;
};

constexpr bool WithPrefixSumCheck = true;

static constexpr u32 kStorageSize = 1 << 20;
using SolutionStorage = GlobalBufferStorage<kStorageSize>;

class Solution
    : public std::
          conditional_t<WithPrefixSumCheck, PrefixSumCheck, NoPrefixSumCheck>
{
public:
    static int maxTaskAssign(
        std::vector<int>& tasks,
        std::vector<int>& workers,
        const u32 pills,
        const int strength) noexcept
    {
        radix_sort<u32, SortOrder::Ascending, 8, 4>(
            reinterpret_range<u32>(tasks));
        radix_sort<u32, SortOrder::Ascending, 8, 4>(
            reinterpret_range<u32>(workers));

        InitPrefixSumCheck(tasks, workers);

        const u32 num_workers = cast<u32>(workers.size());

        auto canComplete = [&](const u32 num_tasks)
        {
            u32 p = 0;

            u32 ti = num_tasks - 1;
            const u32 t_end = 0xFFFFFFFF;
            if (num_tasks <= num_workers &&
                CheckPrefixSum(num_tasks, num_workers, pills, strength))
            {
                SolutionStorage::Instance().Reset();
                ObjectWithoutDtor<std::multiset<
                    int,
                    std::less<int>,
                    BumpAllocator<int, SolutionStorage>>>
                    q;
                for (u32 i = num_workers - num_tasks; i != num_workers; ++i)
                {
                    q->insert(workers[i]);
                }

                for (; ti != t_end && !q->empty();)
                {
                    auto it = std::prev(q->end());
                    if (tasks[ti] <= *it)
                    {
                        --ti;
                        q->erase(it);
                        continue;
                    }

                    // use pill
                    if (p++ == pills) break;

                    // find worker
                    it = q->lower_bound(tasks[ti] - strength);
                    if (it == q->end()) break;
                    q->erase(it);
                    --ti;
                }
            }

            return ti == t_end;
        };

        return cast<int>(*std::ranges::lower_bound(
                   std::views::iota(u32{0}, cast<u32>(tasks.size() + 1)),
                   false,
                   std::greater{},
                   canComplete)) -
               1;
    }
};

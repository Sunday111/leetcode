#include <algorithm>
#include <array>
#include <ranges>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

template <typename To>
[[nodiscard]] FORCE_INLINE static constexpr To to(auto v) noexcept
{
    return static_cast<To>(v);
}

class Solution
{
public:
    int maxTaskAssign(
        std::vector<int>& tasks,
        std::vector<int>& workers,
        const int pills,
        const int strength)
    {
        std::ranges::sort(tasks);
        std::ranges::sort(workers);
        static std::array<u64, 50'001> ws, ts;
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

        const u32 nw = cast<u32>(workers.size());
        static std::array<u8, 50'001> used_workers;

        return cast<int>(*std::ranges::lower_bound(
                   std::views::iota(u32{0}, cast<u32>(tasks.size() + 1)),
                   false,
                   std::greater{},
                   [&](const u32 num_tasks)
                   {
                       int p = 0;

                       u32 ti = num_tasks - 1;
                       const u32 t_end = 0xFFFFFFFF;
                       if (num_tasks <= nw)
                       {
                           const u32 w0 = nw - num_tasks;

                           {
                               u64 req = 0;
                               if (num_tasks > 0) req = ts[num_tasks - 1];

                               u64 avl = ws[nw - 1] +
                                         cast<u64>(pills) * cast<u64>(strength);
                               if (w0 > 0) avl -= ws[w0 - 1];

                               if (req > avl) return false;
                           }

                           const u32 w_end = w0 - 1;
                           std::fill_n(used_workers.begin(), nw, 0);

                           for (u32 wi = nw - 1; ti != t_end && wi != w_end;)
                           {
                               if (used_workers[wi])
                               {
                                   --wi;
                                   continue;
                               }

                               int task = tasks[ti];
                               if (task <= workers[wi])
                               {
                                   --ti;
                                   --wi;
                                   continue;
                               }

                               // use pill
                               if (p++ == pills) break;
                               task = std::max(0, task - strength);

                               // find worker
                               auto begin = std::next(workers.begin(), w0);
                               auto end = std::next(workers.begin(), wi + 1);
                               u32 wx =
                                   w0 +
                                   cast<u32>(std::distance(
                                       begin,
                                       std::lower_bound(begin, end, task)));

                               while (wx <= wi && used_workers[wx]) ++wx;

                               if (wx > wi) break;

                               used_workers[wx] = 1;
                               wi -= (wx == wi);
                               --ti;
                           }
                       }

                       return ti == t_end;
                   })) -
               1;
    }
};

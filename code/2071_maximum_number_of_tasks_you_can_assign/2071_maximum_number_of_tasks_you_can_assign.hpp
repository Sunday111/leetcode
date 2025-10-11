#include <algorithm>
#include <array>
#include <ranges>
#include <vector>

#include "radix_sorter.hpp"

template <typename To>
[[nodiscard]] FORCE_INLINE static constexpr To to(auto v) noexcept
{
    return static_cast<To>(v);
}

class Solution
{
public:
    static int maxTaskAssign(
        std::vector<int>& tasks,
        std::vector<int>& workers,
        const u32 pills,
        const int strength) noexcept
    {
        radix_sort<8>(reinterpret_range<u32>(tasks));
        radix_sort<8>(reinterpret_range<u32>(workers));

        const u32 num_workers = to<u32>(workers.size());

        static std::array<int, 50'001> q;

        auto canComplete = [&](const u32 num_tasks)
        {
            u32 qi = 0, qs = 0;
            u32 p = pills, j = num_workers - 1;
            for (u32 i = num_tasks; i--;)
            {
                int a = tasks[i];
                if (qi != qs && q[qi] >= a)
                {
                    ++qi;
                    continue;
                }
                if (j < num_workers && workers[j] >= a)
                {
                    j--;
                    continue;
                }
                a -= strength;
                while (j < num_workers && workers[j] >= a)
                {
                    q[qs++] = workers[j--];
                }
                if (qi == qs || p-- == 0) return false;
                --qs;
            }
            return true;
        };

        return to<int>(*std::ranges::lower_bound(
                   std::views::iota(u32{0}, to<u32>(tasks.size() + 1)),
                   false,
                   std::greater{},
                   canComplete)) -
               1;
    }
};

#include <algorithm>
#include <cassert>
#include <vector>

#include "bump_allocator.hpp"
#include "heap_with_erase.hpp"
#include "integral_aliases.hpp"

using SolutionStorage = GlobalBufferStorage<1u << 25>;

class Solution
{
public:
    struct sum_n_smallest
    {
        FORCE_INLINE constexpr void reserve(size_t n) noexcept
        {
            larger.reserve(n);
            smaller.reserve(n);
        }

        template <class Iter>
        FORCE_INLINE constexpr void init(Iter begin, Iter end) noexcept
        {
            smaller.init(begin, end);
            for (auto i = begin; i < end; ++i)
            {
                sum += *i;
            }
        }

        FORCE_INLINE constexpr void add_and_drop(u32 a, u32 d) noexcept
        {
            const u32 top_larger = larger.top();
            if (a >= top_larger == d >= top_larger)
            {
                if (a == d) return;
                if (a >= top_larger)
                {
                    larger.erase(d);
                    larger.push(a);
                }
                else
                {
                    smaller.erase(d);
                    smaller.push(a);
                    sum += a;
                    sum -= d;
                }
                return;
            }
            drop(d, top_larger);
            add(a);
        }

        FORCE_INLINE constexpr void add(u32 i) noexcept
        {
            const u32 old_top = smaller.top();
            if (i < old_top)
            {
                smaller.push(i);
                smaller.pop();
                larger.push(old_top);
                sum += i;
                sum -= old_top;
            }
            else
            {
                larger.push(i);
            }
        }

        FORCE_INLINE constexpr void drop(u32 i, u32 old_top) noexcept
        {
            if (i < old_top)
            {
                smaller.erase(i);
                larger.pop();
                smaller.push(old_top);
                sum += old_top;
                sum -= i;
            }
            else
            {
                larger.erase(i);
            }
        }

        max_heap_with_erase<
            u32,
            std::identity,
            BumpAllocator<u32, SolutionStorage>>
            smaller;
        min_heap_with_erase<
            u32,
            std::identity,
            BumpAllocator<u32, SolutionStorage>>
            larger;
        u64 sum = 0;
    };

    [[nodiscard]] auto
    minimumCost(const std::vector<u32>& nums, u32 k, u32 dist) const noexcept
    {
        const u32 n = static_cast<u32>(nums.size()), d2 = dist + 2;

        if (d2 == k)
        {
            u64 run_sum = 0;
            for (u32 i = 1; i != d2; ++i) run_sum += nums[i];

            u64 min_run_sum = run_sum;
            for (u32 left = 1, right = d2; right != n; ++left, ++right)
            {
                run_sum += nums[right];
                run_sum -= nums[left];
                min_run_sum = std::min(min_run_sum, run_sum);
            }

            return nums[0] + min_run_sum;
        }

        sum_n_smallest sum_n;
        sum_n.reserve(2 * n);
        sum_n.init(nums.begin() + 1, nums.begin() + k);
        for (u32 i = k, lim = d2; i != lim; ++i)
        {
            sum_n.add(nums[i]);
        }

        u64 r = sum_n.sum;
        for (u32 left = 1, right = d2; right != n; ++left, ++right)
        {
            sum_n.add_and_drop(nums[right], nums[left]);
            r = std::min(r, sum_n.sum);
        }

        return nums[0] + r;
    }

    [[nodiscard]] auto
    minimumCost(std::vector<int>& nums, u32 k, u32 dist) noexcept
    {
        return minimumCost(reinterpret_cast<std::vector<u32>&>(nums), k, dist);
    }
};

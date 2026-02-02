#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

template <
    typename T,
    typename Cmp,
    typename Proj = std::identity,
    typename Allocator = std::allocator<T>>
struct heap_with_erase
{
    template <typename Op>
    FORCE_INLINE constexpr static void heap_op(
        Op&& op,
        std::vector<T>& rng) noexcept
    {
        std::forward<Op>(op)(rng, Cmp{});
    }

    FORCE_INLINE constexpr static void push_(std::vector<T>& rng, T v) noexcept
    {
        rng.push_back(v);
        heap_op(std::ranges::push_heap, rng);
    }

    FORCE_INLINE constexpr static void pop_(std::vector<T>& rng) noexcept
    {
        heap_op(std::ranges::pop_heap, rng);
        rng.pop_back();
    }

    FORCE_INLINE constexpr void reserve(size_t n) noexcept
    {
        queued.reserve(n);
        erased.reserve(n);
    }

    template <typename It>
    FORCE_INLINE constexpr void init(It begin, It end) noexcept
    {
        assert(empty());
        queued.insert(queued.end(), begin, end);
        heap_op(std::ranges::make_heap, queued);
    }

    [[nodiscard]] FORCE_INLINE const T& top() const noexcept
    {
        purge();
        return queued.front();
    }

    FORCE_INLINE constexpr void pop() noexcept
    {
        purge();
        pop_(queued);
    }

    [[nodiscard]] FORCE_INLINE constexpr bool empty() const noexcept
    {
        return queued.size() == erased.size();
    }

    [[nodiscard]] FORCE_INLINE constexpr size_t size() const noexcept
    {
        return queued.size() - erased.size();
    }

    FORCE_INLINE constexpr void push(const T& v) noexcept { push_(queued, v); }

    FORCE_INLINE constexpr void erase(const T& v) noexcept { push_(erased, v); }

private:
    [[nodiscard]] FORCE_INLINE static constexpr bool eq(
        const T& a,
        const T& b) noexcept
    {
        constexpr Proj p{};
        constexpr Cmp c{};
        auto pa = p(a), pb = p(b);
        return c(pa, pb) == c(pb, pa);
    }

    FORCE_INLINE constexpr void purge() const noexcept
    {
        while (!erased.empty() && eq(erased.front(), queued.front()))
        {
            pop_(erased);
            pop_(queued);
        }
    }

    mutable std::vector<T> queued, erased;
};

template <
    typename T,
    typename Proj = std::identity,
    typename Allocator = std::allocator<T>>
using min_heap_with_erase = heap_with_erase<T, std::greater<>, Proj, Allocator>;

template <
    typename T,
    typename Proj = std::identity,
    typename Allocator = std::allocator<T>>
using max_heap_with_erase = heap_with_erase<T, std::less<>, Proj, Allocator>;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

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

        max_heap_with_erase<u32> smaller;
        min_heap_with_erase<u32> larger;
        u64 sum = 0;
    };

    [[nodiscard]] auto
    minimumCost(const std::vector<u32>& nums, u32 k, u32 dist) const noexcept
    {
        const u32 n = static_cast<u32>(nums.size()), d2 = dist + 2;
        // The special case when dist == k-2
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

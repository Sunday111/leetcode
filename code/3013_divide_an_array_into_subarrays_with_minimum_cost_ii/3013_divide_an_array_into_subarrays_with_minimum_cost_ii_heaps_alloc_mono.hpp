#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

#define NO_SANITIZERS \
    __attribute__((no_sanitize("undefined", "address", "coverage", "thread")))

struct ScopedArena
{
    u32 rollback_offset = 0;
    u32* offset = nullptr;

    [[gnu::always_inline]] inline void Reset() const noexcept
    {
        *offset = rollback_offset;
    }

    [[gnu::always_inline]] inline ~ScopedArena() noexcept
    {
        if (offset)
        {
            Reset();
            offset = nullptr;
        }
    }
};

template <u32 num_bytes>
struct GlobalBufferStorage
{
    [[gnu::always_inline]] inline static GlobalBufferStorage&
    Instance() noexcept
    {
        static GlobalBufferStorage inst;
        return inst;
    }

    [[gnu::always_inline]] inline void Reset() noexcept
    {
        allocator_offset_ = 0;
    }

    [[nodiscard, gnu::always_inline]] inline ScopedArena StartArena() noexcept
    {
        return {allocator_offset_, &allocator_offset_};
    }

    alignas(64) std::array<std::byte, num_bytes> allocator_memory_;
    u32 allocator_offset_;
};

template <typename T, typename S>
struct BumpAllocator
{
    using value_type = T;

    BumpAllocator() = default;

    template <class U>
    [[gnu::always_inline]] inline explicit constexpr BumpAllocator(
        const BumpAllocator<U, S>&) noexcept
    {
    }

    [[nodiscard, gnu::always_inline, gnu::hot]] inline T* allocate(
        u32 n) noexcept NO_SANITIZERS
    {
        auto& inst = S::Instance();

        // align current offset for T
        u32 alignment = alignof(T);
        u32 offset = inst.allocator_offset_;
        u32 aligned_offset = (offset + (alignment - 1)) & ~(alignment - 1);
        u32 bytes = n * sizeof(T);

        assert(aligned_offset + bytes <= inst.allocator_memory_.size());

        // bump offset
        inst.allocator_offset_ = aligned_offset + bytes;

        return reinterpret_cast<T*>(
            inst.allocator_memory_.data() + aligned_offset);  // NOLINT
    }

    [[gnu::always_inline]] inline void deallocate(T*, u32) noexcept {}

    // equality so containers can compare allocators
    [[gnu::always_inline]] inline constexpr bool operator==(
        const BumpAllocator&) const noexcept
    {
        return true;
    }
    [[gnu::always_inline]] inline constexpr bool operator!=(
        const BumpAllocator&) const noexcept
    {
        return false;
    }
};

template <typename T>
class ObjectWithoutDtor
{
    alignas(T) std::array<std::byte, sizeof(T)> arr;

public:
    [[gnu::always_inline]] inline ObjectWithoutDtor() noexcept { Reset(); }
    [[gnu::always_inline]] inline void Reset() noexcept { new (&get()) T(); }

    [[gnu::always_inline]] inline T& get() noexcept
    {
        return *reinterpret_cast<T*>(arr.data());  // NOLINT
    }

    [[gnu::always_inline]] inline const T& get() const noexcept
    {
        return *reinterpret_cast<const T*>(arr.data());  // NOLINT
    }

    [[gnu::always_inline]] inline T* operator->() noexcept
    {
        return reinterpret_cast<T*>(arr.data());  // NOLINT
    }

    [[gnu::always_inline]] inline const T* operator->() const noexcept
    {
        return reinterpret_cast<const T*>(arr.data());  // NOLINT
    }
};

template <
    typename T,
    typename Cmp,
    typename Proj = std::identity,
    template <typename> typename Allocator = std::allocator>
struct heap_with_erase
{
    template <typename Op>
    [[gnu::always_inline]] inline constexpr static void heap_op(
        Op&& op,
        std::vector<T>& rng) noexcept
    {
        std::forward<Op>(op)(rng, Cmp{});
    }

    [[gnu::always_inline]] inline constexpr static void push_(
        std::vector<T>& rng,
        T v) noexcept
    {
        rng.push_back(v);
        heap_op(std::ranges::push_heap, rng);
    }

    [[gnu::always_inline]] inline constexpr static void pop_(
        std::vector<T>& rng) noexcept
    {
        heap_op(std::ranges::pop_heap, rng);
        rng.pop_back();
    }

    [[gnu::always_inline]] inline constexpr void reserve(size_t n) noexcept
    {
        queued.reserve(n);
        erased.reserve(n);
    }

    template <typename It>
    [[gnu::always_inline]] inline constexpr void init(It begin, It end) noexcept
    {
        assert(empty());
        queued.insert(queued.end(), begin, end);
        heap_op(std::ranges::make_heap, queued);
    }

    [[nodiscard, gnu::always_inline]] inline const T& top() const noexcept
    {
        purge();
        return queued.front();
    }

    [[gnu::always_inline]] inline constexpr void pop() noexcept
    {
        purge();
        pop_(queued);
    }

    [[nodiscard, gnu::always_inline]] inline constexpr bool empty()
        const noexcept
    {
        return queued.size() == erased.size();
    }

    [[nodiscard, gnu::always_inline]] inline constexpr size_t size()
        const noexcept
    {
        return queued.size() - erased.size();
    }

    [[gnu::always_inline]] inline constexpr void push(const T& v) noexcept
    {
        push_(queued, v);
    }

    [[gnu::always_inline]] inline constexpr void erase(const T& v) noexcept
    {
        push_(erased, v);
    }

private:
    [[nodiscard, gnu::always_inline]] inline static constexpr bool eq(
        const T& a,
        const T& b) noexcept
    {
        constexpr Proj p{};
        constexpr Cmp c{};
        auto pa = p(a), pb = p(b);
        return c(pa, pb) == c(pb, pa);
    }

    [[gnu::always_inline]] inline constexpr void purge() const noexcept
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
    template <typename> typename Allocator = std::allocator>
using min_heap_with_erase = heap_with_erase<T, std::greater<>, Proj, Allocator>;

template <
    typename T,
    typename Proj = std::identity,
    template <typename> typename Allocator = std::allocator>
using max_heap_with_erase = heap_with_erase<T, std::less<>, Proj, Allocator>;

using SolutionStorage = GlobalBufferStorage<1u << 25>;

class Solution
{
public:
    struct sum_n_smallest
    {
        [[gnu::always_inline]] inline constexpr void reserve(size_t n) noexcept
        {
            larger.reserve(n);
            smaller.reserve(n);
        }

        template <class Iter>
        [[gnu::always_inline]] inline constexpr void init(
            Iter begin,
            Iter end) noexcept
        {
            smaller.init(begin, end);
            for (auto i = begin; i < end; ++i)
            {
                sum += *i;
            }
        }

        [[gnu::always_inline]] inline constexpr void add_and_drop(
            u32 a,
            u32 d) noexcept
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

        [[gnu::always_inline]] inline constexpr void add(u32 i) noexcept
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

        [[gnu::always_inline]] inline constexpr void drop(
            u32 i,
            u32 old_top) noexcept
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

        template <typename X>
        using Alctr = BumpAllocator<X, SolutionStorage>;

        max_heap_with_erase<u32, std::identity, Alctr> smaller;
        min_heap_with_erase<u32, std::identity, Alctr> larger;
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

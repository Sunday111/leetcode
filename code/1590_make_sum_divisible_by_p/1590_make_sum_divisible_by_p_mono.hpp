#include <array>
#include <cassert>
#include <cstdint>
#include <span>
#include <unordered_map>
#include <utility>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

#define HOT_PATH __attribute__((hot))

#define NO_SANITIZERS \
    __attribute__((no_sanitize("undefined", "address", "coverage", "thread")))

struct ScopedArena
{
    u32 rollback_offset = 0;
    u32* offset = nullptr;

    FORCE_INLINE void Reset() const noexcept { *offset = rollback_offset; }

    FORCE_INLINE ~ScopedArena() noexcept
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
    FORCE_INLINE static GlobalBufferStorage& Instance() noexcept
    {
        static GlobalBufferStorage inst;
        return inst;
    }

    FORCE_INLINE void Reset() noexcept { allocator_offset_ = 0; }

    [[nodiscard]] FORCE_INLINE ScopedArena StartArena() noexcept
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
    FORCE_INLINE explicit constexpr BumpAllocator(
        const BumpAllocator<U, S>&) noexcept
    {
    }

    [[nodiscard]] FORCE_INLINE T* allocate(u32 n) noexcept HOT_PATH
        NO_SANITIZERS
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

    FORCE_INLINE void deallocate(T*, u32) noexcept {}

    // equality so containers can compare allocators
    FORCE_INLINE constexpr bool operator==(const BumpAllocator&) const noexcept
    {
        return true;
    }
    FORCE_INLINE constexpr bool operator!=(const BumpAllocator&) const noexcept
    {
        return false;
    }
};

template <typename T>
class ObjectWithoutDtor
{
    alignas(T) std::array<std::byte, sizeof(T)> arr;

public:
    FORCE_INLINE ObjectWithoutDtor() noexcept { Reset(); }
    FORCE_INLINE void Reset() noexcept { new (&get()) T(); }

    FORCE_INLINE T& get() noexcept
    {
        return *reinterpret_cast<T*>(arr.data());  // NOLINT
    }

    FORCE_INLINE const T& get() const noexcept
    {
        return *reinterpret_cast<const T*>(arr.data());  // NOLINT
    }

    FORCE_INLINE T* operator->() noexcept
    {
        return reinterpret_cast<T*>(arr.data());  // NOLINT
    }

    FORCE_INLINE const T* operator->() const noexcept
    {
        return reinterpret_cast<const T*>(arr.data());  // NOLINT
    }
};

template <
    typename Key,
    typename Value,
    typename Storage,
    typename Hash = std::hash<Key>,
    typename Cmp = std::equal_to<Key>>
using BumpHashMap = std::unordered_map<
    Key,
    Value,
    Hash,
    Cmp,
    BumpAllocator<std::pair<const Key, Value>, Storage>>;

template <typename Value, typename Storage>
using BumpVector = std::vector<Value, BumpAllocator<Value, Storage>>;

template <typename To>
inline static constexpr auto cast = []<typename From>(From&& v) INLINE_LAMBDA
{
    return static_cast<To>(std::forward<From>(v));
};

template <typename To, typename From, std::size_t extent = std::dynamic_extent>
    requires(sizeof(To) == sizeof(From))
[[nodiscard]] FORCE_INLINE static auto reinterpret_range(
    std::span<From, extent> in) noexcept
{
    return std::span<To, extent>{
        reinterpret_cast<To*>(in.data()),  // NOLINT
        in.size()};
}

template <typename To, typename From, typename Allocator>
    requires(sizeof(To) == sizeof(From))
[[nodiscard]] FORCE_INLINE static std::span<To> reinterpret_range(
    std::vector<From, Allocator>& v) noexcept
{
    return reinterpret_range<To>(std::span{v});
}

class Solution
{
private:
    using SolutionStorage = GlobalBufferStorage<1 << 25>;
    static constexpr size_t kArrayCapacity = 100'000;

    [[nodiscard]] static int
    solve_map(std::span<const u32> nums, u32 p, u32 n, u32 target) noexcept
    {
        u32 r = n;
        ObjectWithoutDtor<BumpHashMap<u32, u32, SolutionStorage>> m;
        m->reserve(2 * n);
        m.get()[0] = ~0u;
        for (u32 i = 0; i != n; ++i)
        {
            u32 s = nums[i], x = (s + p - target) % p;
            if (auto it = m->find(x); it != m->end())
            {
                r = std::min(i - it->second, r);
            }
            m.get()[s] = i;
        }
        return r == n ? -1 : cast<int>(r);
    }

    [[nodiscard]] static int
    solve_arr(std::span<const u32> nums, u32 p, u32 n, u32 target) noexcept
    {
        u32 r = n;
        BumpVector<u32, SolutionStorage> m;
        m.resize(p, 2 * n);

        m[0] = ~0u;
        for (u32 i = 0; i != n; ++i)
        {
            u32 s = nums[i], x = (s + p - target) % p;
            r = std::min(i - m[x], r);
            m[s] = i;
        }
        return r == n ? -1 : cast<int>(r);
    }

public:
    [[nodiscard]] static int minSubarray(
        std::vector<int>& nums_,
        u32 p) noexcept
    {
        auto arena = SolutionStorage::Instance().StartArena();
        const auto nums = reinterpret_range<u32>(nums_);
        u32 target = 0, n = cast<u32>(nums.size());
        for (u32& v : nums) v = ((target += v) %= p);
        if (target == 0) return 0;  // No action needed
        auto fn = (p > kArrayCapacity || p > n) ? solve_map : solve_arr;
        return fn(nums, p, n, target);
    }
};

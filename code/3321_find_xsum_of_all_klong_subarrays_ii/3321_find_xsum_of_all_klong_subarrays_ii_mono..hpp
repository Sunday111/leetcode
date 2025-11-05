#include <array>
#include <cassert>
#include <cstdint>
#include <set>
#include <span>
#include <unordered_map>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

#define HOT_PATH __attribute__((hot))

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

    std::array<std::byte, num_bytes> allocator_memory_;
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

using SolutionStorage = GlobalBufferStorage<1 << 25>;

template <typename V, typename Storage, typename Cmp = std::less<V>>
using BumpSet = std::set<V, Cmp, BumpAllocator<V, SolutionStorage>>;

class Solution
{
public:
    std::vector<long long> findXSum(std::span<u32> nums, u32 k, u32 x)
    {
        SolutionStorage::Instance().Reset();
        ObjectWithoutDtor<BumpHashMap<u32, u32, SolutionStorage>> val_to_freq;
        ObjectWithoutDtor<BumpSet<std::pair<u32, u32>, SolutionStorage>>
            freq_val_set;
        ObjectWithoutDtor<BumpSet<std::pair<u32, u32>, SolutionStorage>>
            waitlist;
        u64 current_sum = 0;

        auto add_value = [&](u32 value)
        {
            u32& freq = val_to_freq.get()[value];

            if (freq)
            {
                if (freq_val_set->erase(std::pair{freq, value}))
                {
                    current_sum -= u64{value} * u64{freq};
                }
                else
                {
                    waitlist->erase(std::pair{freq, value});
                }
            }

            if (++freq)
            {
                waitlist->emplace(std::pair{freq, value});
            }
        };

        auto remove_value = [&](u32 value)
        {
            u32& freq = val_to_freq.get()[value];
            if (freq_val_set->erase(std::pair{freq, value}))
            {
                current_sum -= u64{value} * u64{freq};
            }
            else
            {
                waitlist->erase(std::pair{freq, value});
            }

            if (--freq)
            {
                waitlist->emplace(std::pair{freq, value});
            }
        };

        auto refresh_map_size = [&]()
        {
            while (!waitlist->empty() &&
                   (freq_val_set->size() < x ||
                    *waitlist->rbegin() > *freq_val_set->begin()))
            {
                current_sum += u64{waitlist->rbegin()->first} *
                               u64{waitlist->rbegin()->second};
                freq_val_set->insert(
                    waitlist->extract(std::prev(waitlist->end())));
            }

            while (freq_val_set->size() > x)
            {
                auto it = freq_val_set->begin();
                current_sum -= u64{it->second} * u64{it->first};
                waitlist->insert(freq_val_set->extract(it));
            }
        };

        for (u32 i = 0; i != k; ++i) add_value(nums[i]);

        const u32 n = static_cast<u32>(nums.size());
        refresh_map_size();
        std::vector<long long> r;
        r.push_back(static_cast<i64>(current_sum));
        for (u32 i = 0, j = k; j != n; ++i, ++j)
        {
            remove_value(nums[i]);
            add_value(nums[j]);
            refresh_map_size();
            r.push_back(static_cast<i64>(current_sum));
        }

        return r;
    }

    std::vector<long long> findXSum(std::vector<int>& nums, u32 k, u32 x)
    {
        return findXSum(reinterpret_range<u32>(nums), k, x);
    }
};

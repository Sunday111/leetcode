#include <array>
#include <cassert>
#include <cstdint>
#include <set>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

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

template <typename V, typename Storage, typename Cmp = std::less<V>>
using BumpMultiset = std::multiset<V, Cmp, BumpAllocator<V, Storage>>;

using SolutionStorage = GlobalBufferStorage<1u << 25>;

struct SumKSmallest
{
    u32 k{};
    u64 sum = 0;
    BumpMultiset<u32, SolutionStorage> smallest{};
    BumpMultiset<u32, SolutionStorage> other{};

    FORCE_INLINE void insert(u32 v) noexcept
    {
        if (smallest.size() < k)
        {
            smallest.insert(v);
            sum += v;
        }
        else
        {
            auto it = std::prev(smallest.end());
            if (v < *it)
            {
                other.insert(*it);
                sum -= *it;

                auto node = smallest.extract(it);
                sum += v;
                node.value() = v;
                smallest.insert(std::move(node));
            }
            else
            {
                other.insert(v);
            }
        }
    }

    FORCE_INLINE void erase(u32 v) noexcept
    {
        if (auto it = other.find(v); it != other.end())
        {
            other.erase(it);
        }
        else
        {
            it = smallest.find(v);
            sum -= *it;
            smallest.erase(it);

            if (!other.empty())
            {
                auto it2 = other.begin();
                sum += *it2;
                smallest.insert(*it2);
                other.erase(it2);
            }
        }
    }

    [[nodiscard]] FORCE_INLINE constexpr u32 size() noexcept
    {
        return static_cast<u32>(smallest.size() + other.size());
    }
};

class Solution
{
public:
    [[nodiscard]] static auto
    minimumCost(std::vector<u32>& nums, u32 k, u32 dist) noexcept
    {
        auto& storage = SolutionStorage::Instance();
        auto arena = storage.StartArena();

        ObjectWithoutDtor<SumKSmallest> s;
        s->k = k - 2;

        u64 r = std::numeric_limits<long>::max();
        u32 n = static_cast<u32>(nums.size());

        for (u32 i = 1; i <= dist; ++i) s->insert(nums[i]);

        for (u32 i1 = 1, ik = 1 + dist; ik != n; ++i1, ++ik)
        {
            s->erase(nums[i1]);
            s->insert(nums[ik]);
            r = std::min(r, nums[i1] + s->sum);
        }

        for (u32 i = n - s->size(); !s->other.empty(); ++i)
        {
            s->erase(nums[i]);
            r = std::min(r, nums[i] + s->sum);
        }

        return r + nums[0];
    }

    [[nodiscard]] static auto
    minimumCost(std::vector<int>& nums, u32 k, u32 dist) noexcept
    {
        return minimumCost(reinterpret_cast<std::vector<u32>&>(nums), k, dist);
    }
};

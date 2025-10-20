#include <algorithm>
#include <cassert>
#include <deque>
#include <unordered_map>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

using u32 = uint32_t;
using u64 = uint64_t;

struct ScopedArena
{
    size_t rollback_offset = 0;
    size_t* offset = nullptr;

    ~ScopedArena()
    {
        if (offset)
        {
            *offset = rollback_offset;
            offset = nullptr;
        }
    }
};

template <size_t num_bytes>
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
    size_t allocator_offset_;
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

    [[nodiscard]] FORCE_INLINE T* allocate(std::size_t n) noexcept
    {
        auto& inst = S::Instance();

        // raw buffer start
        std::byte* base = inst.allocator_memory_.data();

        // align current offset for T
        std::size_t alignment = alignof(T);
        std::size_t offset = inst.allocator_offset_;
        std::size_t aligned_offset =
            (offset + (alignment - 1)) & ~(alignment - 1);

        // compute how many bytes we need
        std::size_t bytes = n * sizeof(T);

        assert(aligned_offset + bytes <= inst.allocator_memory_.size());

        // pointer to aligned location
        void* p = base + aligned_offset;  // NOLINT

        // bump offset
        inst.allocator_offset_ = aligned_offset + bytes;

        return static_cast<T*>(p);
    }

    FORCE_INLINE void deallocate(T*, std::size_t) noexcept {}

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

using SolutionStorage = GlobalBufferStorage<1 << 25>;

class Solution
{
public:
    template <typename To>
    [[nodiscard]] FORCE_INLINE static constexpr To to(auto v) noexcept
    {
        return static_cast<To>(v);
    }

    [[nodiscard]] static std::vector<int> avoidFlood(
        std::vector<int>& rains) noexcept
    {
        SolutionStorage::Instance().Reset();
        std::unordered_map<
            int,
            u32,
            std::hash<int>,
            std::equal_to<int>,
            BumpAllocator<std::pair<const int, u32>, SolutionStorage>>
            full_lakes;
        std::deque<u32, BumpAllocator<u32, SolutionStorage>> dry_days;

        for (u32 i = 0; i != rains.size(); ++i)
        {
            int lake = rains[i];
            if (!lake)
            {
                dry_days.push_back(i);
                continue;
            }

            rains[i] = -1;
            const auto [full_lake_iterator, inserted] =
                full_lakes.try_emplace(lake, i);
            if (inserted) continue;

            // This lake is full. Need to find the dry day
            // so that day >= full_lakes[lake]
            const auto dry_day_iterator = std::ranges::lower_bound(
                dry_days,
                std::exchange(full_lake_iterator->second, i));

            if (dry_day_iterator == dry_days.end()) return {};
            rains[*dry_day_iterator] = lake;
            dry_days.erase(dry_day_iterator);
        }

        for (u32 dry_day : dry_days) rains[dry_day] = 1;

        return std::move(rains);
    }
};

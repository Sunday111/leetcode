#ifndef __clang__
#pragma GCC optimize("O3")
#endif

#include <array>
#include <cassert>
#include <set>
#include <vector>

#define NO_SANITIZERS \
    __attribute__((no_sanitize("undefined", "address", "coverage", "thread")))
#define HOT_PATH __attribute__((hot))

#define FORCE_INLINE inline __attribute__((always_inline))
using u32 = uint32_t;

template <size_t num_bytes>
struct GlobalBufferStorage
{
    FORCE_INLINE static GlobalBufferStorage& Instance() noexcept
    {
        static GlobalBufferStorage inst;
        return inst;
    }

    FORCE_INLINE void Reset() noexcept { allocator_offset_ = 0; }

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

    [[nodiscard]] FORCE_INLINE T* allocate(std::size_t n) noexcept HOT_PATH
        NO_SANITIZERS
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

template <
    typename Element,
    typename AllocatorStorage,
    template <typename> typename Comparator>
class BumpSet
{
    using Set = std::set<
        Element,
        Comparator<Element>,
        BumpAllocator<Element, AllocatorStorage>>;
    alignas(Set) inline static std::array<std::byte, sizeof(Set)> arr;

public:
    FORCE_INLINE BumpSet() noexcept
    {
        AllocatorStorage::Instance().Reset();
        new (&get()) Set();
    }

    FORCE_INLINE Set& get() noexcept
    {
        return *reinterpret_cast<Set*>(arr.data());  // NOLINT
    }

    FORCE_INLINE const Set& get() const noexcept
    {
        return *reinterpret_cast<const Set*>(arr.data());  // NOLINT
    }

    FORCE_INLINE Set* operator->() noexcept
    {
        return reinterpret_cast<Set*>(arr.data());  // NOLINT
    }

    FORCE_INLINE const Set* operator->() const noexcept
    {
        return reinterpret_cast<const Set*>(arr.data());  // NOLINT
    }
};

class TaskManager
{
public:
    using UP = std::pair<int, int>;
    using PT = std::pair<int, u32>;
    using SetStorage = GlobalBufferStorage<1 << 22>;
    inline static std::array<UP, 100001> t_up;
    BumpSet<PT, SetStorage, std::greater> pt;  // NOLINT

    explicit TaskManager(std::vector<std::vector<int>>& tasks) noexcept
    {
        for (auto& utp : tasks)
        {
            add(utp[0], static_cast<u32>(utp[1]), utp[2]);
        }
    }

    void add(int userId, u32 taskId, int priority) noexcept NO_SANITIZERS
    {
        t_up[taskId] = {userId, priority};
        pt->emplace(priority, taskId);
    }

    void edit(u32 taskId, int newPriority) noexcept NO_SANITIZERS
    {
        auto& [user, priority] = t_up[taskId];
        auto h = pt->extract({priority, taskId});
        priority = h.value().first = newPriority;
        pt->insert(std::move(h));
    }

    void rmv(u32 taskId) noexcept NO_SANITIZERS
    {
        auto& [userId, priority] = t_up[taskId];
        pt->erase({priority, taskId});
    }

    int execTop() noexcept NO_SANITIZERS
    {
        if (pt->empty()) return -1;
        auto pt_it = pt->begin();
        auto& [userId, priority] = t_up[pt_it->second];
        pt->erase(pt_it);
        return userId;
    }
};

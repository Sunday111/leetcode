#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <set>
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
using BumpSet = std::set<V, Cmp, BumpAllocator<V, Storage>>;

class Solution
{
public:
    struct Edge
    {
        u32 link;
        u32 value;
        u32 next;
    };

    struct Node
    {
        u32 maxEdge = 0xFFFFFFFF;
        u32 firstEdge = 0xFFFFFFFF;
    };

    [[nodiscard]] static constexpr int minMaxWeight(
        u32 n,
        const std::vector<std::vector<int>>& inedges,
        [[maybe_unused]] int threshold) noexcept
    {
        static Node nodes[100'001];  // NOLINT
        std::fill_n(nodes, n, Node{});

        u32 numEdges = 0;
        static Edge edges[100'001];  // NOLINT

        for (auto& inEdge : inedges)
        {
            edges[numEdges] = {
                .link = static_cast<u32>(inEdge[0]),
                .value = static_cast<u32>(inEdge[2]),
                .next = std::exchange(
                    nodes[static_cast<u32>(inEdge[1])].firstEdge,
                    numEdges),
            };
            ++numEdges;
        }

        nodes[0].maxEdge = 0;

        using SetStorage = GlobalBufferStorage<1 << 22>;
        SetStorage::Instance().Reset();
        ObjectWithoutDtor<BumpSet<
            std::pair<u32, u32>,
            SetStorage,
            std::less<std::pair<u32, u32>>>>
            queue;
        queue->emplace(0, 0);

        while (!queue->empty())
        {
            auto [w, node_id] = *queue->begin();
            queue->erase(queue->begin());

            auto& node = nodes[node_id];
            if (node.maxEdge < w) continue;

            for (u32 edgeId = node.firstEdge; edgeId != 0xFFFFFFFF;)
            {
                const Edge& edge = edges[edgeId];
                u32 maxEdgeInPath = std::max(node.maxEdge, edge.value);
                if (auto& src_node = nodes[edge.link];
                    maxEdgeInPath < src_node.maxEdge)
                {
                    src_node.maxEdge = maxEdgeInPath;
                    queue->emplace(maxEdgeInPath, edge.link);
                }
                edgeId = edge.next;
            }
        }

        return static_cast<int>(std::ranges::max_element(
                                    nodes,
                                    nodes + n,  // NOLINT
                                    std::less{},
                                    &Node::maxEdge)
                                    ->maxEdge);
    }
};

#include <algorithm>
#include <cassert>
#include <set>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

template <size_t num_bytes>
struct GlobalBufferStorage
{
    FORCE_INLINE static GlobalBufferStorage& Instance() noexcept
    {
        static GlobalBufferStorage inst;
        return inst;
    }

    FORCE_INLINE void Reset() noexcept { allocator_offset_ = 0; }

    inline static constexpr size_t capacity = num_bytes;
    std::byte allocator_memory_[capacity];  // NOLINT
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

        // align current offset for T
        size_t alignment = alignof(T);
        size_t offset = inst.allocator_offset_;
        size_t aligned_offset = (offset + (alignment - 1)) & ~(alignment - 1);

        // compute how many bytes we need
        size_t bytes = static_cast<size_t>(n) * sizeof(T);

        assert(aligned_offset + bytes <= inst.capacity);

        // pointer to aligned location
        void* p = inst.allocator_memory_ + aligned_offset;  // NOLINT

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
    alignas(Set) std::array<std::byte, sizeof(Set)> arr;

public:
    FORCE_INLINE BumpSet() noexcept { new (&get()) Set(); }

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

using u32 = uint32_t;

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
        BumpSet<std::pair<u32, u32>, SetStorage, std::less> queue;
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

#include <algorithm>
#include <array>
#include <cassert>
#include <set>
#include <span>
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

class Solution
{
public:
    using u32 = uint32_t;

    struct Edge  // NOLINT
    {
        u32 src;
        u32 value;
        u32 next = 0xFFFFFFFF;
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
        const auto nodes = [&]()
        {
            static std::array<Node, 100'001> nodes_arr;
            std::fill_n(nodes_arr.begin(), n, Node{});
            return std::span{nodes_arr}.first(n);
        }();

        const auto edges = [&]()
        {
            static std::array<Edge, 100'001> edges_arr;
            u32 numEdges = 0;

            for (auto& inEdge : inedges)
            {
                u32 a = static_cast<u32>(inEdge[0]);
                u32 b = static_cast<u32>(inEdge[1]);
                u32 w = static_cast<u32>(inEdge[2]);

                auto& node = nodes[b];
                edges_arr[numEdges] = {a, w, node.firstEdge};
                node.firstEdge = numEdges++;
            }

            return std::span{edges_arr}.first(numEdges);
        }();

        nodes[0].maxEdge = 0;

        using SetStorage = GlobalBufferStorage<1 << 25>;
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
                if (auto& src_node = nodes[edge.src];
                    maxEdgeInPath < src_node.maxEdge)
                {
                    src_node.maxEdge = maxEdgeInPath;
                    queue->emplace(maxEdgeInPath, edge.src);
                }
                edgeId = edge.next;
            }
        }

        u32 r = 0;
        for (auto& node : nodes) r = std::max(r, node.maxEdge);

        if (r == 0xFFFFFFFF) return -1;
        return static_cast<int>(r);
    }
};

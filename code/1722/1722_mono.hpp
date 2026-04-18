#include <array>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <ranges>
#include <unordered_map>
#include <utility>
#include <vector>





#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

#define HOT_PATH __attribute__((hot))


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

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
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};


namespace stdr = std::ranges;
namespace stdv = std::views;


// Swaps a and b if condition is true. Only for integers. Branchless
inline static constexpr auto swap_if =
    []<std::integral Int> [[gnu::always_inline]] (
        bool condition,
        Int& a,
        Int& b) noexcept
{
    Int mask = static_cast<Int>(static_cast<Int>(a ^ b) & -Int{condition});
    a ^= mask, b ^= mask;
};

struct UFNode
{
    u32 parent;
    u32 size;
};

class Solution
{
public:
    static u32 impl(
        const std::vector<u32>& s,
        const std::vector<u32>& t,
        const std::vector<std::vector<u32>>& swaps) noexcept
    {
        static UFNode nodes[100'000];

        const u32 n = cast<u32>(s.size());

        for (u32 i = 0; i != n; ++i)
        {
            nodes[i].parent = i;
            nodes[i].size = 1;
        }

        auto find = [&] [[gnu::always_inline]] (u32 i) -> u32
        {
            u32 root = i;
            while (nodes[root].parent != root)
            {
                root = nodes[root].parent;
            }
            while (i != root)
            {
                u32 next = nodes[i].parent;
                nodes[i].parent = root;
                i = next;
            }
            return root;
        };

        for (auto& swp : swaps)
        {
            u32 ra = find(swp[0]), rb = find(swp[1]);
            swap_if(nodes[rb].size < nodes[ra].size, ra, rb);
            auto &a = nodes[ra], &b = nodes[rb];
            a.parent = rb;
            b.size += a.size & -u32{ra != rb};
        }

        using Storage = GlobalBufferStorage<1 << 23>;
        auto _ = Storage::Instance().StartArena();
        BumpVector<ObjectWithoutDtor<BumpHashMap<u32, int, Storage>>, Storage>
            groups;
        groups.reserve(n);

        static u32 node_to_group[100001];
        std::fill_n(node_to_group, n, ~u32{});
        for (u32 i = 0; i != n; ++i)
        {
            u32 root = find(i);
            auto& gi = node_to_group[root];
            if (gi == ~u32())
            {
                gi = cast<u32>(groups.size());
                groups.emplace_back();
                groups.back().get().reserve(nodes[root].size);
            }

            if (u32 sv = s[i], tv = t[i]; sv != tv)
            {
                auto& g = groups[gi];
                ++g.get()[sv];
                --g.get()[tv];
            }
        }

        u32 dist = 0;
        for (auto& g : groups)
        {
            for (auto& v : g.get() | stdv::values)
            {
                dist += cast<u32>(std::abs(v));
            }
        }

        return dist / 2;
    }

    u32 minimumHammingDistance(
        const std::vector<int>& source,
        const std::vector<int>& target,
        const std::vector<std::vector<int>>& allowedSwaps) const noexcept
    {
        return impl(
            reinterpret_cast<const std::vector<u32>&>(source),
            reinterpret_cast<const std::vector<u32>&>(target),
            reinterpret_cast<const std::vector<std::vector<u32>>&>(
                allowedSwaps));
    }
};

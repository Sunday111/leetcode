#include <array>
#include <bitset>
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
using BumpSet = std::set<V, Cmp, BumpAllocator<V, Storage>>;

using u32 = uint32_t;
using i64 = int64_t;

using SolutionStorage = GlobalBufferStorage<1u << 25>;

class Solution
{
public:
    struct Node
    {
        i64 v = 0;
        u32 prev = 0;
        u32 next = 0;
    };

    u32 minimumPairRemoval(std::vector<int>& nums) noexcept
    {
        auto arena = SolutionStorage::Instance().StartArena();

        u32 r = 0, n = static_cast<u32>(nums.size()), left_bound = 0,
            right_bound = n + 1;
        Node* nodes = BumpAllocator<Node, SolutionStorage>{}.allocate(n + 2);

        std::bitset<1 << 17> removed;
        ObjectWithoutDtor<BumpSet<std::pair<i64, u32>, SolutionStorage>> set;

        removed[left_bound] = 1;
        nodes[left_bound] = {
            .v = std::numeric_limits<i64>::lowest(),
            .prev = 0,
            .next = 1,
        };

        u32 num_bad = 0;
        for (u32 i = 1; i != right_bound; ++i)
        {
            i64 v = nums[i - 1];

            nodes[i] = {
                .v = v,
                .prev = i - 1,
                .next = i + 1,
            };

            if (i != n)
            {
                i64 vi = v;
                i64 vj = nums[i];
                num_bad += (vi > vj);
                set->emplace(vi + vj, i);
            }
        }

        removed[right_bound] = 1;
        nodes[right_bound] = {
            .v = std::numeric_limits<i64>::max(),
            .prev = n,
            .next = right_bound,
        };

        while (num_bad)
        {
            auto pop_node = set->extract(*set->begin());
            const auto [next_sum, i] = pop_node.value();
            auto& node = nodes[i];
            auto& prev = nodes[node.prev];
            auto& next = nodes[node.next];
            auto& next_next = nodes[next.next];

            if (removed[i] || node.next == right_bound) continue;

            i64 new_value = node.v + nodes[node.next].v;
            if (new_value != next_sum)
            {
                pop_node.value() = {node.v + nodes[node.next].v, i};
                set->insert(std::move(pop_node));
                continue;
            }

            num_bad += (new_value > next_next.v) + (prev.v > new_value) -
                       (prev.v > node.v) - (node.v > next.v) -
                       (next.v > next_next.v);

            i64 old_value = std::exchange(node.v, new_value);
            removed[node.next] = 1;
            node.next = next.next;
            next_next.prev = i;

            if (next.next != right_bound)
            {
                pop_node.value() = {node.v + next_next.v, i};
                set->insert(std::move(pop_node));
            }

            if (node.prev != left_bound)
            {
                i64 pv = prev.v;
                auto x = set->extract(set->find({pv + old_value, node.prev}));
                x.value().first = node.v + pv;
                set->insert(std::move(x));
            }

            ++r;
        }

        return r;
    }
};

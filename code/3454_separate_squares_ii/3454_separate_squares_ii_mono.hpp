#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <map>
#include <set>
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

#define NO_SANITIZERS \
    __attribute__((no_sanitize("undefined", "address", "coverage", "thread")))

struct ScopedArena
{
    u32 rollback_offset = 0;
    u32* offset = nullptr;

    [[gnu::always_inline]] inline void Reset() const noexcept
    {
        *offset = rollback_offset;
    }

    [[gnu::always_inline]] inline ~ScopedArena() noexcept
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
    [[gnu::always_inline]] inline static GlobalBufferStorage&
    Instance() noexcept
    {
        static GlobalBufferStorage inst;
        return inst;
    }

    [[gnu::always_inline]] inline void Reset() noexcept
    {
        allocator_offset_ = 0;
    }

    [[nodiscard, gnu::always_inline]] inline ScopedArena StartArena() noexcept
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
    [[gnu::always_inline]] inline explicit constexpr BumpAllocator(
        const BumpAllocator<U, S>&) noexcept
    {
    }

    [[nodiscard, gnu::always_inline, gnu::hot]] inline T* allocate(
        u32 n) noexcept NO_SANITIZERS
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

    [[gnu::always_inline]] inline void deallocate(T*, u32) noexcept {}

    // equality so containers can compare allocators
    [[gnu::always_inline]] inline constexpr bool operator==(
        const BumpAllocator&) const noexcept
    {
        return true;
    }
    [[gnu::always_inline]] inline constexpr bool operator!=(
        const BumpAllocator&) const noexcept
    {
        return false;
    }
};

template <typename T>
class ObjectWithoutDtor
{
    alignas(T) std::array<std::byte, sizeof(T)> arr;

public:
    [[gnu::always_inline]] inline ObjectWithoutDtor() noexcept { Reset(); }
    [[gnu::always_inline]] inline void Reset() noexcept { new (&get()) T(); }

    [[gnu::always_inline]] inline T& get() noexcept
    {
        return *reinterpret_cast<T*>(arr.data());  // NOLINT
    }

    [[gnu::always_inline]] inline const T& get() const noexcept
    {
        return *reinterpret_cast<const T*>(arr.data());  // NOLINT
    }

    [[gnu::always_inline]] inline T* operator->() noexcept
    {
        return reinterpret_cast<T*>(arr.data());  // NOLINT
    }

    [[gnu::always_inline]] inline const T* operator->() const noexcept
    {
        return reinterpret_cast<const T*>(arr.data());  // NOLINT
    }
};

template <typename K, typename V, typename Storage, typename Cmp = std::less<K>>
using BumpMap =
    std::map<K, V, Cmp, BumpAllocator<std::pair<const K, V>, Storage>>;

template <typename V, typename Storage, typename Cmp = std::less<V>>
using BumpSet = std::set<V, Cmp, BumpAllocator<V, Storage>>;

template <typename Value, typename Storage>
using BumpVector = std::vector<Value, BumpAllocator<Value, Storage>>;

template <typename To>
inline static constexpr auto cast =
    []<typename From> [[gnu::always_inline]] (From&& v)
{
    return static_cast<To>(std::forward<From>(v));
};

using Storage = GlobalBufferStorage<1u << 25>;

struct Event
{
    u32 x1, x2, y, type;
};

struct Node
{
    u32 covered_cnt : 31 = 0;
    u32 covered_len : 31 = 0;
    u32 left_covered : 1 = 0;
    u32 right_covered : 1 = 0;
};
struct SegmentTree
{
    BumpVector<u32, Storage> vals;
    BumpVector<Node, Storage> tree;

    explicit SegmentTree(const BumpSet<u32, Storage>& st)
        : vals(st.begin(), st.end()),
          tree(4 * st.size())
    {
    }

    void update_range(u32 l, u32 r, u32 delta)
    {
        update_range(l, r, delta, 1, 0, cast<u32>(vals.size()) - 1);
    }

    void update_range(u32 l, u32 r, u32 delta, u32 v, u32 vl, u32 vr)
    {
        if (vl > r || vr < l) return;

        u32 mid = (vl + vr) / 2;
        if (l <= vl && vr <= r)
        {
            tree[v].covered_cnt += delta;
        }
        else
        {
            update_range(l, r, delta, 2 * v, vl, mid);
            update_range(l, r, delta, 2 * v + 1, mid + 1, vr);
        }
        if (tree[v].covered_cnt)
        {
            tree[v].covered_len = vals[vr] - vals[vl] + 1;
            tree[v].left_covered = tree[v].right_covered = true;
        }
        else if (vl == vr)
        {
            tree[v].covered_len = 0;
            tree[v].left_covered = tree[v].right_covered = false;
        }
        else
        {
            tree[v].covered_len =
                tree[2 * v].covered_len + tree[2 * v + 1].covered_len;
            if (tree[2 * v].right_covered && tree[2 * v + 1].left_covered)
            {
                tree[v].covered_len += vals[mid + 1] - vals[mid] - 1;
            }
            tree[v].left_covered = tree[2 * v].left_covered;
            tree[v].right_covered = tree[2 * v + 1].right_covered;
        }
    }
    u32 covered() { return tree[1].covered_len; }
};

class Solution
{
public:
    double separateSquares(std::vector<std::vector<int>>& squares_)
    {
        auto arena = Storage::Instance().StartArena();

        auto& squares =
            reinterpret_cast<std::vector<std::vector<u32>>&>(squares_);

        BumpMap<u32, u32, Storage> mapping;
        BumpSet<u32, Storage> vals;
        for (auto& sq : squares)
        {
            vals.insert(sq[0] - 1);
            vals.insert(sq[0]);
            vals.insert(sq[0] + sq[2] - 1);
            vals.insert(sq[0] + sq[2]);
        }
        for (u32 s = 0; auto v : vals) mapping[v] = s++;

        BumpVector<Event, Storage> events;
        for (auto& sq : squares)
        {
            u32 x1 = sq[0], x2 = sq[0] + sq[2] - 1;
            events.emplace_back(mapping[x1], mapping[x2], sq[1], 1);
            events.emplace_back(
                mapping[x1],
                mapping[x2],
                sq[1] + sq[2],
                0xFFFFFFFF);
        }
        std::ranges::sort(events, std::less{}, &Event::y);

        SegmentTree segtree(vals);

        u32 prev_y = 0;
        u64 total_area = 0;
        for (auto& event : events)
        {
            total_area += u64{event.y - prev_y} * segtree.covered();
            prev_y = event.y;
            segtree.update_range(event.x1, event.x2, event.type);
        }

        u64 current_area = 0;
        prev_y = 0;
        for (auto& event : events)
        {
            u64 next_area =
                current_area + u64{event.y - prev_y} * segtree.covered();
            if (next_area >= (total_area + 1) / 2)
            {
                return prev_y + ((cast<double>(total_area) / 2) -
                                 cast<double>(current_area)) /
                                    segtree.covered();
            }
            else
            {
                current_area = next_area;
            }
            prev_y = event.y;
            segtree.update_range(event.x1, event.x2, event.type);
        }
        std::unreachable();
    }
};

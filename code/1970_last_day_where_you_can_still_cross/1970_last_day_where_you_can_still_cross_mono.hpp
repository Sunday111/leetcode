#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <span>
#include <unordered_map>
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

struct Vec2
{
    u16 x, y;

    bool operator==(const Vec2&) const noexcept = default;

    Vec2 operator+(Vec2 v) const noexcept
    {
        return {.x = static_cast<u16>(x + v.x), .y = static_cast<u16>(y + v.y)};
    }
};

using SolutionStorage = GlobalBufferStorage<1 << 25>;

class Solution
{
public:
    size_t
    latestDayToCross(u16 row, u16 col, std::vector<std::vector<int>>& cells)
    {
        auto arena = SolutionStorage::Instance().StartArena();

        const u16 h = row + 2, w = col + 2;
        auto pos_to_index = [&](Vec2 p) -> u16
        {
            return p.y * w + p.x;
        };

        ObjectWithoutDtor<BumpHashMap<u16, u16, SolutionStorage>> cell_to_group;
        ObjectWithoutDtor<
            BumpHashMap<u16, BumpVector<u16, SolutionStorage>, SolutionStorage>>
            groups;
        cell_to_group->reserve(w * h);
        groups->reserve(cells.size());
        u16 next_group_id = 0;
        u16 left_group_id = next_group_id++;
        u16 right_group_id = next_group_id++;

        {
            auto& left_group = groups.get()[left_group_id];
            auto& right_group = groups.get()[right_group_id];
            for (u16 y = 0, last_x = w - 1; y != h; ++y)
            {
                u16 left_idx = pos_to_index({.x = 0, .y = y});
                u16 right_idx = pos_to_index({.x = last_x, .y = y});
                left_group.push_back(left_idx);
                right_group.push_back(right_idx);
                cell_to_group.get()[left_idx] = left_group_id;
                cell_to_group.get()[right_idx] = right_group_id;
            }
        }

        constexpr std::array<Vec2, 8> offsets{{
            {0xFFFF, 0xFFFF},
            {0xFFFF, 0},
            {0xFFFF, 1},
            {0, 0xFFFF},
            {0, 1},
            {1, 0xFFFF},
            {1, 0},
            {1, 1},
        }};

        u16 day = 0;
        for (auto& cell_vec : cells)
        {
            const Vec2 flood_pos{
                .x = static_cast<u16>(cell_vec[1]),
                .y = static_cast<u16>(cell_vec[0])};
            const u16 flood_index = pos_to_index(flood_pos);

            // Find flooded neighbor groups
            std::array<u16, 8> neighbor_groups;  // NOLINT
            uint8_t num_neighbor_groups = 0;
            for (Vec2 offset : offsets)
            {
                Vec2 neighbor_pos = offset + flood_pos;
                u16 neighbor_i = pos_to_index(neighbor_pos);

                auto it = cell_to_group->find(neighbor_i);
                if (it != cell_to_group->end())
                {
                    neighbor_groups[num_neighbor_groups++] = it->second;
                }
            }

            // deduplicate
            auto ng = std::span{neighbor_groups}.first(num_neighbor_groups);
            std::ranges::sort(ng);
            ng = std::span{ng.begin(), std::ranges::unique(ng).begin()};

            u16 group_id = 0;

            if (ng.size() == 0)
            {
                // form a new group
                group_id = next_group_id++;
            }
            else if (ng.size() == 1)
            {
                // add to group
                group_id = neighbor_groups[0];
            }
            else
            {
                // merge groups

                // find merge target
                u16 target_group_id = 0;
                u16 target_group_size = 0;
                bool found_left = false;
                bool found_right = false;
                for (u16 g : ng)
                {
                    found_left |= (g == left_group_id);
                    found_right |= (g == right_group_id);
                    u16 group_size = groups.get()[g].size() & 0xFFFF;
                    if (group_size > target_group_size)
                    {
                        target_group_size = group_size;
                        target_group_id = g;
                    }
                }

                // left and right have to merge, which means
                // there will be no way from top to bottom
                if (found_left && found_right) return day;

                // Even if there is largest group than left or right,
                // they need to be preserved
                if (found_left) target_group_id = left_group_id;
                if (found_right) target_group_id = right_group_id;

                // Merge everything into the target group
                auto& target = groups.get()[target_group_id];
                for (u16 g : ng)
                {
                    if (g != target_group_id)
                    {
                        auto& source = groups.get()[g];
                        for (u16 x : source)
                        {
                            target.push_back(x);
                            cell_to_group.get()[x] = target_group_id;
                        }
                        groups->erase(g);
                    }
                }

                group_id = target_group_id;
            }

            // add current cell to the group
            auto& group = groups.get()[group_id];
            group.push_back(flood_index);
            cell_to_group.get()[flood_index] = group_id;
            ++day;
        }

        return cells.size();
    }
};

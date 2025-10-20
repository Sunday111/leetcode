#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <unordered_map>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

#define HOT_PATH __attribute__((hot))

#define NO_SANITIZERS \
    __attribute__((no_sanitize("undefined", "address", "coverage", "thread")))

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

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

#define HOT_PATH __attribute__((hot))

using SolutionStorage = GlobalBufferStorage<1 << 25>;

class Solution
{
public:
    using u8 = uint8_t;
    using u32 = uint32_t;

    using Cnt = std::array<u32, 3>;
    std::vector<Cnt, BumpAllocator<Cnt, SolutionStorage>> freq{};
    u32 n = 0;

    [[nodiscard]] static u32 one_char(char target, std::string_view s) noexcept
        HOT_PATH NO_SANITIZERS
    {
        u32 l = 0, r = 0;
        for (char c : s)
        {
            r = std::max(r, l);
            u32 b = c != target;
            l &= (b - 1);
            l += !b;
        }

        return std::max(r, l);
    }

    [[nodiscard]] u32 two_chars(char c1, char c2, char c3)
        const noexcept HOT_PATH NO_SANITIZERS
    {
        const auto scoped_arena = SolutionStorage::Instance().StartArena();

        ObjectWithoutDtor<std::unordered_map<
            u32,
            u32,
            std::hash<u32>,
            std::equal_to<u32>,
            BumpAllocator<std::pair<const u32, u32>, SolutionStorage>>>
            diff_to_idx;
        u32 r = 0;
        const u8 u1 = (c1 - 'a') & 0x1F, u2 = (c2 - 'a') & 0x1F,
                 u3 = (c3 - 'a') & 0x1F;

        u32 split_c1c2 = 0, split_c3 = 0;
        for (u32 i = 0, l = 1; i != n; ++i, ++l)
        {
            const auto& f = freq[i];
            if (f[u3] != split_c3)
            {
                l = 0;
                split_c1c2 = f[u1] - f[u2], split_c3 = f[u3];
                diff_to_idx.Reset();
                continue;
            }

            u32 t = 0;
            if (u32 diff = f[u1] - f[u2] - split_c1c2)
            {
                auto [it, inserted] = diff_to_idx->try_emplace(diff, i);
                t = (inserted - 1) & (i - it->second);
            }
            else
            {
                t = l;
            }
            r = std::max(r, t);
        }

        return r;
    }

    [[nodiscard]] u32 three_chars() const noexcept HOT_PATH NO_SANITIZERS
    {
        const auto scoped_arena = SolutionStorage::Instance().StartArena();

        ObjectWithoutDtor<std::unordered_map<
            u64,
            u32,
            std::hash<u64>,
            std::equal_to<u64>,
            BumpAllocator<std::pair<const u64, u32>, SolutionStorage>>>
            diff_to_idx;
        u32 r = 0;

        for (u32 i = 0; i != n; ++i)
        {
            const auto& [fa, fb, fc] = freq[i];
            u32 t = 0;
            if (u32 d1 = fa - fb, d2 = fc - fa; d1 | d2)
            {
                u64 key = (u64{d1} << 32) | u64{d2};
                auto [it, inserted] = diff_to_idx->try_emplace(key, i);
                t = (inserted - 1) & (i - it->second);
            }
            else
            {
                t = i + 1;
            }
            r = std::max(r, t);
        }

        return r;
    }

    [[nodiscard]] u32 longestBalanced(const std::string& s) noexcept HOT_PATH
        NO_SANITIZERS
    {
        const auto scoped_arena = SolutionStorage::Instance().StartArena();

        n = static_cast<u32>(s.size());

        freq.reserve(n);
        freq.emplace_back()[(s[0] - 'a') & 0x1F]++;

        for (u32 i = 1; i != n; ++i)
        {
            auto f = freq.back();
            ++f[(s[i] - 'a') & 0x1F];
            freq.push_back(f);
        }

        u32 r = 0;
        r = std::max(r, one_char('a', s));
        r = std::max(r, one_char('b', s));
        r = std::max(r, one_char('c', s));
        r = std::max(r, two_chars('a', 'b', 'c'));
        r = std::max(r, two_chars('b', 'c', 'a'));
        r = std::max(r, two_chars('a', 'c', 'b'));
        r = std::max(r, three_chars());
        return r;
    }
};

#ifndef __clang__
auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
#endif

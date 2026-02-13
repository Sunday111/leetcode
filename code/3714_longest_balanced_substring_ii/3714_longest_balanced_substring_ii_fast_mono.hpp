#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <concepts>
#include <cstdint>
#include <string>
#include <utility>





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





template <typename To>
inline static constexpr auto cast = []<typename From>(From&& v) INLINE_LAMBDA
{
    return static_cast<To>(std::forward<From>(v));
};

template <std::integral T>
[[nodiscard]] FORCE_INLINE constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & cast<T>(-c)) + (b & cast<T>(~cast<T>(-c)));
}

using SolutionStorage = GlobalBufferStorage<1 << 23>;

template <u32 capacity, typename Storage>
struct HashTable
{
    struct Entry
    {
        u64 key;
        u32 value;
    };

    Entry* table;
    u64* bits;

    static_assert(
        std::popcount(capacity) == 1,
        "Capacity must be a power of 2");
    inline static constexpr u32 kMask = capacity - 1;
    inline static constexpr u32 kNumWords = std::max(1u, capacity / 64);

    FORCE_INLINE HashTable()
    {
        table = BumpAllocator<Entry, Storage>{}.allocate(capacity);
        bits = BumpAllocator<u64, Storage>{}.allocate(kNumWords);
        std::fill_n(bits, kNumWords, u64{0});
    }

    [[nodiscard]] FORCE_INLINE static constexpr u32 hash(u64 x) noexcept
    {
        u64 z = x;
        z += 0x9e3779b97f4a7c15ULL;
        z = (z ^ (z >> 30U)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27U)) * 0x94d049bb133111ebULL;
        return z >> 32U;
    }

    FORCE_INLINE constexpr u32 try_emplace(u64 k, u32 v) noexcept
    {
        u32 i = hash(k), wi{};
        u64 m{};

        do
        {
            i = (i + u32{1}) & kMask;
            wi = i >> 6;
            m = u64{1} << (i & u32{63});
        } while ((bits[wi] & m) && table[i].key != k);

        auto& e = table[i];
        const bool empty = (bits[wi] & m) == u64{0};
        e.key = iif<u64>(empty, k, e.key);
        e.value = iif<u32>(empty, v, e.value);
        bits[wi] |= m;
        return e.value;
    }
};

class Solution
{
public:
    [[nodiscard]] static u32 longestBalanced(std::string& s) noexcept
    {
        u32 n = static_cast<u32>(s.size());
        u32 ans = 1;

        for (char& c : s) c -= 'a';

        for (u32 i = 0, cnt = 1; i != n; ++i, ++cnt)
        {
            bool b = i + 1 == n || s[i + 1] != s[i];
            ans = std::max(ans, cnt & -u32{b});
            cnt &= -u32{!b};
        }

        if (ans == n) return ans;

        for (char c = 0; c != 3; ++c)
        {
            static int arrs[2][100'001];
            char c2 = static_cast<char>(((c + 1) % 3));
            int d = 0;
            std::fill_n(arrs[0], n + 1, -1);
            std::fill_n(arrs[1], n + 1, -1);
            arrs[0][0] = 0;
            for (u32 i = 0, lb = 0; i != n;)
            {
                bool is_c = s[i] == c;
                bool is_c2 = s[i] == c2;
                bool is_c3 = !is_c and !is_c2;
                d += is_c - is_c2;
                d = d & -!is_c3;
                ++i;
                lb = iif(is_c3, i, lb);
                auto& x = arrs[d < 0][std::abs(d)];
                bool b = std::cmp_greater_equal(x, lb);
                ans = std::max(ans, i - iif(b, static_cast<u32>(x), i));
                x = iif(b, x, static_cast<int>(i));
            }
        }

        const auto arena = SolutionStorage::Instance().StartArena();
        HashTable<1 << 17, SolutionStorage> mp;
        mp.try_emplace(0, 0);
        for (u32 a = 0, b = 0, i = 0; i != n;)
        {
            bool c0 = s[i] == 0;
            bool c1 = s[i] == 1;
            bool c2 = s[i] == 2;
            a += c0 - c1;
            b += c1 - c2;
            ++i;
            u64 key = (u64{a} << 32) | b;
            ans = std::max(ans, i - mp.try_emplace(key, i));
        }

        return ans;
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

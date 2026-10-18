#include <array>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <numeric>
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

template <typename To>
inline static constexpr auto cast =
    []<typename From> [[gnu::always_inline]] (From&& v)
{
    return static_cast<To>(std::forward<From>(v));
};

template <std::integral T>
[[nodiscard, gnu::always_inline]] inline constexpr T
iif(bool c, T a, T b) noexcept
{
    return (a & cast<T>(-c)) + (b & cast<T>(~cast<T>(-c)));
}

template <std::integral T>
[[nodiscard, gnu::always_inline, gnu::hot]] inline constexpr T negate_if(
    bool c,
    T v) noexcept
{
    return iif(c, -v, v);
}

template <typename Key, u32 capacity, typename Storage>
struct HashTable
{
    Key* tk;
    u32* tv;
    u64* bits;

    static_assert(
        std::popcount(capacity) == 1,
        "Capacity must be a power of 2");
    inline static constexpr u32 kMask = capacity - 1;
    inline static constexpr u32 kNumWords = std::max(1u, capacity / 64);

    [[gnu::always_inline]] inline HashTable()
    {
        tk = BumpAllocator<Key, Storage>{}.allocate(capacity);
        tv = BumpAllocator<u32, Storage>{}.allocate(capacity);
        bits = BumpAllocator<u64, Storage>{}.allocate(kNumWords);
        std::fill_n(bits, kNumWords, u64{0});
    }

    [[nodiscard, gnu::always_inline]] inline static constexpr u32 hash(
        u32 x) noexcept
    {
        u64 z = u64{x} + 0x9e3779b97f4a7c15ULL;
        z = (z ^ (z >> 30U)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27U)) * 0x94d049bb133111ebULL;
        return z >> 32U;
    }

    [[nodiscard, gnu::always_inline]] inline static constexpr u32 hash(
        u64 x) noexcept
    {
        u64 z = u64{x} + 0x9e3779b97f4a7c15ULL;
        z = (z ^ (z >> 30U)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27U)) * 0x94d049bb133111ebULL;
        return z >> 32U;
    }

    [[gnu::always_inline]] inline constexpr u32* insert(Key k, u32 v) noexcept
    {
        u32 i = hash(k);
        u32 wi;  // NOLINT
        u64 m;   // NOLINT

        do
        {
            i = ++i & kMask;
            wi = i >> 6;
            m = u64{1} << (i & 63);
        } while ((bits[wi] & m) && tk[i] != k);

        tk[i] = k;
        tv[i] = v;
        bits[wi] |= m;
        return tv + i;
    }

    [[gnu::always_inline]] inline constexpr u32& get_or_add(Key k) noexcept
    {
        u32 i = hash(k);
        u32 wi;  // NOLINT
        u64 m;   // NOLINT

        do
        {
            i = ++i & kMask;
            wi = i >> 6;
            m = u64{1} << (i & 63);
        } while ((bits[wi] & m) && tk[i] != k);

        tk[i] = k;
        tv[i] &= -u32{(bits[wi] & m) != 0};
        bits[wi] |= m;
        return tv[i];
    }

    [[nodiscard, gnu::always_inline]] inline constexpr u32* find(Key k) noexcept
    {
        u32 i = hash(k);
        bool b1, b2;  // NOLINT
        do
        {
            i = ++i & kMask;
            b1 = (bits[i >> 6] & (u64{1} << (i & 63)));
            b2 = tk[i].key != k;
        } while (b1 && b2);

        u64 r = std::bit_cast<u64>(&tk[i].value);
        r &= -u64{b1 && !b2};
        return std::bit_cast<u32*>(r);
    }
};

using SolutionStorage = GlobalBufferStorage<1 << 25>;
class Solution
{
public:
    inline static constexpr int kBias = 1 << 11;

    template <u64 mm = 0>
    [[gnu::always_inline]] inline static u64 pack(int a, int b) noexcept
    {
        return (u64{std::bit_cast<u32>(i32{a + kBias} << 16) |
                    std::bit_cast<u32>(b + kBias)}
                << 32) |
               mm;
    }

    template <u64 mm = 0>
    [[gnu::always_inline]] inline static u64 pack(int a, int b, int c) noexcept
    {
        return std::bit_cast<u64>(i64{a + kBias} << 50) |
               std::bit_cast<u64>(i64{b + kBias} << 30) |
               std::bit_cast<u64>(i64{c + kBias * kBias}) | mm;
    }

    template <u64 mm = 0>
    [[gnu::always_inline]] inline static u64
    pack(int a, int b, int c, int d) noexcept
    {
        return std::bit_cast<u64>(i64{a + kBias} << 48) |
               std::bit_cast<u64>(i64{b + kBias} << 32) |
               std::bit_cast<u64>(i64{c + kBias} << 16) |
               std::bit_cast<u64>(i64{d + kBias}) | mm;
    }

    [[nodiscard]] static u32 countTrapezoids(
        std::vector<std::vector<int>>& points) noexcept
    {
        const u16 n = points.size() & 0xFFFF;
        const u32 nn = u32{n} * (u32{n} - 1);

        if (nn < (1 << 10)) return countTrapezoidsT<1 << 10>(n, points);
        if (nn < (1 << 11)) return countTrapezoidsT<1 << 11>(n, points);
        if (nn < (1 << 12)) return countTrapezoidsT<1 << 12>(n, points);
        if (nn < (1 << 13)) return countTrapezoidsT<1 << 13>(n, points);
        if (nn < (1 << 14)) return countTrapezoidsT<1 << 14>(n, points);
        if (nn < (1 << 15)) return countTrapezoidsT<1 << 15>(n, points);
        if (nn < (1 << 16)) return countTrapezoidsT<1 << 16>(n, points);
        if (nn < (1 << 17)) return countTrapezoidsT<1 << 17>(n, points);
        return countTrapezoidsT<1 << 18>(n, points);
    }

    template <size_t cap>
    [[nodiscard]] static u32 countTrapezoidsT(
        u16 n,
        std::vector<std::vector<int>>& points) noexcept
    {
        auto arena = SolutionStorage::Instance().StartArena();
        HashTable<u64, cap << 1, SolutionStorage> m64;

        u32 cnt = 0;
        for (u16 i = 0; i != n - 1; ++i)
        {
            const int x0 = points[i][0], y0 = points[i][1];
            for (u16 j = i + 1; j != n; ++j)
            {
                const int x1 = points[j][0], y1 = points[j][1];
                int a = y1 - y0, b = x0 - x1, c = y0 * x1 - y1 * x0;
                bool c1 = !a && b < 0;
                bool c2 = a < 0;
                bool c3 = !c1 && c2;
                bool c4 = c1 || c2;
                a = negate_if(c3, a);
                b = negate_if(c4, b);
                c = negate_if(c4, c);
                int gm = std::gcd(a, b), gc = std::gcd(gm, c);

                u64 v1 = pack<(0b00ul << 62) | (~0ul >> 32)>(a / gm, b / gm);
                u64 v2 = pack<(0b01ul << 62) | (~0ul >> 32)>(x0 + x1, y0 + y1);
                u64 v3 = pack<0b10ul << 62>(a / gc, b / gc, c / gc);
                u64 v4 = pack<0b11ul << 62>(x0 + x1, y0 + y1, a / gm, b / gm);

                cnt += m64.get_or_add(v1)++;
                cnt -= m64.get_or_add(v2)++;
                cnt += m64.get_or_add(v4)++;
                cnt -= m64.get_or_add(v3)++;
            }
        }
        return cnt;
    }
};

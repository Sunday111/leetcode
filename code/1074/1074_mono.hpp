#include <bit>
#include <concepts>
#include <cstdint>
#include <type_traits>
#include <utility>
#include <vector>

// https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/





#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

// simplified std::exchange
template <typename T>
    requires std::is_trivially_copyable_v<T>
[[nodiscard]] FORCE_INLINE constexpr T exch(T& x, T new_value) noexcept
{
    T tmp = x;
    x = new_value;
    return tmp;
}




template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

inline static constexpr auto iif =
    []<std::integral T> [[nodiscard, gnu::always_inline]] (
        bool c,
        T a,
        std::type_identity_t<T> b) noexcept -> T
{
    return (a & cast<T>(-c)) + (b & cast<T>(~cast<T>(-c)));
};


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;


using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

template <u32 capacity>
struct HashTable  // NOLINT
{
    struct Entry
    {
        i32 key;
        u32 value;
    };

    static_assert(
        std::popcount(capacity) == 1,
        "Capacity must be a power of 2");
    inline static constexpr u32 kMask = capacity - 1;
    inline static constexpr u32 kNumWords = std::max(1u, capacity / 64);
    Entry table[capacity];
    u64 bits[kNumWords]{};

    [[nodiscard, gnu::always_inline]] static constexpr u32 hash(i32 x) noexcept
    {
        u64 z = std::bit_cast<u32>(x);
        z += 0x9e3779b97f4a7c15ULL;
        z = (z ^ (z >> 30U)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27U)) * 0x94d049bb133111ebULL;
        return z >> 32U;
    }

    [[gnu::always_inline]] constexpr void insert(i32 k, u32 v) noexcept
    {
        u32 i = hash(k);
        u32 wi;  // NOLINT
        u64 m;   // NOLINT

        do
        {
            i = ++i & kMask;
            wi = i >> 6;
            m = u64{1} << (i & 63);
        } while ((bits[wi] & m) && table[i].key != k);

        auto& e = table[i];
        e.key = k;
        e.value = v;
        bits[wi] |= m;
    }

    [[nodiscard, gnu::always_inline]] constexpr u32 value_or_zero(
        i32 k) noexcept
    {
        u32 i = hash(k);
        bool b1, b2;  // NOLINT
        do
        {
            i = ++i & kMask;
            b1 = (bits[i >> 6] & (u64{1} << (i & 63)));
            b2 = table[i].key != k;
        } while (b1 && b2);

        return table[i].value & -u32{b1 && !b2};
    }

    [[gnu::always_inline]] constexpr void increment(i32 k) noexcept
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
        e.key = iif(empty, k, e.key);
        e.value = iif(empty, 1u, e.value + 1);
        bits[wi] |= m;
    }
};

class Solution
{
public:
    u32 numSubmatrixSumTarget(std::vector<std::vector<int>>& orig, int target)
    {
        static i32 g[128 * 128];

        const u8 h = orig.size() & 0xFF, w = orig[0].size() & 0xFF;

        u8 stride = std::bit_width(w + 1u) & 7;

        auto gg = [&] [[nodiscard, gnu::always_inline]] (
                      u8 x,
                      u8 y) noexcept -> decltype(auto)
        {
            return g[(u32{y} << stride) | u32{x}];
        };

        for (u8 y = 0; y != h; ++y)
        {
            for (u8 x = 0; x != w; ++x)
            {
                gg(x, y) = orig[y][x];
            }
        }

        for (u8 y = 0; y != h; ++y)
        {
            i32 s = 0;
            for (u8 x = 0; x != w; ++x)
            {
                s += exch(gg(x, y), s);
            }
            gg(w, y) = s;
        }

        u8 w1 = w + 1;
        u32 r = 0;

        for (u8 x_begin = 0; x_begin != w; ++x_begin)
        {
            for (u8 x_end = x_begin + 1; x_end != w1; ++x_end)
            {
                HashTable<1 << 10> f;
                f.insert(0, 1);
                i32 s = 0;

                for (u8 y = 0; y != h; ++y)
                {
                    s += gg(x_end, y) - gg(x_begin, y);
                    r += f.value_or_zero(s - target);
                    f.increment(s);
                }
            }
        }

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

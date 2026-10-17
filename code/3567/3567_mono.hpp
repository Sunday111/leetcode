#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <numeric>
#include <ranges>
#include <type_traits>
#include <utility>
#include <vector>

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
    return b ^ ((a ^ b) & static_cast<T>(-c));
};

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

template <typename B, typename F>
[[gnu::always_inline]] constexpr void pbs_for_each_layer(F&& f) noexcept
{
    [&]<size_t... layer> [[gnu::always_inline]] (
        std::index_sequence<layer...>) noexcept
    {
        (f(std::integral_constant<size_t, layer>{}), ...);
    }(std::make_index_sequence<B::kNumLayers>());
}

template <typename B, typename F>
[[gnu::always_inline]] constexpr void pbs_for_each_layer_reversed(
    F&& f) noexcept
{
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        { f(std::integral_constant<size_t, B::kNumLayers - (layer + 1)>{}); });
}

template <std::integral T>
[[nodiscard, gnu::always_inline]] static constexpr T ceil_div(
    T a,
    std::type_identity_t<T> b) noexcept
{
    return (a + (b - 1)) / b;
}

template <u64 value>
using UintForValue = std::conditional_t < value < (1 << 8),
      u8,
      std::conditional_t <
          value<
              (1 << 16),
              u16,
              std::conditional_t<value<(1UL << 32), u32, u64>>>;

template <size_t capacity, typename Word = u64>
struct PyramidBitset
{
    static constexpr size_t kCapacity = capacity;
    using ValueType = UintForValue<capacity - 1>;
    static constexpr size_t kWordSize = sizeof(Word) * 8;
    static constexpr u8 kMask = kWordSize - 1;
    static constexpr int kShift = std::bit_width(kMask);
    static constexpr size_t kNumLayers =
        ceil_div(std::bit_width(capacity), kShift);
    static constexpr auto kLayersSizes = []
    {
        std::array<size_t, kNumLayers> sizes{};
        for (size_t i = 0, x = capacity; i != sizes.size(); ++i)
        {
            x = ceil_div(x, kWordSize);
            sizes[i] = x;
        }
        return sizes;
    }();
    static constexpr size_t kTotalWords =
        std::accumulate(kLayersSizes.begin(), kLayersSizes.end(), 0UZ);
    std::array<Word, kTotalWords> words;

    static constexpr auto offsets = []
    {
        std::array<size_t, kNumLayers> offsets;  // NOLINT
        std::exclusive_scan(
            kLayersSizes.begin(),
            kLayersSizes.end(),
            offsets.begin(),
            size_t{});
        return offsets;
    }();
};

template <size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_add(
    PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            typename B::ValueType wi = v >> B::kShift;
            bits.words[B::offsets[layer] + wi] |= Word{1} << (v & B::kMask);
            v = wi;
        });
}

template <size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_add_if(
    PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v,
    bool c) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            typename B::ValueType wi = v >> B::kShift;
            bits.words[B::offsets[layer] + wi] |= Word{c} << (v & B::kMask);
            v = wi;
        });
}

template <size_t capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr bool pbs_add_ex(
    PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    bool added = false;
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            typename B::ValueType wi = v >> B::kShift;
            auto& word = bits.words[B::offsets[layer] + wi];
            Word m = Word{1} << (v & B::kMask);
            if constexpr (layer == 0)
            {
                added = (word & m) == 0;
            }
            word |= m;
            v = wi;
        });
    return added;
}

template <size_t capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr
    typename PyramidBitset<capacity, Word>::ValueType
    pbs_max(const PyramidBitset<capacity, Word>& bits) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    typename B::ValueType wi = 0;
    pbs_for_each_layer_reversed<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            u8 bi = B::kMask -
                        std::countl_zero(bits.words[B::offsets[layer] + wi]) &
                    0xFF;
            typename B::ValueType x =
                cast<typename B::ValueType>(wi << B::kShift) |
                cast<typename B::ValueType>(bi);
            wi = x;
        });
    return wi;
}

template <size_t capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr bool pbs_is_empty(
    const PyramidBitset<capacity, Word>& bits) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    return bits.words[B::offsets[B::kNumLayers - 1]] == 0;
}

template <size_t capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr
    typename PyramidBitset<capacity, Word>::ValueType
    pbs_min(const PyramidBitset<capacity, Word>& bits) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    assert(!pbs_is_empty(bits));
    typename B::ValueType wi = 0;
    pbs_for_each_layer_reversed<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            u8 bi = std::countr_zero(bits.words[B::offsets[layer] + wi]) & 0xFF;
            typename B::ValueType x =
                cast<typename B::ValueType>(wi << B::kShift) |
                cast<typename B::ValueType>(bi);
            wi = x;
        });
    return wi;
}

template <size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_remove(
    PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    bool prev_empty = true;
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            typename B::ValueType wi = v >> B::kShift;
            auto& w = bits.words[B::offsets[layer] + wi];
            w &= ~(Word{prev_empty} << (v & B::kMask));
            v = wi;
            prev_empty = !w;
        });
}

template <size_t capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr bool pbs_remove_ex(
    PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    bool prev_empty = true, removed = false;
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            typename B::ValueType wi = v >> B::kShift;
            auto& w = bits.words[B::offsets[layer] + wi];
            if constexpr (layer == 0)
            {
                removed = (w & (Word{1} << (v & B::kMask)));
            }

            w &= ~(Word{prev_empty} << (v & B::kMask));
            v = wi;
            prev_empty = !w;
        });

    return removed;
}

inline static constexpr auto min2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return std::min(a, b);
};

inline static constexpr auto upd =
    []<typename T, typename F> [[gnu::always_inline]] (
        T & x,
        const std::type_identity_t<T>& another,
        F&& f) noexcept -> T&
{
    return x = std::forward<F>(f)(x, another);
};

inline static constexpr auto upd_min =
    std::bind(upd, std::placeholders::_1, std::placeholders::_2, min2);

// https://leetcode.com/problems/minimum-absolute-difference-in-sliding-submatrix/

class Solution
{
public:
    [[nodiscard]] auto minAbsDiff(
        std::vector<std::vector<int>>& orig,
        const u8 k) const noexcept
    {
        // make all values unsigned
        for (auto& v : orig | std::views::join) v += 100'000;

        auto& grid = reinterpret_cast<std::vector<std::vector<u32>>&>(orig);

        const u8 h = cast<u8>(grid.size()), w = cast<u8>(grid[0].size());
        const u8 hh = h + 1 - k, ww = w + 1 - k;

        static PyramidBitset<200'001> bs{};

        for (u8 sy = 0; sy != hh; ++sy)
        {
            u8 y_end = sy + k;
            for (u8 sx = 0; sx != ww; ++sx)
            {
                u8 x_end = sx + k;

                // For each submatrix of size k

                u16 n = 0;
                for (u8 y = sy; y != y_end; ++y)
                {
                    for (u8 x = sx; x != x_end; ++x)
                    {
                        n += pbs_add_ex(bs, grid[y][x]);
                    }
                }

                // Find the minimum absolute difference
                // AND clear the bitset at the same time
                u32 prev = pbs_min(bs);
                u32& r = grid[sy][sx] = pbs_max(bs) - prev;
                pbs_remove(bs, prev);

                while (--n)
                {
                    u32 v = pbs_min(bs);
                    pbs_remove(bs, v);
                    u32 delta = v - prev;
                    upd_min(r, iif(delta, delta, r));
                    prev = v;
                }
            }

            grid[sy].resize(ww);
        }

        grid.resize(hh);
        return std::move(orig);
    }
};

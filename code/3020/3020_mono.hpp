#include <algorithm>
#include <bit>
#include <cassert>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <type_traits>
#include <utility>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

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

template <u32 capacity, typename Word = u64>
struct PyramidBitset
{
    static_assert(capacity > 0);
    using WordType = std::remove_cv_t<Word>;
    static constexpr u32 kCapacity = capacity;
    using ValueType = UintForValue<capacity - 1>;
    static constexpr size_t kWordSize = sizeof(Word) * 8;
    static constexpr u8 kMask = kWordSize - 1;
    static constexpr int kShift = std::bit_width(kMask);
    static constexpr size_t kNumLayers = []
    {
        size_t layers = 1;
        for (size_t n = capacity; n > kWordSize; n = ceil_div(n, kWordSize))
        {
            ++layers;
        }
        return layers;
    }();

private:
    struct Layout
    {
        size_t sizes[kNumLayers];
        size_t offsets[kNumLayers];
        size_t total;
    };

    static constexpr Layout kLayout = []
    {
        Layout layout{};
        for (size_t i = 0, x = capacity; i != kNumLayers; ++i)
        {
            x = ceil_div(x, kWordSize);
            layout.sizes[i] = x;
            layout.offsets[i] = layout.total;
            layout.total += x;
        }
        return layout;
    }();

public:
    static constexpr auto& kLayersSizes = kLayout.sizes;
    static constexpr auto& offsets = kLayout.offsets;
    static constexpr size_t kTotalWords = kLayout.total;
    Word* words;
};

template <u32 capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr bool pbs_add_ex(
    const PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    bool added = false;
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            typename B::ValueType wi = v >> B::kShift;
            auto& word = bits.words[B::offsets[layer] + wi];
            Word m = cast<Word>(Word{1} << (v & B::kMask));
            if constexpr (layer == 0)
            {
                added = (word & m) == 0;
            }
            word |= m;
            v = wi;
        });
    return added;
}

template <u32 capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_add_if(
    const PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v,
    bool c) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    pbs_for_each_layer<B>(
        [&]<size_t layer> [[gnu::always_inline]] (
            std::integral_constant<size_t, layer>) noexcept
        {
            typename B::ValueType wi = v >> B::kShift;
            bits.words[B::offsets[layer] + wi] |= Word{c} << (v & B::kMask);
            v = wi;
        });
}

template <u32 capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr bool pbs_get(
    const PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    return bits.words[B::offsets[0] + (v >> B::kShift)] &
           (Word{1} << (v & B::kMask));
}

template <u32 capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr bool pbs_is_empty(
    const PyramidBitset<capacity, Word>& bits) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    return bits.words[B::offsets[B::kNumLayers - 1]] == 0;
}

// Buffer holds kTotalWords; construction preserves its contents.
template <u32 capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr PyramidBitset<capacity, Word>
pbs_make(Word* buffer) noexcept
{
    return {buffer};
}

template <u32 capacity, typename Word>
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

template <u32 capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_remove(
    const PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    bool prev_empty = true;
    pbs_for_each_layer<B>(
        [&]<size_t layer> [[gnu::always_inline]] (
            std::integral_constant<size_t, layer>) noexcept
        {
            typename B::ValueType wi = v >> B::kShift;
            auto& w = bits.words[B::offsets[layer] + wi];
            w &= ~(Word{prev_empty} << (v & B::kMask));
            v = wi;
            prev_empty = !w;
        });
}

template <u32 capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr bool pbs_remove_ex(
    const PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    bool prev_empty = true, removed = false;
    pbs_for_each_layer<B>(
        [&]<size_t layer> [[gnu::always_inline]] (
            std::integral_constant<size_t, layer>) noexcept
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
#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

inline static constexpr auto max2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return std::max(a, b);
};

inline static constexpr auto upd =
    []<typename T, typename F> [[gnu::always_inline]] (
        T& x,
        const std::type_identity_t<T>& another,
        F&& f) noexcept -> T&
{
    return x = std::forward<F>(f)(x, another);
};

inline static constexpr auto upd_max =
    std::bind(upd, std::placeholders::_1, std::placeholders::_2, max2);

class Solution
{
public:
    inline static u64 bs_words[PyramidBitset<1 << 17>::kTotalWords]{};
    inline static auto bs = pbs_make<1 << 17>(bs_words);
    inline static u64 roots_words[PyramidBitset<(1 << 16) + 1>::kTotalWords]{};
    inline static auto roots = pbs_make<(1 << 16) + 1>(roots_words);
    static u32 impl(const std::vector<u32>& nums) noexcept
    {
        constexpr u32 tt = 31623;  // sqrt(10^9)+1
        u32 f1 = 0;

        for (u32 x : nums)
        {
            f1 += x == 1;

            if (x < tt)
            {
                u32 i = x * 2;
                bool prev = pbs_add_ex(bs, i);
                pbs_add_if(bs, i + 1, !prev);
            }
            else
            {
                u32 s = static_cast<u32>(std::sqrt(static_cast<float>(x)));
                pbs_add_if(roots, s, s * s == x);
            }
        }
        pbs_remove(bs, 2);
        pbs_remove(bs, 3);

        u32 ans = 0;

        while (!pbs_is_empty(bs))
        {
            u32 i = pbs_min(bs);
            u32 x = i / 2, f = 1u + pbs_get(bs, i + 1), t = 1;
            pbs_remove(bs, i);
            pbs_remove(bs, i + 1);

            while (x < tt && f >= 2)
            {
                u32 nx = x * x;
                t += 2;
                i = nx * 2;
                if (nx < tt)
                {
                    f = pbs_remove_ex(bs, i) + pbs_remove_ex(bs, i + 1);
                }
                else
                {
                    f = pbs_remove_ex(roots, x);
                }
                x = nx;
            }

            upd_max(ans, t - (u32{!f} << 1));
        }

        while (!pbs_is_empty(roots))
        {
            pbs_remove(roots, pbs_min(roots));
        }

        if (f1 >= 2) upd_max(ans, f1 - !(f1 & 1));

        return ans;
    }

    auto maximumLength(const std::vector<int>& nums) noexcept
    {
        return impl(reinterpret_cast<const std::vector<u32>&>(nums));
    }
};

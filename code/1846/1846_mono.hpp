#include <array>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>
#include <vector>

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
[[gnu::always_inline]] constexpr void pbs_add(
    const PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    pbs_for_each_layer<B>(
        [&]<size_t layer> [[gnu::always_inline]] (
            std::integral_constant<size_t, layer>) noexcept
        {
            typename B::ValueType wi = v >> B::kShift;
            bits.words[B::offsets[layer] + wi] |= Word{1} << (v & B::kMask);
            v = wi;
        });
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

template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

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
#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

class Solution
{
public:
    static constexpr u32 m = 100'000;
    inline static u16 f[m + 1];
    inline static u64 bs_words[PyramidBitset<m + 1>::kTotalWords]{};
    inline static auto bs = pbs_make<m + 1>(bs_words);
    template <bool big>
    static u32 impl(const std::vector<int>& nums) noexcept
    {
        u32 v = 0, g = 0, n = static_cast<u32>(nums.size());
        auto* __restrict__ data = reinterpret_cast<const u32*>(nums.data());
        for (u32 i = 0; i != n; ++i)
        {
            u32 x = std::min(data[i], m);
            // can overflow 16 bit counter?
            if constexpr (big)
            {
                // will overflow now?
                [[unlikely]]
                if (f[x] == 0xFFFFu)
                {
                    // remember number with overflown frequency
                    // there can only be one.
                    g = x;
                    f[x] = 0;
                }
            }
            ++f[x];
            pbs_add(bs, x);
        }
        while (!pbs_is_empty(bs))
        {
            u32 x = pbs_min(bs);
            pbs_remove(bs, x);
            u32 h = std::exchange(f[x], 0u);
            if constexpr (big)
            {
                [[unlikely]]
                if (g == x)
                {
                    h += (1u << 16);
                }
            }
            v += std::min(x - v, h);
        }
        return v;
    }
    u32 maximumElementAfterDecrementingAndRearranging(
        const std::vector<int>& nums) noexcept
    {
        return std::array{&impl<0>, &impl<1>}[nums.size() >= (1ul << 16)](nums);
    }
};

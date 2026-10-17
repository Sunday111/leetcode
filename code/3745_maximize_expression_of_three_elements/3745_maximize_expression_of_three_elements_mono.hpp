#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <type_traits>
#include <utility>
#include <vector>

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

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

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

struct EmptyType
{
};

inline static constexpr EmptyType kEmpty{};

struct FullType
{
};

inline static constexpr FullType kFull{};

template <bool value, size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    PyramidBitset<capacity, Word>& bits,
    size_t end = capacity) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    constexpr auto m = value ? ~Word{} : Word{};
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            end = ceil_div<size_t>(end, B::kWordSize);
            std::fill_n(
                std::next(bits.words.begin(), B::offsets[layer]),
                end,
                m);
        });
}

template <size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    PyramidBitset<capacity, Word>& bits,
    FullType,
    size_t end = capacity) noexcept
{
    pbs_initialize<true>(bits, end);
}

template <size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    PyramidBitset<capacity, Word>& bits,
    EmptyType,
    size_t end = capacity) noexcept
{
    pbs_initialize<false>(bits, end);
}

template <size_t capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr bool pbs_is_empty(
    const PyramidBitset<capacity, Word>& bits) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    return bits.words[B::offsets[B::kNumLayers - 1]] == 0;
}

template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

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

template <size_t max_value, size_t max_count>
class BitsetPriorityQueue
{
public:
    using B = PyramidBitset<max_value + 1>;
    using ValueType = B::ValueType;
    using FrequencyType = UintForValue<max_count>;
    std::array<FrequencyType, max_value + 1> freq{};
    B bits{};

    [[gnu::always_inline]] constexpr void add(ValueType v) noexcept
    {
        ++freq[v];
        pbs_add(bits, v);
    }

    [[gnu::always_inline]] constexpr void remove(ValueType v) noexcept
    {
        if (0 == --freq[v]) pbs_remove(bits, v);
    }

    [[nodiscard, gnu::always_inline]] constexpr ValueType min() const noexcept
    {
        return pbs_min(bits);
    }

    [[nodiscard, gnu::always_inline]] constexpr ValueType max() const noexcept
    {
        return pbs_max(bits);
    }

    [[gnu::always_inline]] constexpr void clear() noexcept
    {
        pbs_initialize(bits, kEmpty);
        std::ranges::fill(freq, 0);
    }

    [[gnu::always_inline]] constexpr ValueType pop_min() noexcept
    {
        auto lo = min();
        remove(lo);
        return lo;
    }
    [[gnu::always_inline]] constexpr ValueType pop_max() noexcept
    {
        auto hi = max();
        remove(hi);
        return hi;
    }
    [[gnu::always_inline]] constexpr bool is_empty() const noexcept
    {
        return pbs_is_empty(bits);
    }
};

class Solution
{
public:
    int maximizeExpressionOfThree(std::vector<int>& nums)
    {
        BitsetPriorityQueue<200, 100> q;

        for (int v : nums)
        {
            v += 100;
            q.add(v & 0xFF);
        }

        auto a = int{q.pop_max()} - 100;
        auto b = int{q.pop_max()} - 100;
        auto c = int{q.pop_min()} - 100;

        return a + b - c;
    }
};

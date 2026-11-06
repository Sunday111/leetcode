#include <algorithm>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <limits>
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

struct EmptyType
{
};

inline static constexpr EmptyType kEmpty{};

struct FullType
{
};

inline static constexpr FullType kFull{};

template <bool value, u32 capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    const PyramidBitset<capacity, Word>& bits,
    size_t end = capacity) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    assert(end <= capacity);
    if (end == 0)
    {
        bits.words[B::offsets[B::kNumLayers - 1]] = 0;
        return;
    }
    constexpr auto m = value ? ~Word{} : Word{};
    pbs_for_each_layer<B>(
        [&]<size_t layer> [[gnu::always_inline]] (
            std::integral_constant<size_t, layer>) noexcept
        {
            const auto count = end;
            end = ceil_div<size_t>(end, B::kWordSize);
            std::fill_n(bits.words + B::offsets[layer], end, m);
            if constexpr (value)
            {
                bits.words[B::offsets[layer] + end - 1] &=
                    std::numeric_limits<Word>::max() >>
                    ((size_t{0} - count) & B::kMask);
            }
        });
}

template <u32 capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    const PyramidBitset<capacity, Word>& bits,
    FullType,
    size_t end = capacity) noexcept
{
    pbs_initialize<true>(bits, end);
}

template <u32 capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    const PyramidBitset<capacity, Word>& bits,
    EmptyType,
    size_t end = capacity) noexcept
{
    pbs_initialize<false>(bits, end);
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

template <size_t max_value, size_t max_count>
class BitsetPriorityQueue
{
public:
    using B = PyramidBitset<max_value + 1>;
    using ValueType = B::ValueType;
    using FrequencyType = UintForValue<max_count>;
    FrequencyType freq[max_value + 1]{};
    u64 words[B::kTotalWords]{};

    [[gnu::always_inline]] constexpr void add(ValueType v) noexcept
    {
        const auto bits = pbs_make<max_value + 1>(words);
        ++freq[v];
        pbs_add(bits, v);
    }

    [[gnu::always_inline]] constexpr void remove(ValueType v) noexcept
    {
        const auto bits = pbs_make<max_value + 1>(words);
        if (0 == --freq[v]) pbs_remove(bits, v);
    }

    [[nodiscard, gnu::always_inline]] constexpr ValueType min() const noexcept
    {
        const auto bits = pbs_make<max_value + 1>(words);
        return pbs_min(bits);
    }

    [[nodiscard, gnu::always_inline]] constexpr ValueType max() const noexcept
    {
        const auto bits = pbs_make<max_value + 1>(words);
        return pbs_max(bits);
    }

    [[gnu::always_inline]] constexpr void clear() noexcept
    {
        const auto bits = pbs_make<max_value + 1>(words);
        pbs_initialize(bits, kEmpty);
        for (auto& count : freq) count = 0;
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
        const auto bits = pbs_make<max_value + 1>(words);
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

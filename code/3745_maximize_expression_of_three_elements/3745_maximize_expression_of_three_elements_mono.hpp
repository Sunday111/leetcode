#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <numeric>
#include <type_traits>
#include <utility>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

template <typename To>
inline static constexpr auto cast = []<typename From>(From&& v) INLINE_LAMBDA
{
    return static_cast<To>(std::forward<From>(v));
};

template <std::integral T>
[[nodiscard]] FORCE_INLINE static constexpr T ceil_div(T a, T b) noexcept
{
    return (a + (b - 1)) / b;
}

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

template <u64 value>
using UintForValue = std::conditional_t < value < (1 << 8),
      u8,
      std::conditional_t <
          value<
              (1 << 16),
              u16,
              std::conditional_t<value<(1UL << 32), u32, u64>>>;

template <size_t capacity, typename Word = u64>
class PyramidBitset
{
public:
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
            sizes[i] = x;
            x = ceil_div(x, kWordSize);
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

    constexpr PyramidBitset(size_t size = capacity) noexcept  // NOLINT
    {
        assert(size <= capacity);
        initialize(size);
    }

    template <bool v>
    FORCE_INLINE constexpr void set(ValueType idx) noexcept
    {
        if constexpr (v)
        {
            add(idx);
        }
        else
        {
            remove(idx);
        }
    }

    FORCE_INLINE constexpr void add(ValueType v) noexcept
    {
        [&]<size_t... layer>(std::index_sequence<layer...>) INLINE_LAMBDA
        {
            (add_impl<layer>(v), ...);
        }(std::make_index_sequence<kNumLayers>());
    }

    FORCE_INLINE constexpr void remove(ValueType v) noexcept
    {
        [&]<size_t... layer>(std::index_sequence<layer...>) INLINE_LAMBDA
        {
            bool pe = true;
            (rem_impl<layer>(v, pe), ...);
        }(std::make_index_sequence<kNumLayers>());
    }

    [[nodiscard]] FORCE_INLINE constexpr ValueType min() const noexcept
    {
        ValueType x = 0;
        [&]<size_t... layer>(std::index_sequence<layer...>) INLINE_LAMBDA
        {
            (min_impl<kNumLayers - (layer + 1)>(x), ...);
        }(std::make_index_sequence<kNumLayers>());
        return x;
    }

    [[nodiscard]] FORCE_INLINE constexpr ValueType max() const noexcept
    {
        ValueType x = 0;
        [&]<size_t... layer>(std::index_sequence<layer...>) INLINE_LAMBDA
        {
            (max_impl<kNumLayers - (layer + 1)>(x), ...);
        }(std::make_index_sequence<kNumLayers>());
        return x;
    }

    [[nodiscard]] FORCE_INLINE constexpr bool get(ValueType v) const noexcept
    {
        return words[offsets[0] + (v >> kShift)] & (Word{1} << (v & kMask));
    }

    [[nodiscard]] FORCE_INLINE static constexpr size_t get_capacity() noexcept
    {
        return capacity;
    }

    [[nodiscard]] FORCE_INLINE constexpr bool is_empty() const noexcept
    {
        return words[offsets[kNumLayers - 1]] == 0;
    }

    FORCE_INLINE constexpr void initialize(size_t end = capacity) noexcept
    {
        [&]<size_t... layer>(std::index_sequence<layer...>) INLINE_LAMBDA
        {
            ((init_layer<layer>(end)), ...);
        }(std::make_index_sequence<kNumLayers>());
    }

private:
    template <size_t layer>
    FORCE_INLINE constexpr void init_layer(size_t& x) noexcept
    {
        x = ceil_div<size_t>(x, kWordSize);
        std::fill_n(std::next(words.begin(), offsets[layer]), x, 0);
    }

    template <size_t layer>
    FORCE_INLINE constexpr void add_impl(ValueType& v) noexcept
    {
        ValueType wi = v >> kShift;
        words[offsets[layer] + wi] |= Word{1} << (v & kMask);
        v = wi;
    }

    template <size_t layer>
    FORCE_INLINE constexpr void rem_impl(
        ValueType& v,
        bool& prev_empty) noexcept
    {
        ValueType wi = v >> kShift;
        auto& w = words[offsets[layer] + wi];
        w &= ~(Word{prev_empty} << (v & kMask));
        v = wi;
        prev_empty = !w;
    }

    template <size_t layer>
    FORCE_INLINE constexpr void min_impl(ValueType& wi) const noexcept
    {
        u8 bi = std::countr_zero(words[offsets[layer] + wi]) & 0xFF;
        ValueType x = cast<ValueType>(wi << kShift) | cast<ValueType>(bi);
        wi = x;
    }

    template <size_t layer>
    FORCE_INLINE constexpr void max_impl(ValueType& wi) const noexcept
    {
        u8 bi = kMask - std::countl_zero(words[offsets[layer] + wi]) & 0xFF;
        ValueType x = cast<ValueType>(wi << kShift) | cast<ValueType>(bi);
        wi = x;
    }
};

template <size_t max_value, size_t max_count>
class BitsetPriorityQueue
{
public:
    using B = PyramidBitset<max_value + 1>;
    using ValueType = B::ValueType;
    using FrequencyType = UintForValue<max_count>;
    std::array<FrequencyType, max_value + 1> freq{};
    B bits{};

    FORCE_INLINE constexpr void add(ValueType v) noexcept
    {
        ++freq[v];
        bits.add(v);
    }

    FORCE_INLINE constexpr void remove(ValueType v) noexcept
    {
        if (0 == --freq[v]) bits.remove(v);
    }

    [[nodiscard]] FORCE_INLINE constexpr ValueType min() noexcept
    {
        return bits.min();
    }

    [[nodiscard]] FORCE_INLINE constexpr ValueType max() noexcept
    {
        return bits.max();
    }

    FORCE_INLINE constexpr void clear() noexcept
    {
        bits.initialize();
        std::ranges::fill(freq, 0);
    }

    FORCE_INLINE constexpr ValueType pop_min() noexcept
    {
        auto lo = min();
        remove(lo);
        return lo;
    }
    FORCE_INLINE constexpr ValueType pop_max() noexcept
    {
        auto hi = max();
        remove(hi);
        return hi;
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

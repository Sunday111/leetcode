#include <array>
#include <bit>
#include <concepts>
#include <cstdint>
#include <numeric>
#include <tuple>
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
    return ((a + b) - 1) / b;
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
using UintForValue = std::tuple_element_t<
    ceil_div(std::bit_width(value), 8),
    std::tuple<u8, u16, u32, u64>>;

template <size_t size, typename Word = u64>
class PyramidBitset
{
public:
    static constexpr size_t kWordSize = sizeof(Word) * 8;
    static constexpr Word kMask = kWordSize - 1;
    static constexpr int kShift = std::bit_width(kMask);

    using ValueType = UintForValue<size>;
    static constexpr size_t kNumLayers = ceil_div(std::bit_width(size), kShift);
    static constexpr auto kLayersSizes = []
    {
        std::array<size_t, kNumLayers> sizes{};
        for (size_t i = 0, x = size; i != sizes.size(); ++i)
        {
            sizes[i] = x;
            x = ceil_div(x, kWordSize);
        }
        return sizes;
    }();
    static constexpr size_t kTotalWords =
        std::accumulate(kLayersSizes.begin(), kLayersSizes.end(), 0UZ);
    std::array<Word, kTotalWords> words{};
    static constexpr auto offsets = []
    {
        std::array<ValueType, kNumLayers> offsets;  // NOLINT
        std::exclusive_scan(
            kLayersSizes.begin(),
            kLayersSizes.end(),
            offsets.begin(),
            ValueType{});
        return offsets;
    }();

    FORCE_INLINE constexpr void add(ValueType v) noexcept
    {
        [&]<size_t... layer>(std::index_sequence<layer...>)
        {
            (add_impl<layer>(v), ...);
        }(std::make_index_sequence<kNumLayers>());
    }

    FORCE_INLINE constexpr void remove(ValueType v) noexcept
    {
        [&]<size_t... layer>(std::index_sequence<layer...>)
        {
            bool pe = true;
            (rem_impl<layer>(v, pe), ...);
        }(std::make_index_sequence<kNumLayers>());
    }

    [[nodiscard]] FORCE_INLINE constexpr ValueType lowest() const noexcept
    {
        ValueType x = 0;
        [&]<size_t... layer>(std::index_sequence<layer...>)
        {
            (lowest_impl<kNumLayers - (layer + 1)>(x), ...);
        }(std::make_index_sequence<kNumLayers>());
        return x;
    }

    [[nodiscard]] FORCE_INLINE constexpr bool get(ValueType v) const noexcept
    {
        return words[offsets[0] + (v >> kShift)] & (Word{1} << (v & kMask));
    }

private:
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
    FORCE_INLINE constexpr void lowest_impl(ValueType& wi) const noexcept
    {
        u8 bi = std::countr_zero(words[offsets[layer] + wi]) & 0xFF;
        ValueType x = cast<ValueType>(wi << kShift) | cast<ValueType>(bi);
        wi = x;
    }
};

template <size_t value_limit, size_t size_limit>
class BitsetPriorityQueue
{
public:
    using B = PyramidBitset<value_limit>;
    using ValueType = B::ValueType;
    using FrequencyType = UintForValue<size_limit>;
    std::array<FrequencyType, value_limit> freq{};
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
        return bits.lowest();
    }

    FORCE_INLINE constexpr ValueType pop_min() noexcept
    {
        auto lo = min();
        remove(lo);
        return lo;
    }
};

class Solution
{
public:
    using Queue = BitsetPriorityQueue<20'002, 100'000>;
    using ValueType = Queue::ValueType;
    using FreqType = Queue::FrequencyType;
    Queue heap{};

    [[nodiscard]] constexpr int findKthLargest(
        const std::vector<int>& nums,
        const FreqType k) noexcept
    {
        for (FreqType i = 0; i != k; ++i)
        {
            heap.add(cast<ValueType>(nums[i] + 10'000));
        }

        const auto n = cast<FreqType>(nums.size());
        for (FreqType i = k; i != n; ++i)
        {
            heap.add(cast<ValueType>(nums[i] + 10'000));
            heap.pop_min();
        }

        return cast<int>(heap.min()) - 10'000;
    }
};

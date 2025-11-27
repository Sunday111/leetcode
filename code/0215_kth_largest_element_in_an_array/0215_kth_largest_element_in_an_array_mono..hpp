#include <array>
#include <bit>
#include <concepts>
#include <cstdint>
#include <numeric>
#include <tuple>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

template <typename To>
[[nodiscard]] FORCE_INLINE static constexpr To to(auto v) noexcept
{
    return static_cast<To>(v);
}

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

template <size_t size>
class LayeredBitset
{
public:
    using ValueType = UintForValue<size>;
    static constexpr size_t kNumLayers = ceil_div(std::bit_width(size), 6);
    static constexpr auto kLayersSizes = []
    {
        std::array<size_t, kNumLayers> sizes{};
        sizes[0] = ceil_div(size, 64UZ);
        for (size_t i = 1; i != sizes.size(); ++i)
        {
            sizes[i] = ceil_div(sizes[i - 1], 64UZ);
        }
        return sizes;
    }();
    static constexpr size_t kTotalWords =
        std::accumulate(kLayersSizes.begin(), kLayersSizes.end(), 0UZ);
    std::array<u64, kTotalWords> words{};
    std::array<ValueType, kNumLayers> offsets;

    LayeredBitset()
    {
        std::exclusive_scan(
            kLayersSizes.begin(),
            kLayersSizes.end(),
            offsets.begin(),
            ValueType{});
    }

    FORCE_INLINE constexpr void add(ValueType v) noexcept { add_r(v); }
    [[nodiscard]] FORCE_INLINE constexpr ValueType lowest() const noexcept
    {
        return lowest_r();
    }
    [[nodiscard]] FORCE_INLINE constexpr bool get(ValueType v) const noexcept
    {
        return words[offsets[0] + (v >> 6)] & (u64{1} << (v & 63));
    }
    FORCE_INLINE constexpr void remove(ValueType v) noexcept { rem_r(v); }

private:
    template <int layer = 0>
    FORCE_INLINE constexpr void add_r(ValueType v) noexcept
    {
        if constexpr (layer != kNumLayers)
        {
            ValueType wi = v >> 6;
            auto o = offsets[layer];
            words[o + wi] |= u64{1} << (v & 63);
            add_r<layer + 1>(wi);
        }
    }
    template <int layer = 0>
    FORCE_INLINE constexpr void rem_r(
        ValueType v,
        bool prev_empty = true) noexcept
    {
        if constexpr (layer != kNumLayers)
        {
            ValueType wi = v >> 6;
            auto& w = words[offsets[layer] + wi];
            w &= ~(u64{prev_empty} << (v & 63));
            rem_r<layer + 1>(wi, !w);
        }
    }
    template <int layer = kNumLayers - 1>
    [[nodiscard]] FORCE_INLINE constexpr ValueType lowest_r(
        ValueType wi = 0) const noexcept
    {
        u8 bi = std::countr_zero(words[offsets[layer] + wi]) & 63;
        ValueType x = to<ValueType>(wi << 6) | to<ValueType>(bi);
        if constexpr (layer == 0)
        {
            return x;
        }
        else
        {
            return lowest_r<layer - 1>(x);
        }
    }
};

template <size_t value_limit>
class BitsetHeap
{
public:
    using ValueType = UintForValue<value_limit>;
    std::array<ValueType, value_limit> freq{};
    LayeredBitset<value_limit> bits{};

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
    static constexpr u32 kValueLimit = 20'002;
    BitsetHeap<kValueLimit> heap{};

    [[nodiscard]] constexpr int findKthLargest(
        const std::vector<int>& nums,
        const u32 k) noexcept
    {
        for (u32 i = 0; i != k; ++i)
        {
            heap.add(to<u32>(nums[i] + 10'000));
        }

        const u32 n = to<u32>(nums.size());
        for (u32 i = k; i != n; ++i)
        {
            heap.add(to<u32>(nums[i] + 10'000));
            heap.pop_min();
        }

        return to<int>(heap.min()) - 10'000;
    }
};

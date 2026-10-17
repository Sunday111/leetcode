#include <array>
#include <bit>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <numeric>
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
    static constexpr u32 kMaxDiff = 100000;
    static constexpr u32 kNumBlocks = (kMaxDiff + 64) / 64;
    inline static std::array<u32, kMaxDiff + 1> frequency{};
    inline static std::array<u64, kNumBlocks> occupied_values{};
    inline static PyramidBitset<kNumBlocks> occupied_blocks{};

public:
    u64 minSumSquareDiff(
        const std::vector<int>& nums1,
        const std::vector<int>& nums2,
        u32 k1,
        u32 k2)
    {
        occupied_values[0] = 1;
        pbs_add(occupied_blocks, 0);
        for (size_t i = 0; i < nums1.size(); ++i)
        {
            u32 diff = static_cast<u32>(std::abs(nums1[i] - nums2[i]));
            if (frequency[diff]++ == 0)
            {
                u32 block = diff >> 6;
                if (!occupied_values[block])
                {
                    pbs_add(occupied_blocks, static_cast<u16>(block));
                }
                occupied_values[block] |= u64{1} << (diff & 63);
            }
        }

        u32 block = 0;
        u64 bits = 0;
        auto pop_max = [&] [[gnu::always_inline]]
        {
            if (!bits)
            {
                block = pbs_max(occupied_blocks);
                pbs_remove(occupied_blocks, static_cast<u16>(block));
                bits = std::exchange(occupied_values[block], 0);
            }
            u32 bit = 63 - static_cast<u32>(std::countl_zero(bits));
            bits ^= u64{1} << bit;
            return block * 64 + bit;
        };

        u32 k = k1 + k2, level = pop_max();
        u64 count = std::exchange(frequency[level], 0), sum{};
        while (level)
        {
            u32 next = pop_max();
            u64 next_count = std::exchange(frequency[next], 0);
            u64 cost = (level - next) * count;
            if (k < cost)
            {
                sum = u64{next} * next * next_count;
                break;
            }

            k -= static_cast<u32>(cost);
            level = next;
            count += next_count;
        }

        if (level)
        {
            sum += count * level * level + k / count * (k + k % count) +
                   k % count - 2 * u64{level} * k;
        }

        while (bits || !pbs_is_empty(occupied_blocks))
        {
            u32 diff = pop_max();
            sum += u64{diff} * diff * std::exchange(frequency[diff], 0);
        }
        return sum;
    }
};

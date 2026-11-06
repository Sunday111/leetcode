#include <array>
#include <bit>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
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
    static constexpr u32 kMaxDiff = 100000;
    static constexpr u32 kNumBlocks = (kMaxDiff + 64) / 64;
    inline static std::array<u32, kMaxDiff + 1> frequency{};
    inline static std::array<u64, kNumBlocks> occupied_values{};
    inline static u64
        occupied_blocks_words[PyramidBitset<kNumBlocks>::kTotalWords]{};
    inline static auto occupied_blocks =
        pbs_make<kNumBlocks>(occupied_blocks_words);

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

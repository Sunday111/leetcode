#include <array>
#include <bit>
#include <cassert>
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

template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

template <std::integral T>
[[nodiscard, gnu::always_inline]] static constexpr T ceil_div(
    T a,
    std::type_identity_t<T> b) noexcept
{
    return (a + (b - 1)) / b;
}

struct EmptyType
{
};

inline static constexpr EmptyType kEmpty{};

struct FullType
{
};

inline static constexpr FullType kFull{};

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
            x = ceil_div(x, kWordSize);
            sizes[i] = x;
        }
        return sizes;
    }();
    static constexpr size_t kTotalWords =
        std::accumulate(kLayersSizes.begin(), kLayersSizes.end(), 0UZ);
    std::array<Word, kTotalWords> words;

    template <u8 i>
    struct LyrIdx
    {
        // NOLINTNEXTLINE
        [[nodiscard]] consteval operator u8() const noexcept { return i; }
    };

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

    constexpr PyramidBitset() = default;

    // NOLINTNEXTLINE
    constexpr PyramidBitset(FullType, size_t size = capacity) noexcept
    {
        assert(size <= capacity);
        initialize(kFull, size);
    }

    // NOLINTNEXTLINE
    constexpr PyramidBitset(EmptyType, size_t size = capacity) noexcept
    {
        assert(size <= capacity);
        initialize(kEmpty, size);
    }

    template <bool v>
    [[gnu::always_inline]] constexpr void set(ValueType idx) noexcept
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

    [[gnu::always_inline]] constexpr void set(ValueType idx, bool v) noexcept
    {
        if (v)
        {
            add(idx);
        }
        else
        {
            remove(idx);
        }
    }

    [[gnu::always_inline]] constexpr void add(ValueType v) noexcept
    {
        for_each_layer(
            [&] [[gnu::always_inline]] (auto layer) noexcept
            {
                ValueType wi = v >> kShift;
                words[offsets[layer] + wi] |= Word{1} << (v & kMask);
                v = wi;
            });
    }

    [[gnu::always_inline]] constexpr void add_if(ValueType v, bool c) noexcept
    {
        for_each_layer(
            [&] [[gnu::always_inline]] (auto layer) noexcept
            {
                ValueType wi = v >> kShift;
                words[offsets[layer] + wi] |= Word{c} << (v & kMask);
                v = wi;
            });
    }

    // Returns true if element did not exist previously
    [[nodiscard, gnu::always_inline]] constexpr bool add_ex(
        ValueType v) noexcept
    {
        bool added = false;
        for_each_layer(
            [&] [[gnu::always_inline]] (auto layer) noexcept
            {
                ValueType wi = v >> kShift;
                auto& word = words[offsets[layer] + wi];
                Word m = Word{1} << (v & kMask);
                if constexpr (layer == 0)
                {
                    added = (word & m) == 0;
                }
                word |= m;
                v = wi;
            });
        return added;
    }

    [[gnu::always_inline]] constexpr void remove(ValueType v) noexcept
    {
        bool prev_empty = true;
        for_each_layer(
            [&] [[gnu::always_inline]] (auto layer) noexcept
            {
                ValueType wi = v >> kShift;
                auto& w = words[offsets[layer] + wi];
                w &= ~(Word{prev_empty} << (v & kMask));
                v = wi;
                prev_empty = !w;
            });
    }

    [[nodiscard, gnu::always_inline]] constexpr bool remove_ex(
        ValueType v) noexcept
    {
        bool prev_empty = true, removed = false;
        for_each_layer(
            [&] [[gnu::always_inline]] (auto layer) noexcept
            {
                ValueType wi = v >> kShift;
                auto& w = words[offsets[layer] + wi];
                if constexpr (layer == 0)
                {
                    removed = (w & (Word{1} << (v & kMask)));
                }

                w &= ~(Word{prev_empty} << (v & kMask));
                v = wi;
                prev_empty = !w;
            });

        return removed;
    }

    [[nodiscard, gnu::always_inline]] constexpr ValueType min() const noexcept
    {
        assert(!is_empty());
        ValueType wi = 0;
        for_each_layer_reversed(
            [&] [[gnu::always_inline]] (auto layer) noexcept
            {
                u8 bi = std::countr_zero(words[offsets[layer] + wi]) & 0xFF;
                ValueType x =
                    cast<ValueType>(wi << kShift) | cast<ValueType>(bi);
                wi = x;
            });
        return wi;
    }

    [[nodiscard, gnu::always_inline]] constexpr ValueType max() const noexcept
    {
        ValueType wi = 0;
        for_each_layer_reversed(
            [&] [[gnu::always_inline]] (auto layer) noexcept
            {
                u8 bi =
                    kMask - std::countl_zero(words[offsets[layer] + wi]) & 0xFF;
                ValueType x =
                    cast<ValueType>(wi << kShift) | cast<ValueType>(bi);
                wi = x;
            });
        return wi;
    }

    [[nodiscard, gnu::always_inline]] constexpr bool get(
        ValueType v) const noexcept
    {
        return words[offsets[0] + (v >> kShift)] & (Word{1} << (v & kMask));
    }

    [[nodiscard, gnu::always_inline]] static constexpr size_t
    get_capacity() noexcept
    {
        return capacity;
    }

    [[nodiscard, gnu::always_inline]] constexpr bool is_empty() const noexcept
    {
        return words[offsets[kNumLayers - 1]] == 0;
    }

    [[gnu::always_inline]] constexpr void initialize(
        FullType,
        size_t end = capacity) noexcept
    {
        initialize<true>(end);
    }

    [[gnu::always_inline]] constexpr void initialize(
        EmptyType,
        size_t end = capacity) noexcept
    {
        initialize<false>(end);
    }

    template <bool value>
    [[gnu::always_inline]] constexpr void initialize(
        size_t end = capacity) noexcept
    {
        constexpr auto m = value ? ~Word{} : Word{};
        for_each_layer(
            [&] [[gnu::always_inline]] (auto layer) noexcept
            {
                end = ceil_div<size_t>(end, kWordSize);
                std::fill_n(std::next(words.begin(), offsets[layer]), end, m);
            });
    }

private:
    template <typename F>
    [[gnu::always_inline]] constexpr static void for_each_layer(F&& f) noexcept
    {
        [&]<size_t... layer> [[gnu::always_inline]] (
            std::index_sequence<layer...>) noexcept
        {
            (f(LyrIdx<layer>{}), ...);
        }(std::make_index_sequence<kNumLayers>());
    }

    template <typename F>
    [[gnu::always_inline]] constexpr static void for_each_layer_reversed(
        F&& f) noexcept
    {
        for_each_layer([&] [[gnu::always_inline]] (auto layer) noexcept
                       { f(LyrIdx<kNumLayers - (layer + 1)>{}); });
    }
};
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
    inline static PyramidBitset<kNumBlocks> occupied_blocks{kEmpty};

public:
    u64 minSumSquareDiff(
        const std::vector<int>& nums1,
        const std::vector<int>& nums2,
        u32 k1,
        u32 k2)
    {
        occupied_values[0] = 1;
        occupied_blocks.add(0);
        for (size_t i = 0; i < nums1.size(); ++i)
        {
            u32 diff = static_cast<u32>(std::abs(nums1[i] - nums2[i]));
            if (frequency[diff]++ == 0)
            {
                u32 block = diff >> 6;
                if (!occupied_values[block])
                {
                    occupied_blocks.add(static_cast<u16>(block));
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
                block = occupied_blocks.max();
                occupied_blocks.remove(static_cast<u16>(block));
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

        while (bits || !occupied_blocks.is_empty())
        {
            u32 diff = pop_max();
            sum += u64{diff} * diff * std::exchange(frequency[diff], 0);
        }
        return sum;
    }
};

#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <numeric>
#include <ranges>
#include <type_traits>
#include <utility>
#include <vector>







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

    [[nodiscard, gnu::always_inline]] constexpr ValueType min() const noexcept
    {
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
        bits.add(v);
    }

    [[gnu::always_inline]] constexpr void remove(ValueType v) noexcept
    {
        if (0 == --freq[v]) bits.remove(v);
    }

    [[nodiscard, gnu::always_inline]] constexpr ValueType min() const noexcept
    {
        return bits.min();
    }

    [[nodiscard, gnu::always_inline]] constexpr ValueType max() const noexcept
    {
        return bits.max();
    }

    [[gnu::always_inline]] constexpr void clear() noexcept
    {
        bits.initialize();
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
        return bits.is_empty();
    }
};

class Solution
{
public:
    int minOperations(std::vector<std::vector<int>>& g, int x)
    {
        BitsetPriorityQueue<10'000, 100'000> b{};

        int tm = g.front().front() % x;
        for (int v : g | std::views::join)
        {
            [[unlikely]] if ((v % x) != tm)
            {
                return -1;
            }

            b.add(v & 0xFFFF);
        }

        u32 m = static_cast<u32>(g.size() * g.front().size()) / 2;
        for (u32 i = 0; i != m; ++i) b.pop_min();

        int t = b.min();

        int r = 0;
        for (int v : g | std::views::join)
        {
            r += std::abs(t - v) / x;
        }
        return r;
    }
};

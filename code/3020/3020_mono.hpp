#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <concepts>
#include <cstdint>
#include <functional>
#include <numeric>
#include <type_traits>
#include <utility>
#include <vector>



struct EmptyType
{
};

inline static constexpr EmptyType kEmpty{};


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




inline static constexpr auto max2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return std::max(a, b);
};


inline static constexpr auto upd =
    []<typename T, typename F> [[gnu::always_inline]] (
        T & x,
        const std::type_identity_t<T>& another,
        F&& f) noexcept -> T&
{
    return x = std::forward<F>(f)(x, another);
};

inline static constexpr auto upd_max =
    std::bind(upd, std::placeholders::_1, std::placeholders::_2, max2);

class Solution
{
public:
    inline static PyramidBitset<1 << 17> bs{kEmpty};
    inline static PyramidBitset<(1 << 16) + 1> roots{kEmpty};
    static u32 impl(const std::vector<u32>& nums) noexcept
    {
        constexpr u32 tt = 31623;  // sqrt(10^9)+1
        u32 f1 = 0;

        for (u32 x : nums)
        {
            f1 += x == 1;

            if (x < tt)
            {
                u32 i = x * 2;
                bool prev = bs.add_ex(i);
                bs.add_if(i + 1, !prev);
            }
            else
            {
                u32 s = static_cast<u32>(std::sqrt(static_cast<float>(x)));
                roots.add_if(s, s * s == x);
            }
        }
        bs.remove(2);
        bs.remove(3);

        u32 ans = 0;

        for (u32 i = bs.min(); i < (1u << 17); i = bs.min())
        {
            u32 x = i / 2, f = 1u + bs.get(i + 1), t = 1;
            bs.remove(i);
            bs.remove(i + 1);

            while (x < tt && f >= 2)
            {
                u32 nx = x * x;
                t += 2;
                i = nx * 2;
                if (nx < tt)
                {
                    f = bs.remove_ex(i) + bs.remove_ex(i + 1);
                }
                else
                {
                    f = roots.remove_ex(x);
                }
                x = nx;
            }

            upd_max(ans, t - (u32{!f} << 1));
        }

        for (u32 x = roots.min(); x < (1 << 16); x = roots.min())
        {
            roots.remove(x);
        }

        if (f1 >= 2) upd_max(ans, f1 - !(f1 & 1));

        return ans;
    }

    auto maximumLength(const std::vector<int>& nums) noexcept
    {
        return impl(reinterpret_cast<const std::vector<u32>&>(nums));
    }
};

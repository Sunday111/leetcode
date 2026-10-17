#include <algorithm>
#include <array>
#include <bit>
#include <bitset>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

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
[[nodiscard, gnu::always_inline]] constexpr bool pbs_get(
    const PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    return bits.words[B::offsets[0] + (v >> B::kShift)] &
           (Word{1} << (v & B::kMask));
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

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

class Solution
{
public:
    i64 minimumCost(
        std::string_view source,
        std::string_view target,
        std::vector<std::string>& original,
        std::vector<std::string>& changed,
        std::vector<int>& cost)
    {
        if (source == target) return 0;

        static std::array<u32, 26> trie_links[200000];
        static u8 trie_ids[200000];
        u32 next_node = 0;
        u8 num_unique_tokens = 0;

        // reset trie
        trie_links[0].fill(~u32{});
        trie_ids[0] = 0xFF;
        num_unique_tokens = 0;
        next_node = 1;

        auto trie_insert = [&](std::string_view s)
        {
            u32 cur = 0;
            for (char c : s)
            {
                u8 char_index = (c - 'a') & 0xFF;
                if (~u32{} == trie_links[cur][char_index])
                {
                    trie_links[cur][char_index] = next_node;
                    trie_links[next_node].fill(~u32{});
                    trie_ids[next_node] = 0xFF;
                    ++next_node;
                }
                cur = trie_links[cur][char_index];
            }
            if (trie_ids[cur] == 0xFF) trie_ids[cur] = num_unique_tokens++;
            return trie_ids[cur];
        };

        u16 max_len = 0;

        // Reset bitsets
        static std::array<PyramidBitset<256>, 200> bitsets{};
        for (u8 i = 0; i != 200; ++i)
        {
            pbs_initialize(bitsets[i], kEmpty, 200);
        }
        u32 dist[200][200];  // NOLINT
        for (u8 i = 0; i != 200; ++i)
        {
            std::fill_n(dist[i], 200, 1000000000);
        }

        u8 num_sorted = 0;
        std::pair<std::string_view, u8> sorted_tokens[200];
        std::bitset<256> uniq_orig;
        for (u32 i = 0; i != original.size(); ++i)
        {
            u8 from = trie_insert(original[i]);
            sorted_tokens[num_sorted] = {original[i], from};
            num_sorted += !uniq_orig[from];
            uniq_orig[from] = 1;

            max_len = cast<u16>(std::max<size_t>(max_len, original[i].size()));

            u8 to = trie_insert(changed[i]);
            dist[from][to] = std::min(dist[from][to], cast<u32>(cost[i]));
            pbs_add(bitsets[from], to);
        }
        std::ranges::sort(
            sorted_tokens,
            sorted_tokens + num_sorted,
            std::less{},
            [&](auto& x) { return std::get<0>(x).size(); });

        for (u8 k = 0; k != num_unique_tokens; ++k)
        {
            for (u8 i = 0; i != num_unique_tokens; ++i)
            {
                auto& bi = bitsets[i];
                if (!pbs_get(bi, k)) continue;

                for (auto bk = bitsets[k]; !pbs_is_empty(bk);)
                {
                    u8 j = pbs_min(bk);
                    pbs_remove(bk, j);
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                    pbs_add(bi, j);
                }
            }
        }

        static u64 dp[1001];
        const u16 n = cast<u16>(source.size());
        constexpr u64 kHuge = 100'000'000'000'000;
        dp[n] = 0;

        for (u16 i = n - 1; i != 0xFFFF; --i)
        {
            u64 x = dp[i + 1] + (kHuge & -u64{source[i] != target[i]});

            u32 curS = 0, curT = 0;

            const auto ll = std::min<u16>(i + max_len, n);
            for (u16 j = i; j != ll && (curS | curT) != ~u32{}; ++j)
            {
                curS = trie_links[curS][cast<u8>(source[j] - 'a')];
                curT = trie_links[curT][cast<u8>(target[j] - 'a')];

                if ((curS | curT) != ~u32{} &&
                    (trie_ids[curS] | trie_ids[curT]) != 0xFF)
                {
                    auto c = dist[trie_ids[curS]][trie_ids[curT]];
                    if (c < 1000000000)
                    {
                        x = std::min(x, c + dp[j + 1]);
                    }
                }
            }

            dp[i] = std::min(x, kHuge);
        }

        if (dp[0] >= kHuge) return -1;
        return cast<i64>(dp[0]);
    }
};

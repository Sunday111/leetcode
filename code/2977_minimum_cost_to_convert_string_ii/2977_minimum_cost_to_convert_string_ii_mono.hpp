#include <algorithm>
#include <array>
#include <bit>
#include <bitset>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <numeric>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

template <typename To>
inline static constexpr auto cast = []<typename From>(From&& v) INLINE_LAMBDA
{
    return static_cast<To>(std::forward<From>(v));
};

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

template <std::integral T>
[[nodiscard]] FORCE_INLINE static constexpr T ceil_div(T a, T b) noexcept
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

        // Register unique tokens
        std::unordered_map<std::string_view, u8> token_to_index;
        u8 num_unique_tokens = 0;
        for (std::string_view s : original)
        {
            num_unique_tokens +=
                token_to_index.try_emplace(s, num_unique_tokens).second;
        }
        for (std::string_view s : changed)
        {
            num_unique_tokens +=
                token_to_index.try_emplace(s, num_unique_tokens).second;
        }

        u8 num_sorted = 0;
        std::pair<std::string_view, u8> sorted_tokens[200];

        {
            std::bitset<256> visited;
            for (std::string_view token : original)
            {
                u8 idx = token_to_index[token];
                sorted_tokens[num_sorted] = {token, idx};
                num_sorted += !visited[idx];
                visited[idx] = 1;
            }
            num_sorted = visited.count() & 0xFF;
            std::ranges::sort(
                sorted_tokens,
                sorted_tokens + num_sorted,
                std::less{},
                [&](auto& x)
                {
                    auto [s, i] = x;
                    return std::make_tuple(s.size(), i);
                });
        }

        u32 dist[200][200];  // NOLINT
        for (u8 i = 0; i != num_unique_tokens; ++i)
        {
            std::fill_n(dist[i], num_unique_tokens, 1000000000);
        }

        assert(num_unique_tokens <= 200);

        // Reset bitsets
        static std::array<PyramidBitset<256>, 200> bitsets{};
        for (u8 i = 0; i != num_unique_tokens; ++i)
        {
            bitsets[i].initialize(num_unique_tokens);
        }

        for (u32 i = 0; i != original.size(); ++i)
        {
            u8 from = token_to_index[original[i]];
            u8 to = token_to_index[changed[i]];
            dist[from][to] = std::min(dist[from][to], cast<u32>(cost[i]));
            bitsets[from].add(to);
        }

        for (u8 k = 0; k != num_unique_tokens; ++k)
        {
            for (u8 i = 0; i != num_unique_tokens; ++i)
            {
                auto& bi = bitsets[i];
                if (!bi.get(k)) continue;

                for (auto bk = bitsets[k]; !bk.is_empty();)
                {
                    u8 j = bk.min();
                    bk.remove(j);
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                    bi.add(j);
                }
            }
        }

        for (u8 i = 0; i != num_unique_tokens; ++i)
        {
            dist[i][i] = 0;
            bitsets[i].add(i);
        }

        static u64 dp[1001];
        const u16 n = cast<u16>(source.size());
        constexpr u64 kHuge = 100'000'000'000'000;
        dp[n] = 0;

        for (u16 i = n - 1; i != 0xFFFF; --i)
        {
            auto& dpi = dp[i] = kHuge;
            if (source[i] == target[i]) dpi = dp[i + 1];

            std::string_view sub_src = source.substr(i);

            u16 max_l = n - i;
            for (u8 j = 0; j != num_sorted; ++j)
            {
                auto& [src_token, src_idx] = sorted_tokens[j];

                u16 l = cast<u16>(src_token.size());
                if (l > max_l) break;
                if (!sub_src.starts_with(src_token)) continue;

                auto tgt_token = target.substr(i, l);
                if (auto it = token_to_index.find(tgt_token);
                    it != token_to_index.end() &&
                    bitsets[src_idx].get(it->second))
                {
                    dpi = std::min(dpi, dist[src_idx][it->second] + dp[i + l]);
                }
            }
        }

        if (dp[0] >= kHuge) return -1;
        return cast<i64>(dp[0]);
    }
};

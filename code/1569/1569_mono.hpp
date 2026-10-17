#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
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

inline constexpr u32 kMOD = 1'000'000'007;

struct ModInt
{
    u32 value = 0;
};

[[gnu::always_inline]] constexpr ModInt& operator*=(
    ModInt& lhs,
    const ModInt& rhs) noexcept
{
    u64 v = rhs.value;
    v *= lhs.value;
    if (v >= kMOD) v %= kMOD;
    lhs.value = cast<u32>(v);
    return lhs;
}

[[nodiscard, gnu::always_inline]] constexpr ModInt operator*(
    ModInt lhs,
    const ModInt& rhs) noexcept
{
    lhs *= rhs;
    return lhs;
}

template <std::size_t lim_factorial>
constexpr ModInt binomial_coefficient(
    const std::array<ModInt, lim_factorial>& factorials,
    const std::array<ModInt, lim_factorial>& inverse_factorials,
    u32 n,
    u32 k) noexcept
{
    assert(n >= k);
    return factorials[n] * inverse_factorials[k] * inverse_factorials[n - k];
}

template <u32 max_index>
inline constexpr auto factorials_mods()
{
    std::array<ModInt, max_index + 1> r;  // NOLINT
    r[0] = ModInt{1};
    for (u32 i = 1; i != r.size(); ++i)
    {
        r[i] = r[i - 1] * ModInt{i};
    }

    return r;
}

[[nodiscard, gnu::always_inline]] constexpr ModInt inverse(ModInt x) noexcept
{
    auto a = x.value;
    u32 x0 = 1, x1 = 0, mod = kMOD;
    while (a)
    {
        u32 q = mod / a;
        u32 r = mod % a;
        u32 x2 = x1 - q * x0;
        mod = a;
        a = r;
        x1 = x0;
        x0 = x2;
    }
    return {(x1 + kMOD) % kMOD};
}

template <std::size_t size>
inline constexpr auto mod_int_inv_precompute(
    const std::array<ModInt, size>& divisors)
{
    std::array<ModInt, size> inverses;
    for (std::size_t i = 0; i != size; ++i)
    {
        assert(divisors[i].value != 0);
        inverses[i] = inverse(divisors[i]);
    }
    return inverses;
}

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

    // Both searches exclude v and return capacity when no neighbour exists.
    [[nodiscard, gnu::always_inline]] constexpr size_t predecessor(
        ValueType v) const noexcept
    {
        return find_neighbour<false>(v);
    }

    [[nodiscard, gnu::always_inline]] constexpr size_t successor(
        ValueType v) const noexcept
    {
        return find_neighbour<true>(v);
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
    template <bool forward>
    [[nodiscard, gnu::always_inline]] constexpr size_t find_neighbour(
        size_t position) const noexcept
    {
        assert(position < capacity);
        for (size_t layer = 0; layer != kNumLayers; ++layer)
        {
            size_t wi = position >> kShift;
            size_t bi = position & kMask;
            Word candidates = words[offsets[layer] + wi];
            if constexpr (forward)
            {
                candidates >>= bi;
                candidates >>= 1;
            }
            else
            {
                candidates &= (Word{1} << bi) - 1;
            }
            if (candidates)
            {
                if constexpr (forward)
                {
                    position += 1 + cast<size_t>(std::countr_zero(candidates));
                }
                else
                {
                    position = (wi << kShift) + kMask -
                               cast<size_t>(std::countl_zero(candidates));
                }
                while (layer != 0)
                {
                    --layer;
                    Word word = words[offsets[layer] + position];
                    size_t bit = 0;
                    if constexpr (forward)
                    {
                        bit = cast<size_t>(std::countr_zero(word));
                    }
                    else
                    {
                        bit = kMask - cast<size_t>(std::countl_zero(word));
                    }
                    position = (position << kShift) + bit;
                }
                return position < capacity ? position : capacity;
            }
            position = wi;
        }
        return capacity;
    }

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

inline constexpr u32 kNullNode = 1023;

struct Node
{
    u32 v : 10 = 0;
    u32 l : 10 = kNullNode;
    u32 r : 10 = kNullNode;
};

class Solution
{
public:
    inline static Node nodes[1001];
    inline static u16 q[1001];
    inline static constexpr auto factorials = factorials_mods<1000>();
    inline static constexpr auto inverse_factorials =
        mod_int_inv_precompute(factorials);

    static void construct_tree(const std::vector<int>& nums) noexcept
    {
        nodes[0] = {};
        nodes[0].v = nums[0] & 1023;
        std::array<u16, 1001> node_ids;  // NOLINT
        PyramidBitset<1001> inserted{kEmpty};
        node_ids[nodes[0].v] = 0;
        inserted.add(nums[0] & 1023);

        for (size_t i = 1; i != nums.size(); ++i)
        {
            u16 node_id = i & 0xFFFF;
            u16 value = nums[i] & 1023;
            auto next = inserted.successor(value);
            auto prev = inserted.predecessor(value);
            u16 parent_id = 0;
            if (next != inserted.get_capacity()) parent_id = node_ids[next];
            if (prev != inserted.get_capacity())
            {
                parent_id = std::max(parent_id, node_ids[prev]);
            }

            nodes[node_id] = {};
            nodes[node_id].v = nums[i] & 1023;
            auto& parent = nodes[parent_id];
            if (nums[i] < parent.v)
            {
                parent.l = node_id;
            }
            else
            {
                parent.r = node_id;
            }
            node_ids[value] = node_id;
            inserted.add(value);
        }
    }

    u32 numOfWays(const std::vector<int>& nums) noexcept
    {
        construct_tree(nums);

        auto [_, x] = [&](this auto&& dfs,
                          u16 node_id) -> std::pair<u16, ModInt>
        {
            if (node_id == kNullNode) return {0, {1}};

            auto [num, ways] = dfs(nodes[node_id].l);
            auto [rnum, rways] = dfs(nodes[node_id].r);
            num += rnum;
            ways *= rways;

            if ((!!num) & (num != rnum))
            {
                ways *= binomial_coefficient(
                    factorials,
                    inverse_factorials,
                    num,
                    rnum);
            }

            return {num + 1, ways};
        }(0);

        return x.value - 1;
    }
};

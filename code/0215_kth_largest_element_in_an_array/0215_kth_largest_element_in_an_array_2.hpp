#include <array>
#include <bit>
#include <vector>

using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

#define FORCE_INLINE inline __attribute__((always_inline))

template <u16 layer>
struct LastLayerFn
{
    [[nodiscard]] static constexpr u16 last_layer() noexcept { return layer; }
};

[[nodiscard]] constexpr u32 reqWords(u32 v) noexcept
{
    return std::max(1u, (v / 64) + !(v % 64));
}

[[nodiscard]] constexpr size_t count_layers(u32 size) noexcept
{
    u32 w = reqWords(size);
    if (w == 1) return 1;
    return 1 + count_layers(w);
}

template <size_t size>
[[nodiscard]] constexpr auto layers_sizes_arr() noexcept
{
    constexpr size_t num_layers = count_layers(size);
    std::array<u32, num_layers> sizes{};
    sizes[0] = reqWords(size);
    for (size_t i = 1; i != num_layers; ++i) sizes[i] = reqWords(sizes[i - 1]);
    return sizes;
}

static_assert(count_layers(20'000) == 3);

template <size_t size>
[[nodiscard]] constexpr auto layers_sizes_seq() noexcept
{
    constexpr auto arr = layers_sizes_arr<size>();
    return [&]<size_t... i>(std::index_sequence<i...>)
    {
        return std::integer_sequence<u32, arr[i]...>{};
    }(std::make_index_sequence<arr.size()>());
}

template <size_t size>
using layers_sizes_seq_t = decltype(layers_sizes_seq<size>());
static_assert(std::same_as<
              layers_sizes_seq_t<20'000>,
              std::integer_sequence<u32, 312, 4, 1>>);

template<u32 size> 
using LayersWords = decltype([]<u32... layers_sizes>(std::integer_sequence<u32, layers_sizes...>){
    return std::tuple<std::array<u64, layers_sizes>...>{};
}(
    layers_sizes_seq<size>()
));

template <size_t size>
struct PyramidBitset
{
    static constexpr u32 num_layers = count_layers(size);
    LayersWords<size> layers{};

    FORCE_INLINE constexpr void add(u32 v) noexcept { add_r(v); }

    [[nodiscard]] FORCE_INLINE constexpr u32 lowest() const noexcept
    {
        return lowest_r();
    }

    [[nodiscard]] FORCE_INLINE constexpr bool get(u32 v) const noexcept
    {
        u32 wi = v >> 6;
        auto& l = std::get<0>(layers);
        return l[wi] & (u64{1} << (v & 63));
    }

    FORCE_INLINE constexpr void remove(u32 v) noexcept { rem_r(v); }

private:
    template <u32 layer = 0>
    FORCE_INLINE constexpr void add_r(u32 v) noexcept
    {
        if constexpr (layer != num_layers)
        {
            u32 wi = v >> 6;
            auto& l = std::get<layer>(layers);
            l[wi] |= u64{1} << (v & 63);
            add_r<layer + 1>(wi);
        }
    }

    template <u32 layer>
    FORCE_INLINE constexpr void rem_r(u32 v, bool prev_empty = true) noexcept
    {
        if constexpr (layer != num_layers)
        {
            u32 wi = v >> 6;
            auto& l = std::get<layer>(layers);
            l[wi] &= ~(u64{prev_empty} << (v & 63));
            rem_r<layer + 1>(wi, !l[wi]);
        }
    }

    template <u32 layer = num_layers - 1>
    [[nodiscard]] FORCE_INLINE constexpr u32 lowest_r(u32 wi = 0) const noexcept
    {
        const auto& l = std::get<layer>(layers);
        u32 x = (wi << 6) | (std::countr_zero(l[wi]) & 63);
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

class Solution
{
public:
    static constexpr u16 kValueLimit = 20'002;
    static constexpr u16 kLayer0 = (kValueLimit >> 6) + 1;
    static constexpr u16 kLayer1 = (kLayer0 >> 6) + 1;
    std::array<u32, kValueLimit> freq{};
    std::array<u64, kLayer0> bs0{};
    std::array<u64, kLayer1> bs1{};
    u64 bs2{};
    static_assert(kLayer1 <= 64);

    FORCE_INLINE constexpr void add(u16 v) noexcept
    {
        ++freq[v];
        u16 wi0 = v >> 6, wi1 = wi0 >> 6;
        bs0[wi0] |= u64{1} << (v & 63);
        bs1[wi1] |= u64{1} << (wi0 & 63);
        bs2 |= u64{1} << (wi1 & 63);
    }

    FORCE_INLINE constexpr void rem(u16 v) noexcept
    {
        u16 wi0 = v >> 6, bi0 = v & 63;
        u16 wi1 = wi0 >> 6, bi1 = wi0 & 63;
        u16 bi2 = wi1 & 63;
        bs0[wi0] &= ~(u64{!--freq[v]} << bi0);
        bs1[wi1] &= ~(u64{!bs0[wi0]} << bi1);
        bs2 &= ~(u64{!bs1[wi1]} << bi2);
    }

    [[nodiscard]] FORCE_INLINE constexpr u16 min_element() const noexcept
    {
        auto wi1 = std::countr_zero(bs2);
        auto bi1 = std::countr_zero(bs1[wi1 & 0xFFFF]);
        auto wi0 = (wi1 << 6) | bi1, bi0 = std::countr_zero(bs0[wi0 & 0xFFFF]);
        return ((wi0 << 6) | bi0) & 0xFFFF;
    }

    [[nodiscard]] constexpr int findKthLargest(
        const std::vector<int>& nums,
        const u32 k) noexcept
    {
        for (u32 i = 0; i != k; ++i)
        {
            add(static_cast<u16>(nums[i] + 10'000));
        }

        const u32 n = static_cast<u32>(nums.size());
        for (u32 i = k; i != n; ++i)
        {
            add(static_cast<u16>(nums[i] + 10'000));
            rem(min_element());
        }

        return static_cast<int>(min_element()) - 10'000;
    }
};

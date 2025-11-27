#pragma once

#include <array>
#include <numeric>

#include "force_inline.hpp"
#include "to.hpp"
#include "uint_for_value.hpp"

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

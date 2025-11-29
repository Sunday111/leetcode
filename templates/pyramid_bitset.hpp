#pragma once

#include <array>
#include <numeric>

#include "cast.hpp"
#include "force_inline.hpp"
#include "uint_for_value.hpp"

template <size_t size>
class PyramidBitset
{
public:
    using ValueType = UintForValue<size>;
    static constexpr size_t kNumLayers = ceil_div(std::bit_width(size), 6);
    static constexpr auto kLayersSizes = []
    {
        std::array<size_t, kNumLayers> sizes{};
        for (size_t i = 0, x = size; i != sizes.size(); ++i)
        {
            sizes[i] = x;
            x = ceil_div(x, 64uz);
        }
        return sizes;
    }();
    static constexpr size_t kTotalWords =
        std::accumulate(kLayersSizes.begin(), kLayersSizes.end(), 0UZ);
    std::array<u64, kTotalWords> words{};
    static constexpr auto offsets = []
    {
        std::array<ValueType, kNumLayers> offsets;  // NOLINT
        std::exclusive_scan(
            kLayersSizes.begin(),
            kLayersSizes.end(),
            offsets.begin(),
            ValueType{});
        return offsets;
    }();

    FORCE_INLINE constexpr void add(ValueType v) noexcept
    {
        [&]<size_t... layer>(std::index_sequence<layer...>)
        {
            (add_impl<layer>(v), ...);
        }(std::make_index_sequence<kNumLayers>());
    }

    FORCE_INLINE constexpr void remove(ValueType v) noexcept
    {
        [&]<size_t... layer>(std::index_sequence<layer...>)
        {
            bool pe = true;
            (rem_impl<layer>(v, pe), ...);
        }(std::make_index_sequence<kNumLayers>());
    }

    [[nodiscard]] FORCE_INLINE constexpr ValueType lowest() const noexcept
    {
        ValueType x = 0;
        [&]<size_t... layer>(std::index_sequence<layer...>)
        {
            (lowest_impl<kNumLayers - (layer + 1)>(x), ...);
        }(std::make_index_sequence<kNumLayers>());
        return x;
    }

    [[nodiscard]] FORCE_INLINE constexpr bool get(ValueType v) const noexcept
    {
        return words[offsets[0] + (v >> 6)] & (u64{1} << (v & 63));
    }

private:
    template <size_t layer>
    FORCE_INLINE constexpr void add_impl(ValueType& v) noexcept
    {
        ValueType wi = v >> 6;
        words[offsets[layer] + wi] |= u64{1} << (v & 63);
        v = wi;
    }

    template <size_t layer>
    FORCE_INLINE constexpr void rem_impl(
        ValueType& v,
        bool& prev_empty) noexcept
    {
        ValueType wi = v >> 6;
        auto& w = words[offsets[layer] + wi];
        w &= ~(u64{prev_empty} << (v & 63));
        v = wi;
        prev_empty = !w;
    }

    template <size_t layer>
    FORCE_INLINE constexpr void lowest_impl(ValueType& wi) const noexcept
    {
        u8 bi = std::countr_zero(words[offsets[layer] + wi]) & 63;
        ValueType x = cast<ValueType>(wi << 6) | cast<ValueType>(bi);
        wi = x;
    }
};

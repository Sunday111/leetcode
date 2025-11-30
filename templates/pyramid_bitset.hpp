#pragma once

#include <array>
#include <bit>
#include <cassert>
#include <numeric>

#include "cast.hpp"
#include "ceil_div.hpp"
#include "uint_for_value.hpp"

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

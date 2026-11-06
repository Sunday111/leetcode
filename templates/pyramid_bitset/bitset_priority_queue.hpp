#pragma once

#include "pyramid_bitset/pbs_add.hpp"
#include "pyramid_bitset/pbs_initialize.hpp"
#include "pyramid_bitset/pbs_is_empty.hpp"
#include "pyramid_bitset/pbs_make.hpp"
#include "pyramid_bitset/pbs_max.hpp"
#include "pyramid_bitset/pbs_min.hpp"
#include "pyramid_bitset/pbs_remove.hpp"

template <size_t max_value, size_t max_count>
class BitsetPriorityQueue
{
public:
    using B = PyramidBitset<max_value + 1>;
    using ValueType = B::ValueType;
    using FrequencyType = UintForValue<max_count>;
    FrequencyType freq[max_value + 1]{};
    u64 words[B::kTotalWords]{};

    [[gnu::always_inline]] constexpr void add(ValueType v) noexcept
    {
        const auto bits = pbs_make<max_value + 1>(words);
        ++freq[v];
        pbs_add(bits, v);
    }

    [[gnu::always_inline]] constexpr void remove(ValueType v) noexcept
    {
        const auto bits = pbs_make<max_value + 1>(words);
        if (0 == --freq[v]) pbs_remove(bits, v);
    }

    [[nodiscard, gnu::always_inline]] constexpr ValueType min() const noexcept
    {
        const auto bits = pbs_make<max_value + 1>(words);
        return pbs_min(bits);
    }

    [[nodiscard, gnu::always_inline]] constexpr ValueType max() const noexcept
    {
        const auto bits = pbs_make<max_value + 1>(words);
        return pbs_max(bits);
    }

    [[gnu::always_inline]] constexpr void clear() noexcept
    {
        const auto bits = pbs_make<max_value + 1>(words);
        pbs_initialize(bits, kEmpty);
        for (auto& count : freq) count = 0;
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
        const auto bits = pbs_make<max_value + 1>(words);
        return pbs_is_empty(bits);
    }
};

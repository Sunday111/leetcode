#include <algorithm>

#include "pyramid_bitset.hpp"

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

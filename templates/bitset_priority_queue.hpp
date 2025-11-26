#include "pyramid_bitset.hpp"

template <size_t value_limit, size_t size_limit>
class BitsetPriorityQueue
{
public:
    using B = PyramidBitset<value_limit>;
    using ValueType = B::ValueType;
    using FrequencyType = UintForValue<size_limit>;
    std::array<FrequencyType, value_limit> freq{};
    B bits{};

    FORCE_INLINE constexpr void add(ValueType v) noexcept
    {
        ++freq[v];
        bits.add(v);
    }

    FORCE_INLINE constexpr void remove(ValueType v) noexcept
    {
        if (0 == --freq[v]) bits.remove(v);
    }

    [[nodiscard]] FORCE_INLINE constexpr ValueType min() noexcept
    {
        return bits.lowest();
    }

    FORCE_INLINE constexpr ValueType pop_min() noexcept
    {
        auto lo = min();
        remove(lo);
        return lo;
    }
};

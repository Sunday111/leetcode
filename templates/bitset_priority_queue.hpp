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

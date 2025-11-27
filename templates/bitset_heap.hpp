#include "layered_bitset.hpp"

template <size_t value_limit>
class BitsetHeap
{
public:
    using ValueType = UintForValue<value_limit>;
    std::array<ValueType, value_limit> freq{};
    LayeredBitset<value_limit> bits{};

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

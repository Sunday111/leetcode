#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"

template <std::integral T, std::unsigned_integral Idx>
class FenwickTree
{
public:
    std::vector<T> bits;
    Idx size;

    explicit constexpr FenwickTree(Idx n) noexcept : bits(n + 1), size{n} {}

    // Add delta to an element at i
    constexpr void add(Idx i, T delta) noexcept
    {
        ++i;
        while (i <= size)
        {
            bits[i] += delta;
            i += i & (~i + 1);
        }
    }

    // Subtract delta from an element at i
    constexpr void sub(Idx i, T delta) noexcept
    {
        ++i;
        while (i <= size)
        {
            bits[i] -= delta;
            i += i & (~i + 1);
        }
    }

    // Sum of elements BEFORE i
    [[nodiscard]] constexpr T sum(Idx i) const noexcept
    {
        T sum{};
        while (i)
        {
            sum += bits[cast<u32>(i)];
            i -= i & (~i + 1);
        }
        return sum;
    }

    // Value of element
    [[nodiscard]] constexpr T elem(Idx i) const noexcept
    {
        return sum(i + 1) - sum(i);
    }

    // Update element value. Returns magnitude of value change
    constexpr int update(Idx i, int val) noexcept
    {
        int prev = elem(i);
        int delta = val - prev;
        add(i, delta);
        return delta;
    }

    // Sum values in range [i; j)
    [[nodiscard]] constexpr int sumRange(Idx i, Idx j) const noexcept
    {
        return sum(j) - sum(i);
    }
};

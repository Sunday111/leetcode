#include <algorithm>
#include <cassert>
#include <span>

template <std::integral T, std::unsigned_integral Idx>
class FenwickTree
{
public:
    T* data;
    Idx n;

    explicit constexpr FenwickTree(Idx size, std::span<T> buffer) noexcept
        : data(buffer.data()),
          n{size}
    {
        assert(buffer.size() > size);  // Need 1 extra element
        std::fill_n(data, n + 1, T{});
    }

    // Add delta to an element at i
    [[gnu::always_inline]] constexpr void add(Idx i, T delta) noexcept
    {
        ++i;
        while (i <= n)
        {
            data[i] += delta;
            i += i & (~i + 1);
        }
    }

    // Subtract delta from an element at i
    [[gnu::always_inline]] constexpr void sub(Idx i, T delta) noexcept
    {
        ++i;
        while (i <= n)
        {
            data[i] -= delta;
            i += i & (~i + 1);
        }
    }

    // Sum of elements BEFORE i
    [[nodiscard, gnu::always_inline]] constexpr T sum(Idx i) const noexcept
    {
        T sum{};
        while (i)
        {
            sum += data[i];
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
    [[gnu::always_inline]] constexpr T update(Idx i, T val) noexcept
    {
        T prev = elem(i);
        T delta = val - prev;
        add(i, delta);
        return delta;
    }

    // Sum values in range [i; j)
    [[nodiscard, gnu::always_inline]] constexpr T sumRange(Idx i, Idx j)
        const noexcept
    {
        return sum(j) - sum(i);
    }
};

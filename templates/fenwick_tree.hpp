#include <vector>

template <std::integral T>
class FenwickTree
{
public:
    std::vector<T> bits;
    uint16_t size;

    explicit constexpr FenwickTree(uint16_t n) noexcept : bits(n + 1), size{n}
    {
    }

    constexpr void add(uint16_t i, T delta) noexcept
    {
        while (i <= size)
        {
            bits[i] += delta;
            i += i & (~i + 1);
        }
    }

    constexpr void sub(uint16_t i, T delta) noexcept
    {
        while (i <= size)
        {
            bits[i] -= delta;
            i += i & (~i + 1);
        }
    }

    [[nodiscard]] constexpr T sum(uint16_t i) const noexcept
    {
        T sum{};
        while (i)
        {
            sum += bits[static_cast<unsigned>(i)];
            i -= i & (~i + 1);
        }
        return sum;
    }
};

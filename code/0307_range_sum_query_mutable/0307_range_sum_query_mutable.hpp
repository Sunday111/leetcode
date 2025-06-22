#pragma once

#include <vector>

template <std::integral T, std::unsigned_integral Idx>
class FenwickTree
{
public:
    std::vector<T>& bits;  // NOLINT
    Idx size;

    explicit constexpr FenwickTree(std::vector<T>& data, Idx n) noexcept
        : bits(data),
          size{n}
    {
        bits.clear();
        bits.resize(n + 1);
    }

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
            sum += bits[static_cast<unsigned>(i)];
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

using u16 = uint16_t;

class NumArray
{
public:
    [[nodiscard]] std::vector<int>& getStaticData() noexcept
    {
        static auto data = []()
        {
            std::vector<int> v;
            v.reserve(30'000);
            return v;
        }();

        return data;
    }

    constexpr explicit NumArray(const std::vector<int>& nums) noexcept
        : fenwick(getStaticData(), nums.size() & 0xFFFF)
    {
        for (u16 i = 0; i != fenwick.size; ++i)
        {
            fenwick.add(i, nums[i]);
        }
    }

    constexpr void update(u16 i, int val) noexcept
    {
        int prev = fenwick.elem(i);
        fenwick.add(i, val - prev);
    }

    [[nodiscard]] constexpr int sumRange(u16 left, u16 right) const noexcept
    {
        return fenwick.sumRange(left, right + 1);
    }

private:
    FenwickTree<int, u16> fenwick;
};

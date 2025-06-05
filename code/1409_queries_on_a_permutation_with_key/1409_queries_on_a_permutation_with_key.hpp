#pragma once

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

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> processQueries(
        std::vector<int>& queries,
        uint16_t m) noexcept
    {
        uint16_t n = static_cast<uint16_t>(queries.size());

        FenwickTree<uint16_t> ft(n + m);
        std::vector<uint16_t> val_to_idx(m + 1);
        for (uint16_t i = 1; i <= m; ++i)
        {
            uint16_t virutal_idx = n + i;
            val_to_idx[i] = virutal_idx;
            ft.add(virutal_idx, 1);
        }

        uint16_t next_free = n;
        std::vector<int> r;
        r.reserve(n);
        for (int v : queries)
        {
            uint16_t& pos = val_to_idx[v & 0xFFFF];
            uint16_t s = ft.sum(pos);
            r.push_back(s - 1);
            ft.sub(pos, 1);
            pos = next_free--;
            ft.add(pos, 1);
        }

        return r;
    }
};

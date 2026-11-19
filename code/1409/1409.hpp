#pragma once

#include <cstdint>
#include <vector>

#include "fenwick_tree/ft.hpp"
#include "fenwick_tree/ft_add.hpp"
#include "fenwick_tree/ft_prefix.hpp"
#include "fenwick_tree/ft_update.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> processQueries(
        std::vector<int>& queries,
        uint16_t m) noexcept
    {
        uint16_t n = static_cast<uint16_t>(queries.size());

        std::vector<uint16_t> bits(static_cast<unsigned>(n) + m);
        FenwickTree<uint16_t, uint16_t, FenwickTreeAddTraits> ft{
            bits.data(),
            static_cast<uint16_t>(n + m)};
        std::vector<uint16_t> val_to_idx(m + 1);
        for (uint16_t i = 0; i != m; ++i)
        {
            uint16_t position = static_cast<uint16_t>(n + i);
            val_to_idx.at(static_cast<unsigned>(i) + 1) = position;
            ft_update(ft, position, 1);
        }

        uint16_t next_free = n;
        std::vector<int> r;
        r.reserve(n);
        for (int v : queries)
        {
            uint16_t& pos = val_to_idx.at(static_cast<uint16_t>(v));
            r.push_back(ft_prefix(ft, pos));
            ft_update(ft, pos, 0);
            pos = --next_free;
            ft_update(ft, pos, 1);
        }

        return r;
    }
};

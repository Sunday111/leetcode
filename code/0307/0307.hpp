#pragma once

#include <vector>

#include "fenwick_tree/ft.hpp"
#include "fenwick_tree/ft_add.hpp"
#include "fenwick_tree/ft_make.hpp"
#include "fenwick_tree/ft_range.hpp"
#include "fenwick_tree/ft_update.hpp"
#include "integral_aliases.hpp"

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
    {
        auto& data = getStaticData();
        data.resize(nums.size());
        fenwick = ft_make<int, u16, FenwickTreeAddTraits>(
            nums.data(),
            static_cast<u16>(nums.size()),
            data.data());
    }

    constexpr void update(u16 i, int val) noexcept
    {
        ft_update(fenwick, i, val);
    }

    [[nodiscard]] constexpr int sumRange(u16 left, u16 right) const noexcept
    {
        return ft_range(fenwick, left, static_cast<u16>(right + 1));
    }

private:
    FenwickTree<int, u16, FenwickTreeAddTraits> fenwick{};
};

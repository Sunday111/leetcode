#pragma once

#include <cstdint>
#include <vector>

class Solution
{
public:
    int64_t minSum(
        const std::vector<int32_t>& nums1,
        const std::vector<int32_t>& nums2)
    {
        auto count = [](const std::vector<int32_t>& data)
        {
            size_t num_zeroes = 0;
            size_t sum = 0;
            for (auto v : data)
            {
                if (v == 0)
                {
                    ++num_zeroes;
                }
                else
                {
                    sum += static_cast<size_t>(v);
                }
            }

            return std::make_tuple(num_zeroes, sum);
        };

        auto [za, sa] = count(nums1);
        auto [zb, sb] = count(nums2);

        sa += za;
        sb += zb;

        if (sa > sb)
        {
            std::swap(za, zb);
            std::swap(sa, sb);
        }

        size_t delta = sb - sa;

        if (delta == 0) return static_cast<int64_t>(sb);

        if (za == 0) return -1;

        return static_cast<int64_t>(sb);
    }
};

#pragma once

#include <vector>

class Solution
{
public:
    std::vector<int> sumEvenAfterQueries(
        std::vector<int>& nums,
        const std::vector<std::vector<int>>& queries)
    {
        int sum_even = 0;
        for (int num : nums)
        {
            sum_even += (num % 2) ? 0 : num;
        }

        std::vector<int> r;
        r.reserve(queries.size());
        for (auto& q : queries)
        {
            int& v = nums[q[1] & 0xFFFF];
            int add = q[0];

            if ((v % 2) == 0) sum_even -= v;
            v += add;
            if ((v % 2) == 0) sum_even += v;

            r.push_back(sum_even);
        }

        return r;
    }
};

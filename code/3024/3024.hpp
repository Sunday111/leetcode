#pragma once

#include <algorithm>
#include <string>
#include <vector>

class Solution
{
public:
    std::string triangleType(std::vector<int>& nums)
    {
        std::ranges::sort(nums);
        const int a = nums[0], b = nums[1], c = nums[2];
        if ((a + b) <= nums[2]) return "none";
        if (a == b && b == c) return "equilateral";
        if (a == b || b == c || c == a) return "isosceles";
        return "scalene";
    }
};

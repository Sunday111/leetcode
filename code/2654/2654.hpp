#include <algorithm>
#include <numeric>
#include <vector>

class Solution
{
public:
    int minOperations(std::vector<int>& nums)
    {
        const size_t n = nums.size();
        size_t l = 0;
        int lgcd = 0, rgcd = 0, g = 0;
        std::vector<int> left{0}, right;

        auto add = [&](int v)
        {
            rgcd = std::gcd(rgcd, v);
            right.emplace_back(v);
            g = std::gcd(lgcd, rgcd);
            ++l;
        };

        auto remove = [&]()
        {
            if (!lgcd)
            {
                rgcd = 0;
                left.clear();
                std::swap(left, right);
                left.push_back(0);
                std::ranges::reverse(left);
                left.pop_back();
                for (auto& v : left) v = lgcd = std::gcd(lgcd, v);
            }
            else
            {
                left.pop_back();
            }

            lgcd = left.back();

            --l;
            g = std::gcd(lgcd, rgcd);
        };

        if (auto ones = static_cast<size_t>(std::ranges::count(nums, 1)))
        {
            return static_cast<int>(n - ones);
        }

        size_t shortest = n + 1;
        for (size_t i = 0; i != n && shortest > 2; ++i)
        {
            add(nums[i]);

            while (g == 1 && l > 1)
            {
                shortest = std::min(shortest, l);
                remove();
            }
        }

        if (shortest > n) return -1;
        return static_cast<int>((n - 1) + (shortest - 1));
    }
};

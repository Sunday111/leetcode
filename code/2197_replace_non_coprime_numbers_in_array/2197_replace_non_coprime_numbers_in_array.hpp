#include <numeric>
#include <vector>

class Solution
{
public:
    [[nodiscard]] constexpr std::vector<int> replaceNonCoprimes(
        std::vector<int>& nums) noexcept
    {
        uint32_t n = 0;
        for (int b : nums)
        {
            while (n)
            {
                int gcd = std::gcd(nums[n - 1], b);
                if (gcd == 1) break;
                b *= nums[n-- - 1] / gcd;
            }
            nums[n++] = b;
        }

        nums.resize(n);
        return std::move(nums);
    }
};

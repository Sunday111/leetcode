#include <algorithm>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int maxFrequency(
        std::vector<int>& nums,
        int k) noexcept
    {
        std::ranges::sort(nums, std::greater{});

        auto i = nums.begin(), j = i, e = nums.end();
        int r = 0;
        while (j != e && std::distance(i, e) > r)
        {
            if (auto d = *i - *j; d <= k)
            {
                r = std::max<int>(r, static_cast<int>(++j - i));
                k -= d;
            }
            else
            {
                int pv = *i++;
                k += static_cast<int>(j - i) * (pv - *i);
            }
        }

        return r;
    }
};

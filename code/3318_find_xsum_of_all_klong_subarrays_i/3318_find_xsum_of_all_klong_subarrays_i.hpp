#include <algorithm>
#include <array>
#include <functional>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    using int2 = std::pair<u32, u32>;
    static constexpr int x_sum(const auto& freq, u32 x) noexcept
    {
        auto freq2 = freq;  // copy
        std::ranges::sort(freq2, std::greater<int2>{});
        int sum = 0;
        for (u32 i = 0; i != x; i++)
        {
            auto [f, num] = freq2[i];
            if (f == 0) break;
            sum += num * f;
        }
        return sum;
    }

    [[nodiscard]] static constexpr std::vector<int>
    findXSum(std::vector<int>& nums, u32 k, u32 x) noexcept
    {
        const u32 n = static_cast<u32>(nums.size()), sz = n - k + 1;
        std::vector<int> result(sz);
        std::array<int2, 51> freq;
        freq.fill({0, 0});
        for (u32 r = 0; r != k; ++r)
        {
            u32 z = static_cast<u32>(nums[r]);
            freq[z].second = z;
            freq[z].first++;
        }

        result[0] = x_sum(freq, x);
        for (u32 l = 1, r = k; l < sz; l++, r++)
        {
            u32 L = static_cast<u32>(nums[l - 1]);
            u32 R = static_cast<u32>(nums[r]);
            freq[L].first--;
            freq[R].first++;
            freq[R].second = R;
            result[l] = x_sum(freq, x);
        }
        return result;
    }
};

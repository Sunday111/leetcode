#pragma once

#include <algorithm>
#include <bitset>
#include <vector>

class Solution
{
public:
    using u16 = uint16_t;

    [[nodiscard]] static constexpr u16 maximumLength(
        const std::vector<int>& nums_,
        u16 k) noexcept
    {
        u16 n = 0;
        std::array<u16, 1000> freq{};
        std::array<u16, 1000> nums;  // NOLINT
        for (int v : nums_) ++freq[nums[n++] = (v % k) & 0xFFFF];

        u16 max_len = std::max<u16>(2, *std::ranges::max_element(freq));

        const auto nums_end = nums.begin() + n;

        std::bitset<1024> v, v2;
        for (u16 i = 0; i != n; ++i)
        {
            const u16 vi = nums[i], fi = freq[vi];
            if (v[vi]) continue;
            v[vi] = true;
            if (fi * 2 + 1 <= max_len) continue;

            v2 = v;

            for (u16 j = i + 1; j != n && j + max_len <= n; ++j)
            {
                u16 a = vi, b = nums[j];
                if (v2[b]) continue;
                v2[b] = true;

                if (u16 fj = freq[b];
                    (std::min(fi, fj) * 2 + (fi != fj)) <= max_len)
                {
                    continue;
                }

                u16 len = 2;
                for (auto it = std::find(nums.begin() + j, nums_end, a);
                     it != nums_end;
                     it = std::find(it, nums_end, a))
                {
                    ++len;
                    std::swap(a, b);
                }

                max_len = std::max(max_len, len);
            }
        }

        return max_len;
    }
};

class Solution2
{
public:
    using u16 = uint16_t;

    [[nodiscard]] static constexpr u16 maximumLength(
        const std::vector<int>& nums_,
        u16 k) noexcept
    {
        u16 n = 0;
        std::array<u16, 1000> freq{};
        std::array<u16, 1000> nums;  // NOLINT
        for (int v : nums_) ++freq[nums[n++] = (v % k) & 0xFFFF];

        u16 max_len = std::max<u16>(2, *std::ranges::max_element(freq));

        const auto nums_end = nums.begin() + n;

        std::bitset<1024> v, v2;
        for (u16 i = 0; i != n; ++i)
        {
            const u16 vi = nums[i], fi = freq[vi];
            if (v[vi]) continue;
            v[vi] = true;
            if (fi * 2 + 1 <= max_len) continue;

            v2 = v;

            for (u16 j = i + 1; j != n && j + max_len <= n; ++j)
            {
                u16 a = vi, b = nums[j];
                if (v2[b]) continue;
                v2[b] = true;

                if (u16 fj = freq[b];
                    (std::min(fi, fj) * 2 + (fi != fj)) <= max_len)
                {
                    continue;
                }

                u16 len = 2;
                for (auto it = std::find(nums.begin() + j, nums_end, a);
                     it != nums_end;
                     it = std::find(it, nums_end, a))
                {
                    ++len;
                    std::swap(a, b);
                }

                max_len = std::max(max_len, len);
            }
        }

        return max_len;
    }
};

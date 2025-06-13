#pragma once

#include <algorithm>
#include <span>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    using u8 = uint8_t;

    template <typename To, typename From, size_t extent = std::dynamic_extent>
    [[nodiscard]] static auto reinterpret_span(std::span<From, extent> in)
    {
        return std::span<To, extent>{
            reinterpret_cast<To*>(in.data()),  // NOLINT
            in.size()};
    }

    [[nodiscard]] static std::vector<u32>& get_static_data()
    {
        static std::vector<u32> v;
        v.reserve(100'000);
        return v;
    }

    static void radixSortBase64(std::span<u32> arr) noexcept
    {
        constexpr u8 kBitsPerPass = 6;
        constexpr u8 kNumPasses =
            (32 + kBitsPerPass - 1) / kBitsPerPass;  // = 6
        constexpr u32 kRadix = 1u << kBitsPerPass;   // = 64
        constexpr u32 kMask = kRadix - 1;            // = 0x3F

        u32 n = static_cast<u32>(arr.size());
        if (n == 0) return;

        auto& temp = get_static_data();
        temp.clear();
        temp.resize(n);

        std::array<u32, kRadix> count{};

        for (u8 pass = 0; pass < kNumPasses; ++pass)
        {
            count.fill(0);
            const u32 shift = pass * kBitsPerPass;

            // Count digit occurrences
            for (auto v : arr) ++count[(v >> shift) & kMask];

            // Prefix sums for positions
            for (u32 i = 1; i < kRadix; ++i) count[i] += count[i - 1];

            // Stable placement
            u32 i = n;
            do
            {
                --i;
                u32 digit = (arr[i] >> shift) & kMask;
                temp[--count[digit]] = arr[i];
            } while (i);

            std::ranges::copy(temp, arr.begin());
        }
    }

    [[nodiscard]] static u32 minimizeMax(std::vector<int>& nums, u32 p) noexcept
    {
        return minimizeMax(reinterpret_span<u32>(std::span{nums}), p);
    }

    [[nodiscard]] static u32 minimizeMax(std::span<u32> nums, u32 p) noexcept
    {
        const u32 n = static_cast<u32>(nums.size());
        radixSortBase64(nums);

        u32 l = 0;
        u32 r = nums.back() - nums.front();

        while (l < r)
        {
            u32 mid = l + (r - l) / 2;

            u32 pairs = 0, i = 1;
            while (i < n && pairs < p)
            {
                bool ok = mid >= (nums[i] - nums[i - 1]);
                pairs += ok;
                i += 1 + ok;
            }

            if (pairs >= p)
            {
                r = mid;
            }
            else
            {
                l = mid + 1;
            }
        }

        return l;
    }
};

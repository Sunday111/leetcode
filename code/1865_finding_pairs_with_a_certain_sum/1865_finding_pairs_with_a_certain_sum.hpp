#pragma once

#include <algorithm>
#include <span>
#include <unordered_map>
#include <vector>

#ifdef __GNUC__
#define ATTR inline __attribute__((always_inline))
#else
#define ATTR inline
#endif

class FindSumPairs
{
public:
    using u32 = uint32_t;
    using i32 = int32_t;

    [[nodiscard]] ATTR static std::unordered_map<i32, u32>& freq2() noexcept
    {
        static auto m = []()
        {
            std::unordered_map<i32, u32> r;
            r.reserve(100'000);
            return r;
        }();
        return m;
    }

    ATTR FindSumPairs(std::vector<i32>& nums1, std::vector<i32>& nums2) noexcept
        : n1{nums1},
          n2{nums2}
    {
        std::ranges::sort(n1);
        freq2().clear();
        for (i32 v : n2) ++freq2()[v];
    }

    ATTR void add(i32 index, i32 val) noexcept
    {
        i32& v = n2[std::bit_cast<u32>(index)];
        --freq2()[v];
        v += val;
        ++freq2()[v];
    }

    [[nodiscard]] ATTR i32 count(i32 tot) const noexcept
    {
        u32 r = 0;
        for (i32 v : n1)
        {
            const i32 search = tot - v;
            if (search < 1) break;
            if (auto it = freq2().find(search); it != freq2().end())
            {
                r += it->second;
            }
        }

        return std::bit_cast<i32>(r);
    }

private:
    std::span<i32> n1, n2;
};

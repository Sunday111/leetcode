#pragma once

#include <algorithm>
#include <span>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    using u64 = uint64_t;

private:
    static auto& get_static_data() noexcept
    {
        static auto v = []()
        {
            std::vector<u64> data;
            data.resize(100'000);
            return data;
        }();
        return v;
    }

    template <typename To, typename From, size_t extent = std::dynamic_extent>
    [[nodiscard]] static auto reinterpret_span(
        std::span<From, extent> in) noexcept
    {
        return std::span<To, extent>{
            reinterpret_cast<To*>(in.data()),  // NOLINT
            in.size()};
    }

public:
    [[nodiscard]] static auto chalkReplacer(
        const std::vector<int>& chalk,
        u32 k) noexcept
    {
        const u32 n = static_cast<u32>(chalk.size());
        const auto c = reinterpret_span<const u32>(std::span{chalk});

        auto& sums = get_static_data();

        u64 s = 0;
        for (u32 i = 0; i != n; ++i)
        {
            s += c[i];
            sums[i] = s;
        }

        k %= s;

        const auto begin = sums.begin();
        const auto end = std::next(begin, n);
        return std::distance(begin, std::upper_bound(begin, end, u64{k}));
    }
};

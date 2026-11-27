#include "radix_sort/adaptive_sort.hpp"

#include <random>
#include <vector>

#include "gtest/gtest.h"

TEST(AdaptiveSort, OrdersTheSelectedFieldAndPreservesPayloads)
{
    std::mt19937_64 rng{3947};
    for (u32 n : {0u, 1u, 63u, 64u, 65u, 1024u})
    {
        for (u32 limit : {0u, 255u, 256u, 65535u, 65536u})
        {
            std::vector<u64> values(n);
            for (auto& v : values)
            {
                v = (rng() & 0xFFFF0000000000FFull) |
                    ((rng() % (limit + 1)) << 8);
            }
            if (n) values.front() = u64{limit} << 8;
            auto expected = values;
            adaptive_sort<17, 1024, 8>(values.data(), n, limit);
            EXPECT_TRUE(
                std::ranges::is_sorted(
                    values,
                    std::less{},
                    [](u64 v) { return (v >> 8) & 0x1FFFF; }));
            std::ranges::sort(values);
            std::ranges::sort(expected);
            EXPECT_EQ(values, expected);
        }
    }
}

TEST(AdaptiveSort, FullWidthWithoutBound)
{
    std::mt19937_64 rng{64};
    for (u32 n : {63u, 64u})
    {
        std::vector<u64> values(n);
        std::ranges::generate(values, [&] { return rng(); });
        auto expected = values;
        std::ranges::sort(expected);
        adaptive_sort<64, 64>(values.data(), n);
        EXPECT_EQ(values, expected);
    }
}

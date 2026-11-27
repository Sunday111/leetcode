#include "radix_sort/adaptive_sort_indices_by.hpp"

#include <numeric>
#include <vector>

#include "gtest/gtest.h"

TEST(AdaptiveSortIndicesBy, SelectsTheSameFieldAcrossDispatchBoundaries)
{
    const auto key = [](u32 i)
    {
        return (u64{i % 3} << 56) | (u64{i % 127} << 32) | (8192 - i);
    };
    for (u32 n : {1u, 255u, 256u, 1279u, 1280u, 8191u, 8192u})
    {
        SCOPED_TRACE(n);
        std::vector<u32> indices(n);
        std::iota(indices.begin(), indices.end(), 0u);
        adaptive_sort_indices_by<7, 8192, 32>(indices.data(), n, key);
        EXPECT_TRUE(
            std::ranges::is_sorted(
                indices,
                std::less{},
                [](u32 i) { return i % 127; }));
        std::ranges::sort(indices);
        for (u32 i = 0; i != n; ++i) ASSERT_EQ(indices.at(i), i);
    }
}

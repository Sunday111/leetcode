#include <vector>

#include "0307_range_sum_query_mutable.hpp"
#include "gtest/gtest.h"

TEST(t0307, Example)
{
    const std::vector<int> source{1, 3, 5};
    NumArray array(source);
    EXPECT_EQ(array.sumRange(0, 2), 9);
    array.update(1, 2);
    EXPECT_EQ(array.sumRange(0, 2), 8);
    EXPECT_EQ(array.sumRange(1, 1), 2);
    EXPECT_EQ(source, (std::vector<int>{1, 3, 5}));
}

TEST(t0307, RangesMatchReferenceAfterUpdates)
{
    std::vector<int> reference{-4, 0, 7, 3, -2, 9};
    NumArray array(reference);
    const auto size = static_cast<u16>(reference.size());
    const auto verify = [&]
    {
        for (u16 begin = 0; begin != size; ++begin)
        {
            int expected = 0;
            for (u16 end = begin; end != size; ++end)
            {
                expected += reference.at(end);
                EXPECT_EQ(array.sumRange(begin, end), expected);
            }
        }
    };
    verify();
    for (int pass = 0; pass != 3; ++pass)
    {
        for (u16 i = 0; i != size; ++i)
        {
            reference.at(i) = pass * 5 - static_cast<int>(i);
            array.update(i, reference.at(i));
            verify();
        }
    }
}

TEST(t0307, SingleElement)
{
    NumArray array(std::vector<int>{-5});
    EXPECT_EQ(array.sumRange(0, 0), -5);
    array.update(0, 0);
    EXPECT_EQ(array.sumRange(0, 0), 0);
    array.update(0, 8);
    EXPECT_EQ(array.sumRange(0, 0), 8);
}
